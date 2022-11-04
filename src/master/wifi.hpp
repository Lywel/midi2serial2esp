#pragma once

#include <ESP8266WiFi.h>
#include <espnow.h>

#include "./animation.hpp"
#include "../shared/now_utils.hpp"

wifi_msg_s wifi_msg;

void wifi_setup()
{
    WiFi.mode(WIFI_STA);

    if (esp_now_init() != 0)
    {
        Serial.println("Error initializing ESP-NOW");
        error_animation();
        ESP.reset();
        return;
    }

    Serial.println(WiFi.macAddress());

    esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);

    // Using the broadcast addres to send to all slaves
    // No ack is needed from peers in broadcast mode and weed don't need
    // to know the mac address of the slaves.
    // Also the slaves don't have to know the mac address of the master
    esp_now_add_peer(broadcast_mac_addr, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
}
