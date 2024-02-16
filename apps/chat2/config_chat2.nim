import
  chronicles, chronos,
  confutils, confutils/defs, confutils/std/net,
  eth/keys,
  libp2p/crypto/crypto,
  libp2p/crypto/secp,
  nimcrypto/utils,
  std/strutils,
  regex
import
  ../../../waku/waku_core

type
  Fleet* =  enum
    none
    prod
    test
  EthRpcUrl = distinct string
  Chat2Conf* = object
    ## General node config

    logLevel* {.
      desc: "Sets the log level."
      defaultValue: LogLevel.INFO
      name: "log-level" }: LogLevel

    nodekey* {.
      desc: "P2P node private key as 64 char hex string.",
      name: "nodekey" }: Option[crypto.PrivateKey]

    listenAddress* {.
      defaultValue: defaultListenAddress(config)
      desc: "Listening address for the LibP2P traffic."
      name: "listen-address"}: IpAddress

    tcpPort* {.
      desc: "TCP listening port."
      defaultValue: 60000
      name: "tcp-port" }: Port

    udpPort* {.
      desc: "UDP listening port."
      defaultValue: 60000
      name: "udp-port" }: Port

    portsShift* {.
      desc: "Add a shift to all port numbers."
      defaultValue: 0
      name: "ports-shift" }: uint16

    nat* {.
      desc: "Specify method to use for determining public address. " &
            "Must be one of: any, none, upnp, pmp, extip:<IP>."
      defaultValue: "any" }: string

    ## Persistence config

    dbPath* {.
      desc: "The database path for peristent storage",
      defaultValue: ""
      name: "db-path" }: string

    persistPeers* {.
      desc: "Enable peer persistence: true|false",
      defaultValue: false
      name: "persist-peers" }: bool

    persistMessages* {.
      desc: "Enable message persistence: true|false",
      defaultValue: false
      name: "persist-messages" }: bool

    ## Relay config

    relay* {.
      desc: "Enable relay protocol: true|false",
      defaultValue: true
      name: "relay" }: bool

    staticnodes* {.
      desc: "Peer multiaddr to directly connect with. Argument may be repeated."
      name: "staticnode" }: seq[string]

    keepAlive* {.
      desc: "Enable keep-alive for idle connections: true|false",
      defaultValue: false
      name: "keep-alive" }: bool

    topics* {.
      desc: "Default topics to subscribe to (space separated list)."
      defaultValue: "/waku/2/default-waku/proto"
      name: "topics" .}: string

    ## Store config

    store* {.
      desc: "Enable store protocol: true|false",
      defaultValue: true
      name: "store" }: bool

    storenode* {.
      desc: "Peer multiaddr to query for storage.",
      defaultValue: ""
      name: "storenode" }: string

    ## Filter config

    filter* {.
      desc: "Enable filter protocol: true|false",
      defaultValue: false
      name: "filter" }: bool

    filternode* {.
      desc: "Peer multiaddr to request content filtering of messages.",
      defaultValue: ""
      name: "filternode" }: string

    ## Lightpush config

    lightpush* {.
      desc: "Enable lightpush protocol: true|false",
      defaultValue: false
      name: "lightpush" }: bool

    lightpushnode* {.
      desc: "Peer multiaddr to request lightpush of published messages.",
      defaultValue: ""
      name: "lightpushnode" }: string

    ## JSON-RPC config

    rpc* {.
      desc: "Enable Waku JSON-RPC server: true|false",
      defaultValue: true
      name: "rpc" }: bool

    rpcAddress* {.
      desc: "Listening address of the JSON-RPC server.",
      defaultValue: parseIpAddress("127.0.0.1")
      name: "rpc-address" }: IpAddress

    rpcPort* {.
      desc: "Listening port of the JSON-RPC server.",
      defaultValue: 8545
      name: "rpc-port" }: uint16

    rpcAdmin* {.
      desc: "Enable access to JSON-RPC Admin API: true|false",
      defaultValue: false
      name: "rpc-admin" }: bool

    rpcPrivate* {.
      desc: "Enable access to JSON-RPC Private API: true|false",
      defaultValue: false
      name: "rpc-private" }: bool

    ## Metrics config

    metricsServer* {.
      desc: "Enable the metrics server: true|false"
      defaultValue: false
      name: "metrics-server" }: bool

    metricsServerAddress* {.
      desc: "Listening address of the metrics server."
      defaultValue: parseIpAddress("127.0.0.1")
      name: "metrics-server-address" }: IpAddress

    metricsServerPort* {.
      desc: "Listening HTTP port of the metrics server."
      defaultValue: 8008
      name: "metrics-server-port" }: uint16

    metricsLogging* {.
      desc: "Enable metrics logging: true|false"
      defaultValue: true
      name: "metrics-logging" }: bool

    ## DNS discovery config

    dnsDiscovery* {.
      desc: "Enable discovering nodes via DNS"
      defaultValue: false
      name: "dns-discovery" }: bool

    dnsDiscoveryUrl* {.
      desc: "URL for DNS node list in format 'enrtree://<key>@<fqdn>'",
      defaultValue: ""
      name: "dns-discovery-url" }: string

    dnsDiscoveryNameServers* {.
      desc: "DNS name server IPs to query. Argument may be repeated."
      defaultValue: @[parseIpAddress("1.1.1.1"), parseIpAddress("1.0.0.1")]
      name: "dns-discovery-name-server" }: seq[IpAddress]

    ## Chat2 configuration

    fleet* {.
      desc: "Select the fleet to connect to. This sets the DNS discovery URL to the selected fleet."
      defaultValue: Fleet.prod
      name: "fleet" }: Fleet

    contentTopic* {.
      desc: "Content topic for chat messages."
      defaultValue: "/toy-chat/2/huilong/proto"
      name: "content-topic" }: string

    ## Websocket Configuration
    websocketSupport* {.
      desc: "Enable websocket:  true|false",
      defaultValue: false
      name: "websocket-support"}: bool

    websocketPort* {.
      desc: "WebSocket listening port."
      defaultValue: 8000
      name: "websocket-port" }: Port

    websocketSecureSupport* {.
      desc: "WebSocket Secure Support."
      defaultValue: false
      name: "websocket-secure-support" }: bool

    ## rln-relay configuration

    rlnRelay* {.
      desc: "Enable spam protection through rln-relay: true|false",
      defaultValue: false
      name: "rln-relay" }: bool

    rlnRelayCredPath* {.
      desc: "The path for peristing rln-relay credential",
      defaultValue: ""
      name: "rln-relay-cred-path" }: string

    rlnRelayCredIndex* {.
      desc: "the index of the onchain commitment to use",
      name: "rln-relay-cred-index" }: Option[uint]

    rlnRelayDynamic* {.
      desc: "Enable waku-rln-relay with on-chain dynamic group management: true|false",
      defaultValue: false
      name: "rln-relay-dynamic" }: bool

    rlnRelayIdKey* {.
      desc: "Rln relay identity secret key as a Hex string",
      defaultValue: ""
      name: "rln-relay-id-key" }: string

    rlnRelayIdCommitmentKey* {.
      desc: "Rln relay identity commitment key as a Hex string",
      defaultValue: ""
      name: "rln-relay-id-commitment-key" }: string

    rlnRelayEthClientAddress* {.
      desc: "HTTP address of an Ethereum testnet client e.g., http://localhost:8540/",
      defaultValue: "http://localhost:8540/"
      name: "rln-relay-eth-client-address" }: EthRpcUrl

    rlnRelayEthContractAddress* {.
      desc: "Address of membership contract on an Ethereum testnet",
      defaultValue: ""
      name: "rln-relay-eth-contract-address" }: string

    rlnRelayCredPassword* {.
      desc: "Password for encrypting RLN credentials",
      defaultValue: ""
      name: "rln-relay-cred-password" }: string

    rlnRelayUserMessageLimit* {.
      desc: "Set a user message limit for the rln membership registration. Must be a positive integer. Default is 1.",
      defaultValue: 1,
      name: "rln-relay-user-message-limit" .}: uint64

# NOTE: Keys are different in nim-libp2p
proc parseCmdArg*(T: type crypto.PrivateKey, p: string): T =
  try:
    let key = SkPrivateKey.init(utils.fromHex(p)).tryGet()
    # XXX: Here at the moment
    result = crypto.PrivateKey(scheme: Secp256k1, skkey: key)
  except CatchableError as e:
    raise newException(ValueError, "Invalid private key")

proc completeCmdArg*(T: type crypto.PrivateKey, val: string): seq[string] =
  return @[]

proc parseCmdArg*(T: type IpAddress, p: string): T =
  try:
    result = parseIpAddress(p)
  except CatchableError as e:
    raise newException(ValueError, "Invalid IP address")

proc completeCmdArg*(T: type IpAddress, val: string): seq[string] =
  return @[]

proc parseCmdArg*(T: type Port, p: string): T =
  try:
    result = Port(parseInt(p))
  except CatchableError as e:
    raise newException(ValueError, "Invalid Port number")

proc completeCmdArg*(T: type Port, val: string): seq[string] =
  return @[]

proc parseCmdArg*(T: type Option[uint], p: string): T =
  try:
    some(parseUint(p))
  except CatchableError:
    raise newException(ValueError, "Invalid unsigned integer")

proc completeCmdArg*(T: type EthRpcUrl, val: string): seq[string] =
  return @[]

proc parseCmdArg*(T: type EthRpcUrl, s: string): T =
  ## allowed patterns:
  ## http://url:port
  ## https://url:port
  ## http://url:port/path
  ## https://url:port/path
  ## http://url/with/path
  ## http://url:port/path?query
  ## https://url:port/path?query
  ## disallowed patterns:
  ## any valid/invalid ws or wss url
  var httpPattern = re2"^(https?:\/\/)(?:w{1,3}\.)?[^\s.]+(?:\.[a-z]+)*(?::\d+)?(?![^<]*(?:<\/\w+>|\/?>))"
  var wsPattern =   re2"^(wss?:\/\/)(?:w{1,3}\.)?[^\s.]+(?:\.[a-z]+)*(?::\d+)?(?![^<]*(?:<\/\w+>|\/?>))"
  if regex.match(s, wsPattern):
    raise newException(ValueError, "Websocket RPC URL is not supported, Please use an HTTP URL")
  if not regex.match(s, httpPattern):
    raise newException(ValueError, "Invalid HTTP RPC URL")
  return EthRpcUrl(s)

func defaultListenAddress*(conf: Chat2Conf): IpAddress =
  # TODO: How should we select between IPv4 and IPv6
  # Maybe there should be a config option for this.
  (static parseIpAddress("0.0.0.0"))
