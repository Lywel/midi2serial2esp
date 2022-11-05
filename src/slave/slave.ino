#include "wifi.hpp"
#include "leds.hpp"
#include "../shared/utils.hpp"
#include "io.h"
#include "animation.hpp"

#define FPS 60

void setup()
{
#ifdef DEBUG
    Serial.begin(115200);
    // Don't use the led on esp8266-01
    // The data line of the led array is on pin 2
    pinMode(LED, OUTPUT);
#endif

    wifi_setup();
    leds_setup();

#ifdef DEBUG
    christmas_tree();
#endif
}

void loop()
{
    EVERY_N_MILLISECONDS(1000 / FPS)
    {
        render();
    }
}
