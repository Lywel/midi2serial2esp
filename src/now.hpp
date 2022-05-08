#pragma once

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <espnow.h>

#include "./leds.hpp"

typedef struct struct_smg
{
    bool on = false;
} struct_msg;

struct_msg buf_msg;

uint8_t esp01_bleu[] = {0x18, 0xfe, 0x34, 0xe4, 0xd0, 0xb8};
uint8_t esp01_red[] = {0xec, 0xfa, 0xbc, 0x41, 0x2e, 0xab};
uint8_t mcu_1[] = {0xf4, 0xcf, 0xa2, 0xef, 0xf4, 0xdd};
uint8_t mcu_f[] = {0xf4, 0xcf, 0xa2, 0xef, 0xb7, 0xf5};


// Helpers

void print_mac_addr(uint8_t *mac_addr)
{
    char macStr[18];
    snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
             mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
    Serial.print(macStr);
}

void on_data_revc_fwd(uint8_t *addr, uint8_t *data, uint8_t len)
{
    Serial.print("Received data from: ");

    esp_now_send(addr, (uint8_t *)&data, len);
}

void on_data_recv_slave(uint8_t *addr, uint8_t *data, uint8_t len)
{
    Serial.print("Received data from: ");
    print_mac_addr(addr);
    Serial.println(".");

    memcpy(&buf_msg, data, len);
    
    if (buf_msg.on) {
        Serial.println("LED ON");
        leds_on();
    } else {
        Serial.println("LED OFF");
        leds_off();
    }


}


void setup_esp_controller()
{
    WiFi.mode(WIFI_STA);

    if (esp_now_init() != 0) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);

    //  esp_now_add_peer(esp01_bleu, ESP_NOW_ROLE_COMBO, 1, NULL, 0);
    esp_now_add_peer(esp01_red, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
    // esp_now_add_peer(mcu_1, ESP_NOW_ROLE_COMBO, 1, NULL, 0);
    // esp_now_add_peer(mcu_f, ESP_NOW_ROLE_COMBO, 1, NULL, 0);
}

void setup_esp_slave()
{
    WiFi.mode(WIFI_STA);

    // Init ESP-NOW
    if (esp_now_init() != 0)
    {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);

    
    esp_now_register_recv_cb(on_data_recv_slave);


    // esp_now_add_peer(esp01_bleu, ESP_NOW_ROLE_COMBO, 1, NULL, 0);
    // esp_now_add_peer(esp01_red, ESP_NOW_ROLE_COMBO, 1, NULL, 0);
    // esp_now_add_peer(mcu_1, ESP_NOW_ROLE_COMBO, 1, NULL, 0);
    esp_now_add_peer(mcu_f, ESP_NOW_ROLE_CONTROLLER, 1, NULL, 0);

    Serial.println("Hello from the RECEIVER !");
}





unsigned long last_time = 0;
unsigned long time_delay = 1000;
bool on = false;

void controller_loop()
{

    if ((millis() - last_time) > time_delay)
    {
        last_time = millis();
        buf_msg.on = on;
        on = !on;

        esp_now_send(esp01_red, (uint8_t *)&buf_msg, sizeof(buf_msg));
    }
}

void slave_loop()
{

    if ((millis() - last_time) > time_delay)
    {
        last_time = millis();

        if (on) {
            leds_on();
        } else {
            leds_off();
        }

        on = !on;
    }
}
