// #define DEBUG

#include "wifi.hpp"
#include "leds.hpp"

#include <Ticker.h>
#include <ESP8266WiFi.h>

void setup() {
#ifdef DEBUG
  // Don't use the led on esp8266-01 while using pin 2
  // The data line of the led array is on pin 2
  pinMode(LED, OUTPUT);
  Serial.begin(115200);
  while(!Serial) {delay(1);}
#else
  leds_setup();
#endif
  espnow_setup();
  PRINTLN("ready to loop");
}

void loop() {
  yield();
}
