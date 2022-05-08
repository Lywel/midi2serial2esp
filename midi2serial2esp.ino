#include <MIDI.h>

#include "./src/setup.hpp"
#include "./src/midi.hpp"
#include "./src/now.hpp"

void setup()
{

    // CONTROLLER
    //pin_setup();
    //midi_setup();
    //setup_esp_controller();

    // SLAVE
    setup_esp_slave();
    setup_leds();
}

void loop()
{
    // CONTROLLER
    //MIDI.read();


    // SLAVE
    //slave_loop();

    //fadeToBlackBy(leds, NUM_LEDS, 50);
}