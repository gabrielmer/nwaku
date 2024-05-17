when (NimMajor, NimMinor) < (1, 4):
  {.push raises: [Defect].}
else:
  {.push raises: [].}

import
  std/[sets, tables, strutils, sequtils, options, strformat],
  chronos/timer,
  chronicles,
  results

import ./tester_message

type
  StatHelper = object
    prevIndex: uint32
    prevArrivedAt: Moment
    lostIndicies: HashSet[uint32]
    seenIndicies: HashSet[uint32]

  Statistics* = object
    allMessageCount*: uint32
    receivedMessages*: uint32
    misorderCount*: uint32
    duplicateCount*: uint32
    minLatency*: Duration
    maxLatency*: Duration
    cummulativeLatency: Duration
    helper: StatHelper

  PerPeerStatistics* = Table[string, Statistics]

proc init*(T: type Statistics, expectedMessageCount: int = 1000): T =
  result.helper.prevIndex = 0
  result.helper.seenIndicies.init(expectedMessageCount)
  return result

proc addMessage*(self: var Statistics, msg: ProtocolTesterMessage) =
  if self.allMessageCount == 0:
    self.allMessageCount = msg.count
  elif self.allMessageCount != msg.count:
    warn "Message count mismatch at message",
      index = msg.index, expected = self.allMessageCount, got = msg.count

  if not self.helper.seenIndicies.contains(msg.index):
    self.helper.seenIndicies.incl(msg.index)
  else:
    inc(self.duplicateCount)
    warn "Duplicate message", index = msg.index
    ## just do not count into stats
    return

  ## detect misorder arrival and possible lost messages
  if self.helper.prevIndex + 1 < msg.index:
    inc(self.misorderCount)
    warn "Misordered message arrival",
      index = msg.index, expected = self.helper.prevIndex + 1

    ## collect possible lost message indicies
    for idx in self.helper.prevIndex + 1 ..< msg.index:
      self.helper.lostIndicies.incl(idx)

  ## may remove late arrival
  self.helper.lostIndicies.excl(msg.index)

  ## calculate latency
  let currentArrivedAt = Moment.now()
  let delaySincePrevArrived = self.helper.prevArrivedAt - currentArrivedAt

  let expectedDelay = nanos(msg.sincePrev)

  let latency = delaySincePrevArrived - expectedDelay
  self.helper.prevArrivedAt = currentArrivedAt
  self.helper.prevIndex = msg.index

  inc(self.receivedMessages)

  if self.minLatency.isZero or (latency < self.minLatency and latency > nanos(0)):
    self.minLatency = latency
  if latency > self.maxLatency:
    self.maxLatency = latency

  self.cummulativeLatency += latency

proc addMessage*(
    self: var PerPeerStatistics, peerId: string, msg: ProtocolTesterMessage
) =
  if not self.contains(peerId):
    self[peerId] = Statistics.init()

  discard catch:
    self[peerId].addMessage(msg)

proc lossCount*(self: Statistics): uint32 =
  self.allMessageCount - self.receivedMessages

proc averageLatency*(self: Statistics): Duration =
  if self.receivedMessages == 0:
    return nanos(0)
  return self.cummulativeLatency div self.receivedMessages

proc echoStat*(self: Statistics) =
  let printable = catch:
    """*----------------------------------------------------------------*
|  Expected  |  Reveived  |    Loss    |  Misorder  |  Duplicate |
|{self.allMessageCount:>11} |{self.receivedMessages:>11} |{self.lossCount():>11} |{self.misorderCount:>11} |{self.duplicateCount:>11} |
*----------------------------------------------------------------*
| Latency stat:                                                  |
|    avg latency: {self.averageLatency():<47}|
|    min latency: {self.maxLatency:<47}|
|    max latency: {self.minLatency:<47}|
*----------------------------------------------------------------*""".fmt()

  if printable.isErr:
    echo "Error while printing statistics"
  else:
    echo printable.get()

proc jsonStat*(self: Statistics): string =
  let json = catch:
    """{{\"expected\":{self.allMessageCount},
         \"received\": {self.receivedMessages},
         \"loss\": {self.lossCount()},
         \"misorder\": {self.misorderCount},
         \"duplicate\": {self.duplicateCount},
         \"latency\":
           {{\"avg\": {self.averageLatency()},
             \"min\": {self.minLatency},
             \"max\": {self.maxLatency}
           }}
     }}""".fmt()
  if json.isErr:
    return "{\"result:\": \"" & json.error.msg & "\"}"

  return json.get()

proc echoStats*(self: var PerPeerStatistics) =
  for peerId, stats in self.pairs:
    let peerLine = catch:
      "Receiver statistics from peer {peerId}".fmt()
    if peerLine.isErr:
      echo "Error while printing statistics"
    else:
      echo peerLine.get()
      stats.echoStat()

proc jsonStats*(self: var PerPeerStatistics): string =
  try:
    #!fmt: off
    var json = "{\"statitics\": ["
    for peerId, stats in self.pairs:
      json.add("{{\"sender\": \"{peerId}\", \"stat\":".fmt())
      json.add(stats.jsonStat())
      json.add("}, ")
    json.add("]}")
    return json
    #!fmt: on
  except CatchableError:
    return
      "{\"result:\": \"Error while generating json stats: " & getCurrentExceptionMsg() &
      "\"}"

proc checkIfAllMessagesReceived*(self: PerPeerStatistics): bool =
  # if there are no peers have sent messages, assume we just have started.
  if self.len == 0:
    return false

  for stat in self.values:
    if (stat.allMessageCount == 0 and stat.receivedMessages == 0) or
        stat.receivedMessages < stat.allMessageCount:
      return false

  return true
