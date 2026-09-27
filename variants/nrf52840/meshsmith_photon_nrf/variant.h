#pragma once

#include "WVariant.h"

#define VARIANT_MCK (64000000ul)
#define USE_LFXO
#define PINS_COUNT 33
#define NUM_DIGITAL_PINS 33
#define NUM_ANALOG_INPUTS 8
#define NUM_ANALOG_OUTPUTS 0
#define ADC_RESOLUTION 12

#define PIN_A0 0
#define PIN_A1 1
#define PIN_A2 2
#define PIN_A3 3
#define PIN_A4 4
#define PIN_A5 5
static const uint8_t A0 = PIN_A0;
static const uint8_t A1 = PIN_A1;
static const uint8_t A2 = PIN_A2;
static const uint8_t A3 = PIN_A3;
static const uint8_t A4 = PIN_A4;
static const uint8_t A5 = PIN_A5;

#define LED_STATE_ON 0
#define PIN_LED1 13
#define PIN_LED2 12
#define PIN_LED3 11
// D0 is the radio interrupt, not an available user button.
#define HAS_BUTTON 0

#define HAS_GPS 1
#define GPS_RX_PIN 7
#define GPS_TX_PIN 6
#define GPS_BAUDRATE 115200
#define PIN_SERIAL1_RX GPS_RX_PIN
#define PIN_SERIAL1_TX GPS_TX_PIN
#define PIN_SERIAL2_RX (-1)
#define PIN_SERIAL2_TX (-1)

#define USE_SX1262
#ifndef USERPREFS_LORACONFIG_TX_POWER
#define USERPREFS_LORACONFIG_TX_POWER 18
#endif
#define SX126X_CS 3
#define SX126X_DIO1 0
#define SX126X_RESET 1
#define SX126X_BUSY 2
#define SX126X_DIO2_AS_RF_SWITCH
#define SX126X_DIO3_TCXO_VOLTAGE 1.8

#define SPI_INTERFACES_COUNT 1
#define PIN_SPI_MISO 9
#define PIN_SPI_MOSI 10
#define PIN_SPI_SCK 8
static const uint8_t SS = SX126X_CS;
static const uint8_t MOSI = PIN_SPI_MOSI;
static const uint8_t MISO = PIN_SPI_MISO;
static const uint8_t SCK = PIN_SPI_SCK;

#define WIRE_INTERFACES_COUNT 1
#define PIN_WIRE_SDA 4
#define PIN_WIRE_SCL 5
static const uint8_t SDA = PIN_WIRE_SDA;
static const uint8_t SCL = PIN_WIRE_SCL;

// Battery voltage and state of charge come from the auto-detected MAX17048 on
// Wire. Keep USB power detection without falling back to the XIAO battery ADC.
#define NRF_APM
#define HICHG 22
