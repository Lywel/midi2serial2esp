#pragma once

#include "./wifi.hpp"
#include "./leds.hpp"
#include "../utils.hpp"
#include "./io.h"
#include "./animation.hpp"

void _setup()
{
#ifdef DEBUG
    Serial.begin(115200);
    // Don't use the led on esp8266-01
    // The data line of the led array is on pin 2
    pinMode(LED, OUTPUT);
#endif

    wifi_setup();
    leds_setup();

#ifdef DEBUG
    christmas_tree();
#endif
}

void _loop()
{
}
