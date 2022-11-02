#pragma once

#include <Arduino.h>
#include <FastLED.h>

#define NUM_LEDS 60

#define DATA_PIN 2

// TODO: use CRGBArrray for some reasons ?
CRGB leds[NUM_LEDS];

void leds_setup()
{
    FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
    // FastLED.setBrightness(max_bright);
    FastLED.setMaxPowerInVoltsAndMilliamps(5, 2000);
}

void leds_on(CRGB color = CRGB::FairyLightNCC)
{
    fill_solid(leds, NUM_LEDS, color);
    FastLED.show();
}

void leds_off()
{
    FastLED.clear(true);
}