#include <Arduino.h>
#include <MIDI.h>

#include <utils.hpp>

#include "midi.hpp"
#include "wifi.hpp"
#include "io.h"
#include "animation.hpp"

void setup()
{
    // Serial print will block exectution if Serial.begin han't been called before
    // Serial.begin(115200);

    pinMode(LED_1, OUTPUT);
    pinMode(LED_2, OUTPUT);

    midi_setup();
    wifi_setup();

    christmas_tree();
}

void loop()
{
    MIDI.read();
}
