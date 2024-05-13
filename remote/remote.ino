#include "macros.h"
#include "wifi.hpp"
#include "leds.hpp"

#include <Ticker.h>

char alive_msg[] = "I'm alive";
Ticker alive_ticker;

void alive() {
  PRINTLN(alive_msg);
  esp_now_send(cast_addr, (uint8_t*)alive_msg, sizeof(alive_msg));
}


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

  alive_ticker.attach(10, alive);
}

void loop() {
  yield();
}
