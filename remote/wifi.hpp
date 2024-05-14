#pragma once

#include "wifi.h"
#include "macros.h"

#include "leds.hpp"

#include <ESP8266WiFi.h>
#include <espnow.h>

// ESP8266 01  -> 1
// ESP8266 01S -> LED_BUILTIN
#define LED LED_BUILTIN

uint8_t cast_addr[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

void print_mac_addr(uint8_t* mac_addr) {
    char macStr[18];
    snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
             mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
    PRINT(macStr);
}

void control(wifi_msg_s* msg) {
    if (msg->on)
    {
        PRINTLN("LED ON");
#ifdef DEBUG
        digitalWrite(LED, HIGH);
#else
        leds_on(msg->color);
#endif
    }
    else
{
        PRINTLN("LED OFF");
#ifdef DEBUG
        digitalWrite(LED, LOW);
#else
        leds_off();
#endif
    }
}

wifi_msg_s ack = {
    .type = ACKNOWLEDGE
};

void recv_callback(uint8_t* mac, uint8_t *data, uint8_t len) {
    print_mac_addr(mac);
    PRINT(" ("); PRINT(len); PRINTLN(")> ");

    if (len == sizeof(wifi_msg_s)) {
        wifi_msg_s msg;
        memcpy(&msg, data, len);
        switch (msg.type) {
        case DISCOVER:
            PRINTLN("> DISCOVER");
            esp_now_send(mac, (uint8_t*)&ack, sizeof(wifi_msg_s));
            break;
        case ACKNOWLEDGE:
            PRINTLN("> ACKNOWLEDGE");
            break;
        case CONTROL:
            PRINTLN("> CONTROL");
            control(&msg);
        default:
            PRINT("> UNKNOWN(");
            PRINT(msg.type);
            PRINTLN(")");
            break;
        }
    }
}

void espnow_setup() {
    WiFi.mode(WIFI_STA);
    PRINT("\r\n\r\nDevice MAC: ");
    PRINTLN(WiFi.macAddress());
    PRINTLN(sizeof(wifi_msg_s));

    esp_now_init();
    delay(10);
    esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
    esp_now_register_recv_cb(recv_callback);
    esp_now_add_peer(NULL, ESP_NOW_ROLE_CONTROLLER, WIFI_CHANNEL, NULL, 0);
}

