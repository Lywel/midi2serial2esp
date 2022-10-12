#pragma once

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <espnow.h>

#include "./leds.hpp"
#include "../now_utils.hpp"
#include "./io.h"
#include "./animation.hpp"

wifi_msg_s wifi_msg;

void on_data_recv_slave(uint8_t *addr, uint8_t *data, uint8_t len)
{
    Serial.print(" <<< [");
    print_mac_addr(addr);
    Serial.print("] ");

    // TODO: explorer why this copy would be needed
    memcpy(&wifi_msg, data, len);

    if (wifi_msg.on)
    {
        Serial.println("LED ON");
        leds_on();
        digitalWrite(LED, HIGH);
    }
    else
    {
        Serial.println("LED OFF");
        leds_off();
        digitalWrite(LED, LOW);
    }
}

void wifi_setup()
{
    WiFi.mode(WIFI_STA);

    if (esp_now_init() != 0)
    {
        Serial.println("Error initializing ESP-NOW");
        error_animation();
        ESP.reset();
    }

    Serial.println(WiFi.macAddress());

    esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
    esp_now_register_recv_cb(on_data_recv_slave);
    // esp_now_add_peer(master_mac_addr, ESP_NOW_ROLE_CONTROLLER, 1, NULL, 0);
}
