#pragma once

#define WIFI_CHANNEL 1

enum msg_type {
    DISCOVER,
    ACKNOWLEDGE,
    CONTROL,
};

typedef struct wifi_msg_s
{
    enum msg_type type;
    int8_t target = -1;
    bool on = false;
    uint32_t color = 0x228B22;
} wifi_msg_s;
