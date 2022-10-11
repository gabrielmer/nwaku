import
  std/[strutils, sequtils, tables],
  confutils,
  chronos,
  stew/shims/net,
  chronicles/topics_registry
import
  libp2p/protocols/ping,
  libp2p/crypto/[crypto, secp]
import
  ../../waku/v2/node/peer_manager/peer_manager,
  ../../waku/v2/utils/peers,
  ../../waku/v2/node/wakunode2,
  ../../waku/v2/node/waku_payload,
  ../../waku/v2/utils/peers

# protocols and their tag
const ProtocolsTable = {
  "store": "/vac/waku/store/",
  "relay": "/vac/waku/relay/",
  "lightpush": "/vac/waku/lightpush/",
  "filter": "/vac/waku/filter/",
}.toTable

# cli flags
type
  WakuCanaryConf* = object
    address* {.
      desc: "Multiaddress of the peer node to attempt to dial",
      defaultValue: "",
      name: "address",
      abbr: "a" }: string

    timeout* {.
      desc: "Timeout to consider that the connection failed",
      defaultValue: chronos.seconds(10),
      name: "timeout",
      abbr: "t" }: chronos.Duration

    protocols* {.
      desc: "Protocol required to be supported: store,relay,lightpush,filter (can be used multiple times)",
      name: "protocol",
      abbr: "p" }: seq[string]

    logLevel* {.
      desc: "Sets the log level",
      defaultValue: LogLevel.DEBUG,
      name: "log-level",
      abbr: "l" .}: LogLevel


proc parseCmdArg*(T: type chronos.Duration, p: TaintedString): T =
  try:
      result = chronos.seconds(parseInt(p))
  except CatchableError as e:
    raise newException(ConfigurationError, "Invalid timeout value")

proc completeCmdArg*(T: type chronos.Duration, val: TaintedString): seq[string] =
  return @[]

# checks if rawProtocols (skipping version) are supported in nodeProtocols
proc areProtocolsSupported(
    rawProtocols: seq[string],
    nodeProtocols: seq[string]): bool =

  var numOfSupportedProt: int = 0

  for nodeProtocol in nodeProtocols:
    for rawProtocol in rawProtocols:
      let protocolTag = ProtocolsTable[rawProtocol]
      if nodeProtocol.startsWith(protocolTag):
        info "Supported protocol ok", expected=protocolTag, supported=nodeProtocol
        numOfSupportedProt += 1
        break

  if numOfSupportedProt == rawProtocols.len:
    return true

  return false

proc main(): Future[int] {.async.} =
  let conf: WakuCanaryConf = WakuCanaryConf.load()

  if conf.logLevel != LogLevel.NONE:
    setLogLevel(conf.logLevel)

  # ensure input protocols are valid
  for p in conf.protocols:
    if p notin ProtocolsTable: 
      error "invalid protocol", protocol=p, valid=ProtocolsTable
      raise newException(ConfigurationError, "Invalid cli flag values" & p)

  info "Cli flags",
    address=conf.address,
    timeout=conf.timeout,
    protocols=conf.protocols,
    logLevel=conf.logLevel

  let
    peer: RemotePeerInfo = parseRemotePeerInfo(conf.address)
    rng = crypto.newRng()
    nodeKey = crypto.PrivateKey.random(Secp256k1, rng[])[]
    node = WakuNode.new(
      nodeKey,
      ValidIpAddress.init("0.0.0.0"),
      Port(60000))

  await node.start()

  let timedOut = not await node.connectToNodes(@[peer]).withTimeout(conf.timeout)
  if timedOut:
    error "Timedout after", timeout=conf.timeout

  let lp2pPeerStore = node.switch.peerStore
  let conStatus = node.peerManager.peerStore.connectionBook[peer.peerId]

  if conStatus in [Connected, CanConnect]:
    let nodeProtocols = lp2pPeerStore[ProtoBook][peer.peerId]
    if not areProtocolsSupported(conf.protocols, nodeProtocols):
      error "Not all protocols are supported", expected=conf.protocols, supported=nodeProtocols
      return 1
  elif conStatus == CannotConnect:
    error "Could not connect", peerId = peer.peerId
    return 1
  return 0

when isMainModule:
  let status = waitFor main()
  if status == 0:
    info "The node is reachable and supports all specified protocols"
  else:
    error "The node has some problems (see logs)"
  quit status
