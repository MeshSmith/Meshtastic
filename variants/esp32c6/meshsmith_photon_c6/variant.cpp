#include "variant.h"
#include "Power.h"
#include <Arduino.h>

void earlyInitVariant()
{
    // Enable the XIAO's 2.4 GHz RF switch before selecting its antenna.
    pinMode(3, OUTPUT);
    digitalWrite(3, LOW);
    delay(100);
    pinMode(14, OUTPUT);
    digitalWrite(14, USE_XIAO_ESP32C6_EXTERNAL_ANTENNA ? HIGH : LOW);
}

void lateInitVariant()
{
    // The MAX17048 is discovered after the first Power::setup() call.
    power->setup();
}
