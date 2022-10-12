#pragma once

#include <Arduino.h>

#include "../utils.hpp"
#include "./io.h"

void christmas_tree()
{
    repeat(6)
    {
        digitalWrite(LED_1, LOW);
        digitalWrite(LED_2, HIGH);
        delay(200);
        digitalWrite(LED_2, LOW);
        digitalWrite(LED_1, HIGH);
        delay(200);
    }
    digitalWrite(LED_2, HIGH);
}

void error_animation()
{
    repeat(3)
    {
        repeat(3)
        {
            digitalWrite(LED_1, LOW);
            digitalWrite(LED_2, LOW);
            delay(100);
            digitalWrite(LED_1, HIGH);
            digitalWrite(LED_2, HIGH);
            delay(100);
        }
        delay(500);
    }
}