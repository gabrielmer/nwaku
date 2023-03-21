{.used.}

import
  std/options,
  stew/[results, byteutils],
  testutils/unittests
import
  ../../waku/v2/protocol/waku_enr,
  ./testlib/waku2


suite "Waku ENR -  Capabilities bitfield":
  test "check capabilities support":
    ## Given
    let bitfield: CapabilitiesBitfield = 0b0000_1101u8  # Lightpush, Filter, Relay

    ## Then
    check:
      bitfield.supportsCapability(Capabilities.Relay)
      not bitfield.supportsCapability(Capabilities.Store)
      bitfield.supportsCapability(Capabilities.Filter)
      bitfield.supportsCapability(Capabilities.Lightpush)

  test "bitfield to capabilities list":
    ## Given
    let bitfield = CapabilitiesBitfield.init(
        relay = true,
        store = false,
        lightpush = true,
        filter = true
      )

    ## When
    let caps = bitfield.toCapabilities()

    ## Then
    check:
      caps == @[Capabilities.Relay, Capabilities.Filter, Capabilities.Lightpush]

  test "encode and extract capabilities from record (EnrBuilder ext)":
    ## Given
    let
      enrSeqNum = 1u64
      enrPrivKey = generatesecp256k1key()

    ## When
    var builder = EnrBuilder.init(enrPrivKey, seqNum = enrSeqNum)
    builder.withWakuCapabilities(Capabilities.Relay, Capabilities.Store)

    let recordRes = builder.build()

    ## Then
    check recordRes.isOk()
    let record = recordRes.tryGet()

    let bitfieldRes = record.getCapabilitiesField()
    check bitfieldRes.isOk()

    let bitfield = bitfieldRes.tryGet()
    check:
      bitfield.toCapabilities() == @[Capabilities.Relay, Capabilities.Store]

  test "encode and extract capabilities from record (deprecated)":
    # TODO: Remove after removing the `Record.init()` proc
    ## Given
    let enrkey = generatesecp256k1key()
    let caps = CapabilitiesBitfield.init(Capabilities.Relay, Capabilities.Store)

    let record = Record.init(1, enrkey, wakuFlags=some(caps))

    ## When
    let bitfieldRes = record.getCapabilitiesField()

    ## Then
    check bitfieldRes.isOk()

    let bitfield = bitfieldRes.tryGet()
    check:
      bitfield.toCapabilities() == @[Capabilities.Relay, Capabilities.Store]

  test "cannot extract capabilities from record":
    ## Given
    let
      enrSeqNum = 1u64
      enrPrivKey = generatesecp256k1key()

    let record = EnrBuilder.init(enrPrivKey, enrSeqNum).build().tryGet()

    ## When
    let bitfieldRes = record.getCapabilitiesField()

    ## Then
    check bitfieldRes.isErr()

    let err = bitfieldRes.tryError()
    check:
      err == "Key not found in ENR"

  test "check capabilities on a waku node record":
    ## Given
    let wakuRecord = "-Hy4QC73_E3B_FkZhsOakaD4pHe-U--UoGASdG9N0F3SFFUDY_jdQbud8" &
        "EXVyrlOZ5pZ7VYFBDPMRCENwy87Lh74dFIBgmlkgnY0iXNlY3AyNTZrMaECvNt1jIWbWGp" &
        "AWWdlLGYm1E1OjlkQk3ONoxDC5sfw8oOFd2FrdTID"

    ## When
    var record: Record
    require waku_enr.fromBase64(record, wakuRecord)

    ## Then
    check:
      record.supportsCapability(Relay) == true
      record.supportsCapability(Store) == true
      record.supportsCapability(Filter) == false
      record.supportsCapability(Lightpush) == false
      record.getCapabilities() == @[Capabilities.Relay, Capabilities.Store]

  test "check capabilities on a non-waku node record":
    ## Given
    # non waku enr, i.e. Ethereum one
    let nonWakuEnr = "enr:-KG4QOtcP9X1FbIMOe17QNMKqDxCpm14jcX5tiOE4_TyMrFqbmhPZHK_ZPG2G" &
    "xb1GE2xdtodOfx9-cgvNtxnRyHEmC0ghGV0aDKQ9aX9QgAAAAD__________4JpZIJ2NIJpcIQDE8KdiXNl" &
    "Y3AyNTZrMaEDhpehBDbZjM_L9ek699Y7vhUJ-eAdMyQW_Fil522Y0fODdGNwgiMog3VkcIIjKA"

    ## When
    var nonWakuEnrRecord: Record
    require waku_enr.fromURI(nonWakuEnrRecord, nonWakuEnr)

    ## Then
    check:
      nonWakuEnrRecord.getCapabilities() == []
      nonWakuEnrRecord.supportsCapability(Relay) == false
      nonWakuEnrRecord.supportsCapability(Store) == false
      nonWakuEnrRecord.supportsCapability(Filter) == false
      nonWakuEnrRecord.supportsCapability(Lightpush) == false


suite "Waku ENR - Multiaddresses":

  test "Parse multiaddr field":
    let
      reasonable = "0x000A047F0000010601BADD03".hexToSeqByte()
      reasonableDns4 = ("0x002F36286E6F64652D30312E646F2D616D73332E77616B7576322E746" &
                       "573742E737461747573696D2E6E65740601BBDE03003837316E6F64652D" &
                       "30312E61632D636E2D686F6E676B6F6E672D632E77616B7576322E74657" &
                       "3742E737461747573696D2E6E65740601BBDE030029BD03ADADEC040BE0" &
                       "47F9658668B11A504F3155001F231A37F54C4476C07FB4CC139ED7E30304D2DE03").hexToSeqByte()
      tooLong = "0x000B047F0000010601BADD03".hexToSeqByte()
      tooShort = "0x000A047F0000010601BADD0301".hexToSeqByte()
      gibberish = "0x3270ac4e5011123c".hexToSeqByte()
      empty = newSeq[byte]()

    ## Note: we expect to fail optimistically, i.e. extract
    ## any addresses we can and ignore other errors.
    ## Worst case scenario is we return an empty `multiaddrs` seq.
    check:
      # Expected cases
      reasonable.toMultiAddresses().contains(MultiAddress.init("/ip4/127.0.0.1/tcp/442/ws")[])
      reasonableDns4.toMultiAddresses().contains(MultiAddress.init("/dns4/node-01.do-ams3.wakuv2.test.statusim.net/tcp/443/wss")[])
      # Buffer exceeded
      tooLong.toMultiAddresses().len() == 0
      # Buffer remainder
      tooShort.toMultiAddresses().contains(MultiAddress.init("/ip4/127.0.0.1/tcp/442/ws")[])
      # Gibberish
      gibberish.toMultiAddresses().len() == 0
      # Empty
      empty.toMultiAddresses().len() == 0

  test "Init ENR for Waku Usage":
    # Tests RFC31 encoding "happy path"
    let
      enrIp = ValidIpAddress.init("127.0.0.1")
      enrTcpPort, enrUdpPort = Port(61101)
      enrKey = generateSecp256k1Key()
      multiaddrs = @[MultiAddress.init("/ip4/127.0.0.1/tcp/442/ws")[],
                     MultiAddress.init("/ip4/127.0.0.1/tcp/443/wss")[]]

    let
      record = enr.Record.init(1, enrKey, some(enrIp),
                       some(enrTcpPort), some(enrUdpPort),
                       none(CapabilitiesBitfield),
                       multiaddrs)
      typedRecord = record.toTyped().get()

    # Check EIP-778 ENR fields
    check:
      @(typedRecord.secp256k1.get()) == enrKey.getPublicKey()[].getRawBytes()[]
      ipv4(typedRecord.ip.get()) == enrIp
      Port(typedRecord.tcp.get()) == enrTcpPort
      Port(typedRecord.udp.get()) == enrUdpPort

    # Check Waku ENR fields
    let decodedAddrs = record.get(MultiaddrEnrField, seq[byte]).tryGet().toMultiAddresses()
    check:
      decodedAddrs.contains(MultiAddress.init("/ip4/127.0.0.1/tcp/442/ws")[])
      decodedAddrs.contains(MultiAddress.init("/ip4/127.0.0.1/tcp/443/wss")[])

  test "Strip multiaddr peerId":
    # Tests that peerId is stripped of multiaddrs as per RFC31
    let
      enrIp = ValidIpAddress.init("127.0.0.1")
      enrTcpPort, enrUdpPort = Port(61102)
      enrKey = generateSecp256k1Key()
      multiaddrs = @[MultiAddress.init("/ip4/127.0.0.1/tcp/443/wss/p2p/16Uiu2HAm4v86W3bmT1BiH6oSPzcsSr31iDQpSN5Qa882BCjjwgrD")[]]

    let
      record = enr.Record.init(1, enrKey, some(enrIp),
                       some(enrTcpPort), some(enrUdpPort),
                       none(CapabilitiesBitfield),
                       multiaddrs)

    # Check Waku ENR fields
    let
      decodedAddrs = record.get(MULTIADDR_ENR_FIELD, seq[byte])[].toMultiAddresses()

    check decodedAddrs.contains(MultiAddress.init("/ip4/127.0.0.1/tcp/443/wss")[]) # Peer Id has been stripped

  test "Decode ENR with multiaddrs field":
    let
      # Known values correspond to shared test vectors with other Waku implementations
      knownIp = ValidIpAddress.init("18.223.219.100")
      knownUdpPort = some(9000.uint16)
      knownTcpPort = none(uint16)
      knownMultiaddrs = @[MultiAddress.init("/dns4/node-01.do-ams3.wakuv2.test.statusim.net/tcp/443/wss")[],
                          MultiAddress.init("/dns6/node-01.ac-cn-hongkong-c.wakuv2.test.statusim.net/tcp/443/wss")[]]
      knownEnr = "enr:-QEnuEBEAyErHEfhiQxAVQoWowGTCuEF9fKZtXSd7H_PymHFhGJA3rGAYDVSH" &
                  "KCyJDGRLBGsloNbS8AZF33IVuefjOO6BIJpZIJ2NIJpcIQS39tkim11bHRpYWRkcn" &
                  "O4lgAvNihub2RlLTAxLmRvLWFtczMud2FrdXYyLnRlc3Quc3RhdHVzaW0ubmV0BgG" &
                  "73gMAODcxbm9kZS0wMS5hYy1jbi1ob25na29uZy1jLndha3V2Mi50ZXN0LnN0YXR1" &
                  "c2ltLm5ldAYBu94DACm9A62t7AQL4Ef5ZYZosRpQTzFVAB8jGjf1TER2wH-0zBOe1" &
                  "-MDBNLeA4lzZWNwMjU2azGhAzfsxbxyCkgCqq8WwYsVWH7YkpMLnU2Bw5xJSimxKav-g3VkcIIjKA"

    var enrRecord: Record
    check:
      enrRecord.fromURI(knownEnr)

    let typedRecord = enrRecord.toTyped().get()

     # Check EIP-778 ENR fields
    check:
      ipv4(typedRecord.ip.get()) == knownIp
      typedRecord.tcp == knownTcpPort
      typedRecord.udp == knownUdpPort

    # Check Waku ENR fields
    let
      decodedAddrs = enrRecord.get(MULTIADDR_ENR_FIELD, seq[byte])[].toMultiAddresses()

    for knownMultiaddr in knownMultiaddrs:
      check decodedAddrs.contains(knownMultiaddr)

