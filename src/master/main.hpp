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
    // Serial.begin(115200);

    pinMode(LED_1, OUTPUT);
    pinMode(LED_2, OUTPUT);

    midi_setup();
    wifi_setup();

    christmas_tree();
}

void _loop()
{
    MIDI.read();
    /*
    if (((long)millis()) - last > 100)
   {
       go = false;
       Serial.println("Sending message");
       last = millis();

       wifi_msg.on = !wifi_msg.on;
       wifi_msg.target = n++ % 3;
       wifi_msg.color = colors[c++ % 11];
       send = true;
   }
   if (millis() - last_all > 100 * 3 * 15)
   {
       last_all = millis();
       last = millis() + 1500;
       n = 0;

       wifi_msg.on = true;
       wifi_msg.target = -1;
       wifi_msg.color = colors[c % 11];
       send = true;
   }*/
    // if (send)
    // {
    //     esp_now_send(broadcast_mac_addr, (uint8_t *)&wifi_msg, sizeof(wifi_msg));
    // }
}