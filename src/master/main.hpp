#pragma once

#include <Arduino.h>
#include <MIDI.h>

#include "../utils.hpp"

#include "./midi.hpp"
#include "./wifi.hpp"
#include "./io.h"
#include "./animation.hpp"

void _setup()
{
    // Serial print will block exectution if Serial.begin han't been called before
    Serial.begin(115200);
    pinMode(LED_1, OUTPUT);
    pinMode(LED_2, OUTPUT);

    // midi_setup();
    wifi_setup();

    christmas_tree();
}

long last = 0;
void _loop()
{
    // MIDI.read();
    if (millis() - last > 500)
    {
        Serial.println("Sending message");
        last = millis();
        esp_now_send(broadcast_mac_addr, (uint8_t *)&wifi_msg, sizeof(wifi_msg));
        wifi_msg.on = !wifi_msg.on;
    }
}