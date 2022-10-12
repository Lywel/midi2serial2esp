#pragma once

#include <Arduino.h>

#include "../utils.hpp"
#include "./io.h"

void christmas_tree()
{
    repeat(6)
    {
        digitalWrite(LED, HIGH);
        delay(200);
        digitalWrite(LED, LOW);
        delay(200);
    }
}

void error_animation()
{
    repeat(3)
    {
        repeat(10)
        {
            digitalWrite(LED, HIGH);
            delay(100);
            digitalWrite(LED, LOW);
            delay(100);
        }
        delay(1000);
    }
}
