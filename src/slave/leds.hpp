#pragma once

#include <Arduino.h>
#include <FastLED.h>

#define NUM_LEDS 60

#define DATA_PIN 2

// TODO: use CRGBArrray for some reasons ?
CRGBArray<NUM_LEDS> leds;

typedef struct scene_s
{
    CRGB color;
    uint8 nframe = 1;
    uint8 frame = 0;
} scene_s;

scene_s scene = {CRGB::Black, 1, 0};

void leds_setup()
{
    FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
    // FastLED.setBrightness(max_bright);
    FastLED.setMaxPowerInVoltsAndMilliamps(5, 2000);
}

void leds_on(CRGB color = CRGB::FairyLightNCC)
{
    // fill_solid(leds, NUM_LEDS, color);
    scene.color = color;
    scene.frame = 0;
    scene.nframe = 12;
}

void leds_off()
{
    // FastLED.clear(true);
    scene.color = CRGB::Black;
    scene.frame = 0;
    scene.nframe = 120;
}

void render()
{
    if (scene.frame <= scene.nframe)
    {
        if (scene.frame == scene.nframe)
        {
            leds.fill_solid(scene.color);
        }
        else
        {
            CRGB newcol = leds[0].lerp8(scene.color, scene.frame * 256 / scene.nframe);
            leds.fill_solid(newcol);
        }
        FastLED.show();
        scene.frame++;
    }
}