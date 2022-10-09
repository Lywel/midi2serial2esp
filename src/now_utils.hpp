#pragma once

#include <Arduino.h>
#include <espnow.h>

typedef struct wifi_msg_s
{
    bool on = false;
} wifi_msg_s;

uint8_t esp01_bleu[] = {0x18, 0xfe, 0x34, 0xe4, 0xd0, 0xb8};
// mort uint8_t esp01_red[] = {0xec, 0xfa, 0xbc, 0x41, 0x2e, 0xab};
uint8_t esp01_bre[] = {0xcc, 0x50, 0xe3, 0xc1, 0x99, 0x6d};
uint8_t mcu_1[] = {0xf4, 0xcf, 0xa2, 0xef, 0xf4, 0xdd};
uint8_t mcu_f[] = {0xf4, 0xcf, 0xa2, 0xef, 0xb7, 0xf5};
uint8_t master_mac_addr[6] = {0xf4, 0xcf, 0xa2, 0xef, 0xb7, 0xf5};

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