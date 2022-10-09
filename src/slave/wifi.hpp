#pragma once

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <espnow.h>

#include "./leds.hpp"
#include "../now_utils.hpp"

wifi_msg_s wifi_msg;

void on_data_recv_slave(uint8_t *addr, uint8_t *data, uint8_t len)
{
    Serial.print("Received data from: ");
    print_mac_addr(addr);
    Serial.println(".");

    // TODO: explorer why this copy would be needed
    memcpy(&wifi_msg, data, len);

    if (wifi_msg.on)
    {
        Serial.println("LED ON");
        leds_on();
    }
    else
    {
        Serial.println("LED OFF");
        leds_off();
    }
}

void wifi_setup()
{
    WiFi.mode(WIFI_STA);

    if (esp_now_init() != 0)
    {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);

    esp_now_register_recv_cb(on_data_recv_slave);

    esp_now_add_peer(master_mac_addr, ESP_NOW_ROLE_CONTROLLER, 1, NULL, 0);

    Serial.println("Hello from the RECEIVER !");
}
