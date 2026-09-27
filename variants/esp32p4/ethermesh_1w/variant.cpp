#include "configuration.h"

#include "Ethernet.h"
#include "NodeDB.h"
#include "concurrency/Periodic.h"
#include "gps/RTC.h"
#include "main.h"
#include "mesh/api/ethServerAPI.h"
#include "mesh/eth/ethClient.h"
#include <ESPmDNS.h>
#include <atomic>
#include <esp_sntp.h>

EtherMeshEthernet Ethernet;
static NetworkUDP syslogClient;
meshtastic::Syslog syslog(syslogClient);
static std::atomic<bool> timeSynchronized{false};

static int32_t pollEthernet()
{
    // SNTP callbacks run outside the firmware scheduler; adopt the time here.
    if (timeSynchronized.exchange(false)) {
        struct timeval now;
        gettimeofday(&now, nullptr);
        perhapsSetRTC(RTCQualityNTP, &now);
    }
    static uint32_t lastIP = 0;
    uint32_t ip = isEthernetAvailable() ? uint32_t(ETH.localIP()) : 0;
    if (ip == lastIP)
        return 500;

    deInitApiServer();
    MDNS.end();
    syslog.disable();
    lastIP = ip;
    if (ip) {
        LOG_INFO("EtherMesh IP: %s", ETH.localIP().toString().c_str());
        initApiServer();
        if (MDNS.begin("Meshtastic")) {
            MDNS.addService("meshtastic", "tcp", SERVER_API_DEFAULT_PORT);
            MDNS.addServiceTxt("meshtastic", "tcp", "shortname", String(owner.short_name));
            MDNS.addServiceTxt("meshtastic", "tcp", "id", String(nodeDB->getNodeId().c_str()));
        }
        if (config.network.rsyslog_server[0]) {
            String server = config.network.rsyslog_server;
            uint16_t port = 514;
            int delimiter = server.indexOf(':');
            if (delimiter > 0) {
                port = server.substring(delimiter + 1).toInt();
                server = server.substring(0, delimiter);
            }
            // Syslog retains the hostname pointer across calls.
            static String syslogHost;
            syslogHost = server;
            syslog.server(syslogHost.c_str(), port);
            syslog.deviceHostname(getDeviceName());
            syslog.appName("Meshtastic");
            syslog.defaultPriority(LOGLEVEL_USER);
            syslog.enable();
        }
        if (config.network.ntp_server[0])
            configTime(0, 0, config.network.ntp_server);
    }
    return 500;
}

bool initEthernet()
{
    static bool started = false;
    if (started)
        return true;
    if (!config.network.eth_enabled)
        return false;

    pinMode(ETH_PHY_RESET, OUTPUT);
    digitalWrite(ETH_PHY_RESET, LOW);
    delay(50);
    digitalWrite(ETH_PHY_RESET, HIGH);
    delay(50);
    if (!ETH.begin(ETH_PHY_TYPE, ETH_PHY_ADDR, ETH_PHY_MDC, ETH_PHY_MDIO, ETH_PHY_POWER, ETH_CLK_MODE)) {
        LOG_ERROR("EtherMesh Ethernet initialization failed");
        return false;
    }
    ETH.setHostname(getDeviceName());
    if (config.network.address_mode == meshtastic_Config_NetworkConfig_AddressMode_STATIC) {
        if (config.network.ipv4_config.ip == 0)
            LOG_WARN("EtherMesh static IP is empty; using DHCP");
        else if (!ETH.config(config.network.ipv4_config.ip, config.network.ipv4_config.gateway, config.network.ipv4_config.subnet,
                             config.network.ipv4_config.dns))
            LOG_WARN("EtherMesh static IP configuration failed");
    }
    sntp_set_time_sync_notification_cb([](struct timeval *) { timeSynchronized.store(true); });
    new concurrency::Periodic("EtherMesh", pollEthernet);
    started = true;
    return true;
}

bool isEthernetAvailable()
{
    return config.network.eth_enabled && ETH.linkUp() && uint32_t(ETH.localIP()) != 0;
}
