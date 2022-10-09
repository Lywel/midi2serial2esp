#include <MIDI.h>

#ifdef MASTER
#include "./src/master/main.hpp"
#else
#include "./src/slave/main.hpp"
#endif

void setup()
{
    _setup();
}

void loop()
{
    _loop();
}