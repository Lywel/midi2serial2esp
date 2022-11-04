#pragma once

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <espnow.h>

#include <utils.hpp>
#include <now_utils.hpp>

#include "./leds.hpp"
#include "./io.h"
#include "./animation.hpp"

wifi_msg_s wifi_msg;

int8 my_id = 2;

void on_data_recv_slave(uint8_t *addr, uint8_t *data, uint8_t len)
{
    PRINT(" <<< [");
    print_mac_addr(addr);
    PRINT("] ");

    // TODO: explorer why this copy would be needed
    memcpy(&wifi_msg, data, len);

    if (wifi_msg.target != my_id && wifi_msg.target != -1)
        return;

    if (wifi_msg.on)
    {
        PRINTLN("LED ON");
        leds_on(wifi_msg.color);
        // digitalWrite(LED, HIGH);
    }
    else
    {
        PRINTLN("LED OFF");
        leds_off();
        // digitalWrite(LED, LOW);
    }
}

void wifi_setup()
{
    WiFi.mode(WIFI_STA);

    if (esp_now_init() != 0)
    {
        PRINTLN("Error initializing ESP-NOW");
        error_animation();
        ESP.reset();
    }

    PRINTLN(WiFi.macAddress());

    esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
    esp_now_register_recv_cb(on_data_recv_slave);

    // Don't need to register anyone if the master is broadcasting
    // esp_now_add_peer(master_mac_addr, ESP_NOW_ROLE_CONTROLLER, 1, NULL, 0);
}
