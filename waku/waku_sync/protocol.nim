when (NimMajor, NimMinor) < (1, 4):
  {.push raises: [Defect].}
else:
  {.push raises: [].}

import
  std/options,
  stew/results,
  chronicles,
  chronos,
  metrics,
  libp2p/protocols/protocol,
  libp2p/stream/connection,
  libp2p/crypto/crypto,
  eth/p2p/discoveryv5/enr
import
  ../common/nimchronos,
  ../common/enr,
  ../waku_core,
  ../waku_enr,
  ../node/peer_manager/peer_manager,
  ./raw_bindings,
  ./common,
  ./session

logScope:
  topics = "waku sync"

type WakuSync* = ref object of LPProtocol
  storage: Storage # Negentropy protocol storage 
  peerManager: PeerManager
  maxFrameSize: int

  syncInterval: timer.Duration # Time between each syncronisation attempt
  relayJitter: Duration # Time delay until all messages are mostly received network wide
  transferCallBack: Option[TransferCallback] # Callback for message transfer.

  pruneCallBack: Option[PruneCallBack] # Callback with the result of the archive query
  pruneStart: Timestamp # Last pruning start timestamp
  pruneOffset: timer.Duration # Offset to prune a bit more than necessary. 

  periodicSyncFut: Future[void]
  periodicPruneFut: Future[void]

proc storageSize*(self: WakuSync): int =
  self.storage.len

proc ingessMessage*(self: WakuSync, pubsubTopic: PubsubTopic, msg: WakuMessage) =
  if msg.ephemeral:
    return

  let msgHash: WakuMessageHash = computeMessageHash(pubsubTopic, msg)

  trace "inserting message into storage ",
    hash = msgHash.toHex(), timestamp = msg.timestamp

  if self.storage.insert(msg.timestamp, msgHash).isErr():
    debug "failed to insert message ", hash = msgHash.toHex()

proc calculateRange(jitter: Duration, syncRange: Duration = 1.hours): (int64, int64) =
  var now = getNowInNanosecondTime()

  # Because of message jitter inherent to Relay protocol
  now -= jitter.nanos

  let range = syncRange.nanos

  let start = now - range
  let `end` = now

  return (start, `end`)

proc request(
    self: WakuSync, conn: Connection
): Future[Result[seq[WakuMessageHash], string]] {.async, gcsafe.} =
  let (start, `end`) = calculateRange(self.relayJitter)

  let initialized =
    ?clientInitialize(self.storage, conn, self.maxFrameSize, start, `end`)

  debug "sync session initialized",
    client = self.peerManager.switch.peerInfo.peerId,
    server = conn.peerId,
    frameSize = self.maxFrameSize,
    timeStart = start,
    timeEnd = `end`

  var hashes: seq[WakuMessageHash]
  var reconciled = initialized

  while true:
    let sent = ?await reconciled.send()

    trace "sync payload sent",
      client = self.peerManager.switch.peerInfo.peerId,
      server = conn.peerId,
      payload = reconciled.payload

    let received = ?await sent.listenBack()

    trace "sync payload received",
      client = self.peerManager.switch.peerInfo.peerId,
      server = conn.peerId,
      payload = received.payload

    reconciled = (?received.clientReconcile(hashes)).valueOr:
      let completed = error # Result[Reconciled, Completed]

      ?await completed.clientTerminate()

      debug "sync session ended gracefully",
        client = self.peerManager.switch.peerInfo.peerId, server = conn.peerId

      return ok(hashes)

proc sync*(
    self: WakuSync, peerInfo: Option[RemotePeerInfo] = none(RemotePeerInfo)
): Future[Result[(seq[WakuMessageHash], RemotePeerInfo), string]] {.async, gcsafe.} =
  let peer =
    if peerInfo.isSome():
      peerInfo.get()
    else:
      let peer: RemotePeerInfo = self.peerManager.selectPeer(WakuSyncCodec).valueOr:
        return err("No suitable peer found for sync")

      peer

  let connOpt = await self.peerManager.dialPeer(peer, WakuSyncCodec)

  let conn: Connection = connOpt.valueOr:
    return err("Cannot establish sync connection")

  let hashes: seq[WakuMessageHash] = (await self.request(conn)).valueOr:
    debug "sync session ended",
      server = self.peerManager.switch.peerInfo.peerId, client = conn.peerId, error

    return err("Sync request error: " & error)

  return ok((hashes, peer))

proc handleLoop(
    self: WakuSync, conn: Connection
): Future[Result[seq[WakuMessageHash], string]] {.async.} =
  let (start, `end`) = calculateRange(self.relayJitter)

  let initialized =
    ?serverInitialize(self.storage, conn, self.maxFrameSize, start, `end`)

  var sent = initialized

  while true:
    let received = ?await sent.listenBack()

    trace "sync payload received",
      server = self.peerManager.switch.peerInfo.peerId,
      client = conn.peerId,
      payload = received.payload

    let reconciled = (?received.serverReconcile()).valueOr:
      let completed = error # Result[Reconciled, Completed]

      let hashes = await completed.serverTerminate()

      return ok(hashes)

    sent = ?await reconciled.send()

    trace "sync payload sent",
      server = self.peerManager.switch.peerInfo.peerId,
      client = conn.peerId,
      payload = reconciled.payload

proc initProtocolHandler(self: WakuSync) =
  proc handle(conn: Connection, proto: string) {.async, gcsafe, closure.} =
    debug "sync session requested",
      server = self.peerManager.switch.peerInfo.peerId, client = conn.peerId

    let hashes = (await self.handleLoop(conn)).valueOr:
      debug "sync session ended",
        server = self.peerManager.switch.peerInfo.peerId, client = conn.peerId, error

      #TODO send error code and desc to client
      return

    if hashes.len > 0 and self.transferCallBack.isSome():
      let callback = self.transferCallBack.get()

      (await callback(hashes, conn.peerId)).isOkOr:
        debug "transfer callback failed", error

    debug "sync session ended gracefully",
      server = self.peerManager.switch.peerInfo.peerId, client = conn.peerId

  self.handler = handle
  self.codec = WakuSyncCodec

proc new*(
    T: type WakuSync,
    peerManager: PeerManager,
    maxFrameSize: int = DefaultMaxFrameSize,
    syncInterval: timer.Duration = DefaultSyncInterval,
    relayJitter: Duration = DefaultGossipSubJitter,
    pruneCB: Option[PruneCallBack] = none(PruneCallback),
    transferCB: Option[TransferCallback] = none(TransferCallback),
): Result[T, string] =
  let storage = Storage.new().valueOr:
    return err("negentropy storage creation failed")

  let sync = WakuSync(
    storage: storage,
    peerManager: peerManager,
    maxFrameSize: maxFrameSize,
    syncInterval: syncInterval,
    relayJitter: relayJitter,
    pruneCallBack: pruneCB,
    pruneOffset: syncInterval div 2,
    transferCallBack: transferCB,
  )

  sync.initProtocolHandler()

  info "WakuSync protocol initialized"

  return ok(sync)

proc periodicSync(self: WakuSync, callback: TransferCallback) {.async.} =
  debug "periodic sync initialized", interval = $self.syncInterval

  while true:
    await sleepAsync(self.syncInterval)

    debug "periodic sync started"

    let (hashes, peer) = (await self.sync()).valueOr:
      debug "sync failed", error
      continue

    if hashes.len > 0:
      (await callback(hashes, peer.peerId)).isOkOr:
        debug "transfer callback failed", error
        continue

    debug "periodic sync done", hashSynced = hashes.len

proc periodicPrune(self: WakuSync, callback: PruneCallback) {.async.} =
  debug "periodic prune initialized", interval = $self.syncInterval

  await sleepAsync(self.syncInterval)

  var pruneStop = getNowInNanosecondTime()

  while true:
    await sleepAsync(self.syncInterval)

    debug "periodic prune started",
      startTime = self.pruneStart - self.pruneOffset.nanos,
      endTime = pruneStop,
      storageSize = self.storage.len

    var (elements, cursor) =
      (newSeq[(WakuMessageHash, Timestamp)](0), none(WakuMessageHash))

    var tries = 3
    while true:
      (elements, cursor) = (
        await callback(self.pruneStart - self.pruneOffset.nanos, pruneStop, cursor)
      ).valueOr:
        debug "pruning callback failed", error
        if tries > 0:
          tries -= 1
          await sleepAsync(30.seconds)
          continue
        else:
          break

      if elements.len == 0:
        break

      for (hash, timestamp) in elements:
        self.storage.erase(timestamp, hash).isOkOr:
          trace "storage erase failed", timestamp, hash, error
          continue

      if cursor.isNone():
        break

    self.pruneStart = pruneStop
    pruneStop = getNowInNanosecondTime()

    debug "periodic prune done", storageSize = self.storage.len

proc start*(self: WakuSync) =
  self.started = true
  self.pruneStart = getNowInNanosecondTime()

  if self.transferCallBack.isSome() and self.syncInterval > ZeroDuration:
    self.periodicSyncFut = self.periodicSync(self.transferCallBack.get())

  if self.pruneCallBack.isSome() and self.syncInterval > ZeroDuration:
    self.periodicPruneFut = self.periodicPrune(self.pruneCallBack.get())

  info "WakuSync protocol started"

proc stopWait*(self: WakuSync) {.async.} =
  if self.transferCallBack.isSome() and self.syncInterval > ZeroDuration:
    await self.periodicSyncFut.cancelAndWait()

  if self.pruneCallBack.isSome() and self.syncInterval > ZeroDuration:
    await self.periodicPruneFut.cancelAndWait()

  info "WakuSync protocol stopped"
