#pragma once

#include "./wifi.hpp"
#include "./leds.hpp"
#include "../utils.hpp"
#include "./io.h"
#include "./animation.hpp"

void _setup()
{
    Serial.begin(115200);
    pinMode(LED, OUTPUT);

    wifi_setup();
    leds_setup();

    christmas_tree();
}

void _loop()
{
}
