#pragma once

#include <ETH.h>
#include <NetworkClient.h>
#include <NetworkServer.h>
#include <NetworkUdp.h>

using EthernetClient = NetworkClient;
using EthernetServer = NetworkServer;
using EthernetUDP = NetworkUDP;

enum EthernetLinkStatus { Unknown, LinkON, LinkOFF };

// Compatibility with Meshtastic's wired connection-status and TCP API interfaces.
class EtherMeshEthernet
{
  public:
    EthernetLinkStatus linkStatus() const { return ETH.linkUp() ? LinkON : LinkOFF; }
    IPAddress localIP() const { return ETH.localIP(); }
};

extern EtherMeshEthernet Ethernet;
