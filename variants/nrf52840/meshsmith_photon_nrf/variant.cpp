#include "variant.h"
#include "Power.h"
#include "wiring_constants.h"
#include "wiring_digital.h"

// XIAO nRF52840 Arduino indices, matching seeed_xiao_nrf52840_kit.
const uint32_t g_ADigitalPinMap[] = {
    2,  3,  28, 29, 4,  5,  43, 44, 45, 46, 47, // D0-D10
    26, 6,  30, 14,                             // LEDs, battery divider enable
    40, 27, 7,  11,                             // IMU
    42, 32, 16,                                 // Microphone
    13, 17,                                     // Charger
    21, 25, 20, 24, 22, 23,                     // QSPI
    9,  10, 31                                  // NFC, battery ADC
};

void initVariant()
{
    // This hook runs before SoftDevice startup; the XIAO has the DC/DC inductor.
    NRF_POWER->DCDCEN = 1;
    pinMode(HICHG, OUTPUT);
    digitalWrite(HICHG, LOW);
    pinMode(PIN_LED1, OUTPUT);
    ledOff(PIN_LED1);
    pinMode(PIN_LED2, OUTPUT);
    ledOff(PIN_LED2);
    pinMode(PIN_LED3, OUTPUT);
    ledOff(PIN_LED3);
}

void lateInitVariant()
{
    // The MAX17048 is discovered after the first Power::setup() call.
    power->setup();
}
