#pragma once

#define HAS_GPS 0
#define HAS_WIRE 0
#define HAS_SCREEN 0
#define HAS_BUTTON 0
#define HAS_ETHERNET 1
#define USE_ETHERNET_DEFAULT 1
// The variant's adapter maps the existing wired API onto ESP32 Network sockets.
#define USE_ARDUINO_ETHERNET

#define ETH_PHY_RESET 51

#define USE_SX1262
#define LORA_SCK 21
#define LORA_MISO 23
#define LORA_MOSI 22
#define LORA_CS 20
#define LORA_RESET 26
#define LORA_DIO1 33
#define SX126X_CS LORA_CS
#define SX126X_RESET LORA_RESET
#define SX126X_DIO1 LORA_DIO1
#define SX126X_BUSY 32
#define SX126X_POWER_EN 27
#define SX126X_DIO2_AS_RF_SWITCH
#define SX126X_DIO3_TCXO_VOLTAGE 1.8
#define SX126X_MAX_POWER 22
#define SX126X_PA_RAMP_US 800
#ifndef USERPREFS_LORACONFIG_TX_POWER
#define USERPREFS_LORACONFIG_TX_POWER 18
#endif
