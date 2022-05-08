#pragma once

#include <Arduino.h>
#include <FastLED.h>


#define NUM_LEDS 60

#define DATA_PIN 2

CRGB leds[NUM_LEDS];

void setup_leds() { 
    FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
    //FastLED.setBrightness(max_bright);
    FastLED.setMaxPowerInVoltsAndMilliamps(5, 2000);
}

void leds_on() {
    fill_solid(leds, NUM_LEDS, CRGB::White);
    FastLED.show();
}

void leds_off() {
    FastLED.clear();
    FastLED.show();
}