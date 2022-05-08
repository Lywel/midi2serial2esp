#pragma once

#include <Arduino.h>

#define repeat(x) for(int i = x; i--;)

#define LED_1 2
#define LED_2 16

void pin_setup() {
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
}

void boot_animation() {
    repeat(2) {
        repeat(5) {
            digitalWrite(LED_1, LOW);
            digitalWrite(LED_2, HIGH);
            delay(400);
            digitalWrite(LED_1, HIGH);
            digitalWrite(LED_2, LOW);
            delay(400);
        }
        repeat(5) {
            delay(100);
            digitalWrite(LED_1, LOW);
            digitalWrite(LED_2, LOW);
            delay(100);
            digitalWrite(LED_1, HIGH);
            digitalWrite(LED_2, HIGH);
        }
    }
}