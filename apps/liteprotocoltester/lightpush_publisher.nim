import
  std/strformat,
  system/ansi_c,
  chronicles,
  chronos,
  stew/byteutils,
  stew/results,
  json_serialization as js
import
  ../../../waku/common/logging,
  ../../../waku/waku_node,
  ../../../waku/node/peer_manager,
  ../../../waku/waku_core,
  ../../../waku/waku_lightpush/client,
  ./tester_config,
  ./tester_message

proc prepareMessage(
    sender: string,
    messageIndex, numMessages: uint32,
    startedAt: TimeStamp,
    prevMessageAt: Timestamp,
    contentTopic: ContentTopic,
): WakuMessage =
  let payload = ProtocolTesterMessage(
    sender: sender,
    index: messageIndex,
    count: numMessages,
    startedAt: startedAt,
    sinceStart: getNowInNanosecondTime() - startedAt,
    sincePrev: getNowInNanosecondTime() - prevMessageAt,
  )

  let text = js.Json.encode(payload)
  let message = WakuMessage(
    payload: toBytes(text), # content of the message
    contentTopic: contentTopic, # content topic to publish to
    ephemeral: true, # tell store nodes to not store it
    timestamp: getNowInNanosecondTime(), # current timestamp
  )

  return message

proc publishMessages(
    wakuNode: WakuNode,
    lightpushPubsubTopic: PubsubTopic,
    lightpushContentTopic: ContentTopic,
    numMessages: uint32,
    delayMessages: Duration,
) {.async.} =
  let startedAt = getNowInNanosecondTime()
  var prevMessageAt = startedAt
  var failedToSendCount: uint32 = 0

  let selfPeerId = $wakuNode.switch.peerInfo.peerId

  var messagesSent: uint32 = 1
  while numMessages >= messagesSent:
    let message = prepareMessage(
      selfPeerId, messagesSent, numMessages, startedAt, prevMessageAt,
      lightpushContentTopic,
    )
    prevMessageAt = getNowInNanosecondTime()
    let wlpRes = await wakuNode.lightpushPublish(some(lightpushPubsubTopic), message)

    if wlpRes.isOk():
      info "published message using lightpush",
        index = messagesSent, count = numMessages
    else:
      error "failed to publish message using lightpush", err = wlpRes.error()
      inc(failedToSendCount)

    await sleepAsync(delayMessages) # Publish every 5 seconds
    inc(messagesSent)

  let report = catch:
    """*----------------------------------------*
|  Expected  |    Sent    |    Failed    |
|{numMessages:>11} |{messagesSent-failedToSendCount:>11} |{failedToSendCount:>11} |
*----------------------------------------*""".fmt()

  if report.isErr:
    echo "Error while printing statistics"
  else:
    echo report.get()

  discard c_raise(ansi_c.SIGTERM)

proc setupAndPublish*(wakuNode: WakuNode, conf: LiteProtocolTesterConf) =
  if wakuNode.wakuLightpushClient == nil:
    error "WakuFilterClient not initialized"
    return

  info "Start sending messages to service node using lightpush"

  # Start maintaining subscription
  asyncSpawn publishMessages(
    wakuNode,
    conf.pubsubTopics[0],
    conf.contentTopics[0],
    conf.numMessages,
    conf.delayMessages.milliseconds,
  )
