#pragma once

#include <stdint.h>

static const uint8_t TX = 37;
static const uint8_t RX = 38;
static const int8_t SDA = -1;
static const int8_t SCL = -1;
static const uint8_t SCK = 21;
static const uint8_t MISO = 23;
static const uint8_t MOSI = 22;
static const uint8_t SS = 20;

#define ETH_PHY_TYPE ETH_PHY_IP101
#define ETH_PHY_ADDR 1
#define ETH_PHY_MDC 31
#define ETH_PHY_MDIO 52
#define ETH_PHY_POWER (-1)
#define ETH_CLK_MODE EMAC_CLK_EXT_IN
#define ETH_RMII_TX_EN 49
#define ETH_RMII_TX0 34
#define ETH_RMII_TX1 35
#define ETH_RMII_RX0 29
#define ETH_RMII_RX1_EN 30
#define ETH_RMII_CRS_DV 28
#define ETH_RMII_CLK 50
