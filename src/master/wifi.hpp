#pragma once

#include <ESP8266WiFi.h>
#include <espnow.h>

#include "../now_utils.hpp"

wifi_msg_s wifi_msg;

void wifi_setup()
{
    WiFi.mode(WIFI_STA);

    if (esp_now_init() != 0)
    {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);

    // TODO: add all peers
    //  esp_now_add_peer(esp01_bleu, ESP_NOW_ROLE_COMBO, 1, NULL, 0);
    esp_now_add_peer(esp01_bre, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
    // esp_now_add_peer(mcu_1, ESP_NOW_ROLE_COMBO, 1, NULL, 0);
    // esp_now_add_peer(mcu_f, ESP_NOW_ROLE_COMBO, 1, NULL, 0);
}
