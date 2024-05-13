#pragma once

#define WIFI_CHANNEL 1

#include <FastLED.h>

typedef struct wifi_msg_s
{
    int8 target = -1;
    bool on = false;
    CRGB color = CRGB::FairyLightNCC;
} wifi_msg_s;
