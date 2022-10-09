#pragma once

#include <Arduino.h>
#include <MIDI.h>

#include "../utils.hpp"

#include "./midi.hpp"
#include "./wifi.hpp"
#include "./io.h"

void boot_animation()
{
    repeat(3)
    {
        digitalWrite(LED_1, LOW);
        digitalWrite(LED_2, HIGH);
        delay(200);
        digitalWrite(LED_2, LOW);
        digitalWrite(LED_1, HIGH);
        delay(200);
    }
    repeat(3)
    {
        digitalWrite(LED_1, HIGH);
        digitalWrite(LED_2, HIGH);
        delay(100);
        digitalWrite(LED_1, LOW);
        digitalWrite(LED_2, LOW);
        delay(100);
    }
    digitalWrite(LED_1, HIGH);
    digitalWrite(LED_2, HIGH);
}

void _setup()
{
    pinMode(LED_1, OUTPUT);
    pinMode(LED_2, OUTPUT);

    midi_setup();
    wifi_setup();

    boot_animation();
}

void _loop()
{
    MIDI.read();
}