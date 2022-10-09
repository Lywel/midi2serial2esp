#pragma once

#include "./wifi.hpp"
#include "./leds.hpp"
#include "../utils.hpp"

void boot_animation()
{
    repeat(3)
    {
        leds_on();
        delay(500);
        leds_off();
        delay(500);
    }
    repeat(10)
    {
        leds_on();
        delay(50);
        leds_off();
        delay(50);
    }
}

void _setup()
{
    wifi_setup();
    leds_setup();

    boot_animation();
}

void _loop()
{
}
