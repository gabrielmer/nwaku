{.used.}

import
  std/tempfiles,
  stew/shims/net as stewNet,
  stew/results,
  testutils/unittests,
  chronos,
  libp2p/switch,
  libp2p/protocols/pubsub/pubsub,
  eth/keys

from std/times import epochTime

import
  ../../../tools/rln_keystore_generator/rln_keystore_generator,
  ../../../waku/[
    node/waku_node,
    node/peer_manager,
    waku_core,
    waku_node,
    waku_rln_relay,
    waku_rln_relay/protocol_types,
    waku_keystore/keystore,
  ],
  ../waku_store/store_utils,
  ../waku_archive/archive_utils,
  ../testlib/[wakucore, wakunode, testasync, futures, common, assertions],
  ../resources/payloads,
  ../waku_rln_relay/[utils_static, utils_onchain],
  ../../../waku/waku_rln_relay/rln

from ../../waku/waku_noise/noise_utils import randomSeqByte
import os

proc addFakeMemebershipToKeystore(
    credentials: IdentityCredential,
    keystorePath: string,
    appInfo: AppInfo,
    rlnRelayEthContractAddress: string,
    password: string,
    membershipIndex: uint,
): IdentityCredential =
  # # We generate a random identity credential (inter-value constrains are not enforced, otherwise we need to load e.g. zerokit RLN keygen)
  # var
  #   idTrapdoor = randomSeqByte(rng[], 32)
  #   idNullifier = randomSeqByte(rng[], 32)
  #   idSecretHash = randomSeqByte(rng[], 32)
  #   idCommitment = randomSeqByte(rng[], 32)
  #   idCredential = IdentityCredential(
  #     idTrapdoor: idTrapdoor,
  #     idNullifier: idNullifier,
  #     idSecretHash: idSecretHash,
  #     idCommitment: idCommitment,
  #   )

  var
    contract = MembershipContract(chainId: "1337", address: rlnRelayEthContractAddress)
    index = MembershipIndex(membershipIndex)

  let
    membershipCredential = KeystoreMembership(
      membershipContract: contract, treeIndex: index, identityCredential: credentials
    )
    persistRes = addMembershipCredentials(
      path = keystorePath,
      membership = membershipCredential,
      password = password,
      appInfo = appInfo,
    )

  assert persistRes.isOk()
  return credentials

proc getWakuRlnConfigOnChain*(
    keystorePath: string,
    appInfo: AppInfo,
    rlnRelayEthContractAddress: string,
    password: string,
    credIndex: uint,
): WakuRlnConfig =
  # let
  #   # probably not needed
  #   # rlnInstance = createRlnInstance(
  #   #     tree_path = genTempPath("rln_tree", "group_manager_onchain")
  #   #   )
  #   #   .expect("Couldn't create RLN instance")
  #   keystoreRes = createAppKeystore(keystorePath, appInfo)

  # assert keystoreRes.isOk()

  # return WakuRlnConfig(
  #   rlnRelayEthClientAddress: EthClient,
  #   rlnRelayDynamic: true,
  #   # rlnRelayCredIndex: some(credIndex), # only needed to manually be set static
  #   rlnRelayCredIndex: some(credIndex), # remove
  #   rlnRelayEthContractAddress: rlnRelayEthContractAddress,
  #   rlnRelayCredPath: keystorePath,
  #   rlnRelayCredPassword: password,
  #   # rlnRelayTreePath: genTempPath("rln_tree", "wakunode_" & $credIndex),
  #   rlnEpochSizeSec: 1,
  # )

  return WakuRlnConfig(
    rlnRelayDynamic: true,
    rlnRelayCredIndex: some(credIndex),
    rlnRelayEthContractAddress: rlnRelayEthContractAddress,
    rlnRelayEthClientAddress: EthClient,
    rlnRelayCredPath: keystorePath,
    rlnRelayCredPassword: password,
    rlnRelayTreePath: genTempPath("rln_tree", "wakunode_" & $credIndex),
    rlnEpochSizeSec: 1,
  )

proc setupRelayWithOnChainRln*(
    node: WakuNode, pubsubTopics: seq[string], wakuRlnConfig: WakuRlnConfig
) {.async.} =
  await node.mountRelay(pubsubTopics)
  await node.mountRlnRelay(wakuRlnConfig)

suite "Waku RlnRelay - End to End - Static":
  var
    pubsubTopic {.threadvar.}: PubsubTopic
    contentTopic {.threadvar.}: ContentTopic

  var
    server {.threadvar.}: WakuNode
    client {.threadvar.}: WakuNode

  var
    serverRemotePeerInfo {.threadvar.}: RemotePeerInfo
    clientPeerId {.threadvar.}: PeerId

  asyncSetup:
    pubsubTopic = DefaultPubsubTopic
    contentTopic = DefaultContentTopic

    let
      serverKey = generateSecp256k1Key()
      clientKey = generateSecp256k1Key()

    server = newTestWakuNode(serverKey, ValidIpAddress.init("0.0.0.0"), Port(0))
    client = newTestWakuNode(clientKey, ValidIpAddress.init("0.0.0.0"), Port(0))

    await allFutures(server.start(), client.start())

    serverRemotePeerInfo = server.switch.peerInfo.toRemotePeerInfo()
    clientPeerId = client.switch.peerInfo.toRemotePeerInfo().peerId

  asyncTeardown:
    await allFutures(client.stop(), server.stop())

  suite "Mount":
    asyncTest "Can't mount if relay is not mounted":
      # Given Relay and RLN are not mounted
      check:
        server.wakuRelay == nil
        server.wakuRlnRelay == nil

      # When RlnRelay is mounted
      let catchRes = catch:
        await server.setupStaticRln(1)

      # Then Relay and RLN are not mounted,and the process fails
      check:
        server.wakuRelay == nil
        server.wakuRlnRelay == nil
        catchRes.error()[].msg ==
          "WakuRelay protocol is not mounted, cannot mount WakuRlnRelay"

    asyncTest "Pubsub topics subscribed before mounting RlnRelay are added to it":
      # Given the node enables Relay and Rln while subscribing to a pubsub topic
      await server.setupRelayWithStaticRln(1.uint, @[pubsubTopic])
      await client.setupRelayWithStaticRln(2.uint, @[pubsubTopic])
      check:
        server.wakuRelay != nil
        server.wakuRlnRelay != nil
        client.wakuRelay != nil
        client.wakuRlnRelay != nil

      # And the nodes are connected
      await client.connectToNodes(@[serverRemotePeerInfo])

      # And the node registers the completion handler
      var completionFuture = subscribeCompletionHandler(server, pubsubTopic)

      # When the client sends a valid RLN message
      let isCompleted1 =
        await sendRlnMessage(client, pubsubTopic, contentTopic, completionFuture)

      # Then the valid RLN message is relayed
      check:
        isCompleted1
        completionFuture.read()

      # When the client sends an invalid RLN message
      completionFuture = newBoolFuture()
      let isCompleted2 = await sendRlnMessageWithInvalidProof(
        client, pubsubTopic, contentTopic, completionFuture
      )

      # Then the invalid RLN message is not relayed
      check:
        not isCompleted2

    asyncTest "Pubsub topics subscribed after mounting RlnRelay are added to it":
      # Given the node enables Relay and Rln without subscribing to a pubsub topic
      await server.setupRelayWithStaticRln(1.uint, @[])
      await client.setupRelayWithStaticRln(2.uint, @[])

      # And the nodes are connected
      await client.connectToNodes(@[serverRemotePeerInfo])

      # await sleepAsync(FUTURE_TIMEOUT)
      # And the node registers the completion handler
      var completionFuture = subscribeCompletionHandler(server, pubsubTopic)

      await sleepAsync(FUTURE_TIMEOUT)
      # When the client sends a valid RLN message
      let isCompleted1 =
        await sendRlnMessage(client, pubsubTopic, contentTopic, completionFuture)

      # Then the valid RLN message is relayed
      check:
        isCompleted1
        completionFuture.read()

      # When the client sends an invalid RLN message
      completionFuture = newBoolFuture()
      let isCompleted2 = await sendRlnMessageWithInvalidProof(
        client, pubsubTopic, contentTopic, completionFuture
      )

      # Then the invalid RLN message is not relayed
      check:
        not isCompleted2

  suite "Analysis of Bandwith Limitations":
    asyncTest "Valid Payload Sizes":
      # Given the node enables Relay and Rln while subscribing to a pubsub topic
      await server.setupRelayWithStaticRln(1.uint, @[pubsubTopic])
      await client.setupRelayWithStaticRln(2.uint, @[pubsubTopic])

      # And the nodes are connected
      await client.connectToNodes(@[serverRemotePeerInfo])

      # Register Relay Handler
      var completionFut = newPushHandlerFuture()
      proc relayHandler(
          topic: PubsubTopic, msg: WakuMessage
      ): Future[void] {.async, gcsafe.} =
        if topic == pubsubTopic:
          completionFut.complete((topic, msg))

      let subscriptionEvent = (kind: PubsubSub, topic: pubsubTopic)
      server.subscribe(subscriptionEvent, some(relayHandler))
      await sleepAsync(FUTURE_TIMEOUT)

      # Generate Messages
      let
        epoch = epochTime()
        payload1b = getByteSequence(1)
        payload1kib = getByteSequence(1024)
        overhead: uint64 = 419
        payload150kib = getByteSequence((150 * 1024) - overhead)
        payload150kibPlus = getByteSequence((150 * 1024) - overhead + 1)

      var
        message1b = WakuMessage(payload: @payload1b, contentTopic: contentTopic)
        message1kib = WakuMessage(payload: @payload1kib, contentTopic: contentTopic)
        message150kib = WakuMessage(payload: @payload150kib, contentTopic: contentTopic)
        message151kibPlus =
          WakuMessage(payload: @payload150kibPlus, contentTopic: contentTopic)

      doAssert(
        client.wakuRlnRelay
        .appendRLNProof(
          message1b, epoch + float64(client.wakuRlnRelay.rlnEpochSizeSec * 0)
        )
        .isOk()
      )
      doAssert(
        client.wakuRlnRelay
        .appendRLNProof(
          message1kib, epoch + float64(client.wakuRlnRelay.rlnEpochSizeSec * 1)
        )
        .isOk()
      )
      doAssert(
        client.wakuRlnRelay
        .appendRLNProof(
          message150kib, epoch + float64(client.wakuRlnRelay.rlnEpochSizeSec * 2)
        )
        .isOk()
      )
      doAssert(
        client.wakuRlnRelay
        .appendRLNProof(
          message151kibPlus, epoch + float64(client.wakuRlnRelay.rlnEpochSizeSec * 3)
        )
        .isOk()
      )

      # When sending the 1B message
      discard await client.publish(some(pubsubTopic), message1b)
      discard await completionFut.withTimeout(FUTURE_TIMEOUT_LONG)

      # Then the message is relayed
      check completionFut.read() == (pubsubTopic, message1b)
      # When sending the 1KiB message
      completionFut = newPushHandlerFuture() # Reset Future
      discard await client.publish(some(pubsubTopic), message1kib)
      discard await completionFut.withTimeout(FUTURE_TIMEOUT_LONG)

      # Then the message is relayed
      check completionFut.read() == (pubsubTopic, message1kib)

      # When sending the 150KiB message
      completionFut = newPushHandlerFuture() # Reset Future
      discard await client.publish(some(pubsubTopic), message150kib)
      discard await completionFut.withTimeout(FUTURE_TIMEOUT_LONG)

      # Then the message is relayed
      check completionFut.read() == (pubsubTopic, message150kib)

      # When sending the 150KiB plus message
      completionFut = newPushHandlerFuture() # Reset Future
      discard await client.publish(some(pubsubTopic), message151kibPlus)

      # Then the message is not relayed
      check not await completionFut.withTimeout(FUTURE_TIMEOUT_LONG)

    asyncTest "Invalid Payload Sizes":
      # Given the node enables Relay and Rln while subscribing to a pubsub topic
      await server.setupRelayWithStaticRln(1.uint, @[pubsubTopic])
      await client.setupRelayWithStaticRln(2.uint, @[pubsubTopic])

      # And the nodes are connected
      await client.connectToNodes(@[serverRemotePeerInfo])

      # Register Relay Handler
      var completionFut = newPushHandlerFuture()
      proc relayHandler(
          topic: PubsubTopic, msg: WakuMessage
      ): Future[void] {.async, gcsafe.} =
        if topic == pubsubTopic:
          completionFut.complete((topic, msg))

      let subscriptionEvent = (kind: PubsubSub, topic: pubsubTopic)
      server.subscribe(subscriptionEvent, some(relayHandler))
      await sleepAsync(FUTURE_TIMEOUT)

      # Generate Messages
      let
        epoch = epochTime()
        overhead: uint64 = 419
        payload150kibPlus = getByteSequence((150 * 1024) - overhead + 1)

      var message151kibPlus =
        WakuMessage(payload: @payload150kibPlus, contentTopic: contentTopic)

      doAssert(
        client.wakuRlnRelay
        .appendRLNProof(
          message151kibPlus, epoch + float64(client.wakuRlnRelay.rlnEpochSizeSec * 3)
        )
        .isOk()
      )

      # When sending the 150KiB plus message
      completionFut = newPushHandlerFuture() # Reset Future
      discard await client.publish(some(pubsubTopic), message151kibPlus)

      # Then the message is not relayed
      check not await completionFut.withTimeout(FUTURE_TIMEOUT_LONG)

suite "Waku RlnRelay - End to End - OnChain":
  let runAnvil {.used.} = runAnvil()

  var
    pubsubTopic {.threadvar.}: PubsubTopic
    contentTopic {.threadvar.}: ContentTopic

  var
    server {.threadvar.}: WakuNode
    client {.threadvar.}: WakuNode

  var
    serverRemotePeerInfo {.threadvar.}: RemotePeerInfo
    clientPeerId {.threadvar.}: PeerId

  asyncSetup:
    pubsubTopic = DefaultPubsubTopic
    contentTopic = DefaultContentTopic

    let
      serverKey = generateSecp256k1Key()
      clientKey = generateSecp256k1Key()

    server = newTestWakuNode(serverKey, ValidIpAddress.init("0.0.0.0"), Port(0))
    client = newTestWakuNode(clientKey, ValidIpAddress.init("0.0.0.0"), Port(0))

    await allFutures(server.start(), client.start())

    serverRemotePeerInfo = server.switch.peerInfo.toRemotePeerInfo()
    clientPeerId = client.switch.peerInfo.toRemotePeerInfo().peerId

  asyncTeardown:
    await allFutures(client.stop(), server.stop())

  # asyncTest "No valid contract":
  #   let
  #     invalidContractAddress = "0x0000000000000000000000000000000000000000"
  #     keystorePath =
  #       genTempPath("rln_keystore", "test_wakunode_relay_rln-no_valid_contract")
  #     appInfo = RlnAppInfo
  #     password = "1234"
  #     wakuRlnConfig1 = getWakuRlnConfigOnChain(
  #       keystorePath, appInfo, invalidContractAddress, password, 1
  #     )
  #     wakuRlnConfig2 = getWakuRlnConfigOnChain(
  #       keystorePath, appInfo, invalidContractAddress, password, 2
  #     )
  #     credentials = addFakeMemebershipToKeystore(
  #       keystorePath, appInfo, invalidContractAddress, password, 1
  #     )

  #   # Given the node enables Relay and Rln while subscribing to a pubsub topic
  #   try:
  #     await server.setupRelayWithOnChainRln(@[pubsubTopic], wakuRlnConfig1)
  #     assert false, "Relay should fail mounting when using an invalid contract"
  #   except CatchableError:
  #     assert true

  #   try:
  #     await client.setupRelayWithOnChainRln(@[pubsubTopic], wakuRlnConfig2)
  #     assert false, "Relay should fail mounting when using an invalid contract"
  #   except CatchableError:
  #     assert true

  asyncTest "Valid contract":
    #[
      # Notes
      # Remaining
      Instead of running the idCredentials monkeypatch, passing the correct membershipIndex and keystorePath and keystorePassword should work.
      # Methods
      A) Using the register callback to fetch the correct membership
      B) Using two different keystores, one for each rlnconfig. If there's only one key, it will fetch it regardless of membershipIndex.
      # A
      - Register is not calling callback even though register is happening, this should happen.
      - This command should be working, but it doesn't on the current HEAD of the branch, it does work on master, which suggest there's something wrong with the branch.
      - nim c -r --out:build/onchain -d:chronicles_log_level=NOTICE --verbosity:0 --hints:off  -d:git_version="v0.27.0-rc.0-3-gaa9c30" -d:release --passL:librln_v0.3.7.a --passL:-lm tests/waku_rln_relay/test_rln_group_manager_onchain.nim && onchain_group_test
      - All modified files are tests/*, which is a bit weird. Might be interesting re-creating the branch slowly, and checking out why this is happening.
      # B
      Haven't tried this approach.
    ]#

    echo "# 1"
    let
      onChainGroupManager = await setup()
      contractAddress = onChainGroupManager.ethContractAddress
      keystorePath =
        genTempPath("rln_keystore", "test_wakunode_relay_rln-valid_contract")
      appInfo = RlnAppInfo
      password = "1234"

    let keystoreRes = createAppKeystore(keystorePath, appInfo)
    assert keystoreRes.isOk()

    # TODO: how do I register creds or groupmanager on contract?

    proc dummyC(registrations: seq[Membership]): Future[void] {.async.} =
      echo "~~~~"
      echo registrations
      echo "~~~~"

    onChainGroupManager.onRegister(dummyC)

    let rlnInstance = onChainGroupManager.rlnInstance

    # Generate configs before registering the credentials. Otherwise the file gets cleared up.
    let
      wakuRlnConfig1 =
        getWakuRlnConfigOnChain(keystorePath, appInfo, contractAddress, password, 0)
      wakuRlnConfig2 =
        getWakuRlnConfigOnChain(keystorePath, appInfo, contractAddress, password, 1)

    let
      credentialRes1 = rlnInstance.membershipKeyGen()
      credentialRes2 = rlnInstance.membershipKeyGen()

    if credentialRes1.isErr():
      error "failure while generating credentials", error = credentialRes1.error
      quit(1)

    if credentialRes2.isErr():
      error "failure while generating credentials", error = credentialRes2.error
      quit(1)

    let
      idCredential1 = credentialRes1.get()
      idCredential2 = credentialRes2.get()

    echo "-: ", idCredential1.idCommitment.toUInt256()
    discard await onChainGroupManager.init()
    echo "#~~~~~~~~~~~~~~~~~~~#"
    try:
      await onChainGroupManager.register(idCredential1)
      await onChainGroupManager.register(idCredential2)
      await sleepAsync(5.seconds)
      echo "#~~~~~~~~~~~~~~~~~~~#"
    except Exception:
      assert false, "Failed to register credentials: " & getCurrentExceptionMsg()

    let
      credentialIndex1 = onChainGroupManager.membershipIndex.get()
      credentialIndex2 = credentialIndex1 + 1
    echo "-----------", credentialIndex1
    let
      credentials1 = addFakeMemebershipToKeystore(
        idCredential1, keystorePath, appInfo, contractAddress, password,
        credentialIndex1,
      )
      credentials2 = addFakeMemebershipToKeystore(
        idCredential2, keystorePath, appInfo, contractAddress, password,
        credentialIndex2,
      )

    await onChainGroupManager.stop()
    # let
    #   contractAddress = $(await uploadRLNContract(EthClient))
    #   keystorePath =
    #     genTempPath("rln_keystore", "test_wakunode_relay_rln-no_valid_contract")
    #   appInfo = RlnAppInfo
    #   password = "1234"
    #   wakuRlnConfig1 =
    #     getWakuRlnConfigOnChain(keystorePath, appInfo, contractAddress, password, 1)
    #   wakuRlnConfig2 =
    #     getWakuRlnConfigOnChain(keystorePath, appInfo, contractAddress, password, 2)
    #   credentials = addFakeMemebershipToKeystore(
    #     keystorePath, appInfo, contractAddress, password, 1
    #   )
    # echo "######################"

    # let
    #   rlnInstance = createRlnInstance(
    #       tree_path = genTempPath("rln_tree", "group_manager_onchain")
    #     )
    #     .expect("Couldn't create RLN instance")
    #   keystoreRes = createAppKeystore(keystorePath, appInfo)
    # var idCredential = generateCredentials(rlnInstance)
    # assert keystoreRes.isOk()

    # let wakuRlnConfig1 = WakuRlnConfig(
    #   rlnRelayEthClientAddress: EthClient,
    #   rlnRelayDynamic: true,
    #   rlnRelayCredIndex: some(MembershipIndex(1)),
    #   rlnRelayEthContractAddress: contractAddress,
    #   rlnRelayCredPath: keystorePath,
    #   rlnRelayCredPassword: password,
    #   rlnRelayTreePath: genTempPath("rln_tree", "wakunode_" & $1),
    #   rlnEpochSizeSec: 1,
    # )
    # let wakuRlnConfig2 = WakuRlnConfig(
    #   rlnRelayEthClientAddress: EthClient,
    #   rlnRelayDynamic: true,
    #   rlnRelayCredIndex: some(MembershipIndex(2)),
    #   rlnRelayEthContractAddress: contractAddress,
    #   rlnRelayCredPath: keystorePath,
    #   rlnRelayCredPassword: password,
    #   rlnRelayTreePath: genTempPath("rln_tree", "wakunode_" & $2),
    #   rlnEpochSizeSec: 1,
    # )

    # var
    #   contract = MembershipContract(chainId: "5", address: contractAddress)
    #   index = MembershipIndex(1)

    # let
    #   membershipCredential = KeystoreMembership(
    #     membershipContract: contract, treeIndex: index, identityCredential: idCredential
    #   )
    #   keystoreRes2 = addMembershipCredentials(
    #     path = keystorePath,
    #     membership = membershipCredential,
    #     password = password,
    #     appInfo = appInfo,
    #   )

    # assert keystoreRes2.isOk()

    # echo "######################"

    echo "sleep2a"
    # await sleepAsync(30.seconds)
    echo "sleep2b"

    echo "# 2"
    # Given the node enables Relay and Rln while subscribing to a pubsub topic
    await server.setupRelayWithOnChainRln(@[pubsubTopic], wakuRlnConfig1)
    echo "# 3"
    await client.setupRelayWithOnChainRln(@[pubsubTopic], wakuRlnConfig2)
    echo "# 4"

    # proc generateCallback(
    #     futs: TestGroupSyncFuts, credentials: seq[IdentityCredential]
    # ): OnRegisterCallback =
    #   var futureIndex = 0
    #   proc callback(registrations: seq[Membership]): Future[void] {.async.} =
    #     when defined(rln_v2):
    #       if registrations.len == 1 and
    #           registrations[0].rateCommitment ==
    #           getRateCommitment(credentials[futureIndex], UserMessageLimit(1)) and
    #           registrations[0].index == MembershipIndex(futureIndex):
    #         futs[futureIndex].complete()
    #         futureIndex += 1
    #     else:
    #       if registrations.len == 1 and
    #           registrations[0].idCommitment == credentials[futureIndex].idCommitment and
    #           registrations[0].index == MembershipIndex(futureIndex):
    #         futs[futureIndex].complete()
    #         futureIndex += 1

    #   return callback

    # type TestGroupSyncFuts = array[2, Future[void]]
    # var futures: TestGroupSyncFuts
    # for i in 0 ..< futures.len():
    #   futures[i] = newFuture[void]()
    var
      future1 = newFuture[void]()
      future2 = newFuture[void]()

    proc callback1(registrations: seq[Membership]): Future[void] {.async.} =
      echo "~~~1"
      echo registrations
      echo "###"
      future1.complete()

    proc callback2(registrations: seq[Membership]): Future[void] {.async.} =
      echo "~~~2"
      echo registrations
      echo "###"
      future2.complete()

    echo "# 5"
    try:
      server.wakuRlnRelay.groupManager.onRegister(
        callback1 # generateCallback(@[future2], @[credentials2])
      )
      client.wakuRlnRelay.groupManager.onRegister(
        callback2 # generateCallback(@[future1], @[credentials1])
      )
      echo "# 5a"
      (await server.wakuRlnRelay.groupManager.startGroupSync()).isOkOr:
        raiseAssert $error
      echo "# 5b"
      (await client.wakuRlnRelay.groupManager.startGroupSync()).isOkOr:
        raiseAssert $error

      echo "# 6"
      # for i in 0 ..< credentials.len():
      # when defined(rln_v2):
      #   await client.wakuRlnRelay.groupManager.register(
      #     @[credentials1], UserMessageLimit(1)
      #   )
      #   await server.wakuRlnRelay.groupManager.register(
      #     @[credentials2], UserMessageLimit(1)
      #   )
      # else:
      # await client.wakuRlnRelay.groupManager.register(credentials1)
      #   await server.wakuRlnRelay.groupManager.register(credentials2)
      # echo server.wakuRlnRelay.groupManager.idCredentials
      # echo client.wakuRlnRelay.groupManager.idCredentials
      # server.wakuRlnRelay.groupManager.idCredentials = some(credentials1)
      # client.wakuRlnRelay.groupManager.idCredentials = some(credentials2)
      echo server.wakuRlnRelay.groupManager.idCredentials
      echo client.wakuRlnRelay.groupManager.idCredentials
      echo "# 7"
    except Exception, CatchableError:
      assert false, "exception raised: " & getCurrentExceptionMsg()

    echo "# 8"
    # await allFutures(@[future1, future2])
    echo "# FUTURES DONE"

    let serverRemotePeerInfo = server.switch.peerInfo.toRemotePeerInfo()

    # And the nodes are connected
    await client.connectToNodes(@[serverRemotePeerInfo])

    # And the node registers the completion handler
    var completionFuture = subscribeCompletionHandler(server, pubsubTopic)
    echo "# 8"
    # When the client sends a valid RLN message
    let isCompleted1 =
      await sendRlnMessage(client, pubsubTopic, contentTopic, completionFuture)
    echo "# 10"
    # Then the valid RLN message is relayed
    check:
      isCompleted1
      completionFuture.read()
    echo "# 11"

  # TODO: This doesn't work, document and remove
  asyncTest "Concept proff without first onChainManager":
    let
      rlnInstance = createRlnInstance(
          tree_path = genTempPath("rln_tree", "group_manager_onchain")
        )
        .get()
      contractAddress = $(await uploadRLNContract(EthClient))
      web3 = await newWeb3(EthClient)
      accounts = await web3.provider.eth_accounts()
    web3.defaultAccount = accounts[0]

    let
      keystorePath =
        genTempPath("rln_keystore", "test_wakunode_relay_rln-valid_contract")
      appInfo = RlnAppInfo
      password = "1234"

    let
      wakuRlnConfig1 =
        getWakuRlnConfigOnChain(keystorePath, appInfo, contractAddress, password, 0)
      wakuRlnConfig2 =
        getWakuRlnConfigOnChain(keystorePath, appInfo, contractAddress, password, 1)

    let
      credentials1 = rlnInstance.membershipKeyGen().get()
      credentials2 = rlnInstance.membershipKeyGen().get()

    echo "-> Creds1: ", $credentials1
    echo "-> Creds2: ", $credentials2

    # Given the node enables Relay and Rln while subscribing to a pubsub topic
    await server.setupRelayWithOnChainRln(@[pubsubTopic], wakuRlnConfig1)
    await client.setupRelayWithOnChainRln(@[pubsubTopic], wakuRlnConfig2)

    echo "# PrivKey1: ",
      OnChainGroupManager(server.wakuRlnRelay.groupManager).ethPrivateKey
    echo "# PrivKey1: ",
      OnChainGroupManager(client.wakuRlnRelay.groupManager).ethPrivateKey

    echo "# CALLBACKS"
    var
      future1 = newFuture[void]()
      future2 = newFuture[void]()

    proc callback1(registrations: seq[Membership]): Future[void] {.async.} =
      echo "~ callback1"
      echo registrations
      future1.complete()

    proc callback2(registrations: seq[Membership]): Future[void] {.async.} =
      echo "~ callback2"
      echo registrations
      future2.complete()

    try:
      server.wakuRlnRelay.groupManager.onRegister(callback1)
      echo "# CB 1"
      client.wakuRlnRelay.groupManager.onRegister(callback2)
      echo "# CB 2"

      await server.wakuRlnRelay.groupManager.register(credentials1)
      echo "# REGISTER 1"
      await client.wakuRlnRelay.groupManager.register(credentials2)
      echo "# REGISTER 2"

      (await server.wakuRlnRelay.groupManager.startGroupSync()).isOkOr:
        raiseAssert $error
      echo "# GROUP SYNC 1"
      (await client.wakuRlnRelay.groupManager.startGroupSync()).isOkOr:
        raiseAssert $error
      echo "# GROUP SYNC 2"
    except Exception, CatchableError:
      assert false, "exception raised: " & getCurrentExceptionMsg()

    await allFutures(@[future1, future2])
    echo "# FUTURES"

  ################################
  ## Terminating/removing Anvil
  ################################

  # We stop Anvil daemon
  stopAnvil(runAnvil)
