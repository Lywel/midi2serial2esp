#pragma once

#include <Arduino.h>
#include <MIDI.h>

#include "./leds.hpp"
#include "./now.hpp"

struct CustomBaudRateSettings : public MIDI_NAMESPACE::DefaultSerialSettings
{
    static const long BaudRate = 115200;
};

#if defined(ARDUINO_SAM_DUE) || defined(USBCON) || defined(__MK20DX128__) || defined(__MK20DX256__) || defined(__MKL26Z64__)
// Leonardo, Due and other USB boards use Serial1 by default.
MIDI_NAMESPACE::SerialMIDI<HardwareSerial, CustomBaudRateSettings> serialMIDI(Serial1);
MIDI_NAMESPACE::MidiInterface<MIDI_NAMESPACE::SerialMIDI<HardwareSerial, CustomBaudRateSettings>> MIDI((MIDI_NAMESPACE::SerialMIDI<HardwareSerial, CustomBaudRateSettings> &)serialMIDI);
#else
MIDI_NAMESPACE::SerialMIDI<HardwareSerial, CustomBaudRateSettings> serialMIDI(Serial);
MIDI_NAMESPACE::MidiInterface<MIDI_NAMESPACE::SerialMIDI<HardwareSerial, CustomBaudRateSettings>> MIDI((MIDI_NAMESPACE::SerialMIDI<HardwareSerial, CustomBaudRateSettings> &)serialMIDI);
#endif

void handleNoteOn(byte channel, byte note, byte velocity)
{
    digitalWrite(LED_1, LOW);
    buf_msg.on = true;
    esp_now_send(esp01_red, (uint8_t *)&buf_msg, sizeof(buf_msg));
}

void handleNoteOff(byte channel, byte note, byte velocity)
{
    digitalWrite(LED_1, HIGH);
    buf_msg.on = false;
    esp_now_send(esp01_red, (uint8_t *)&buf_msg, sizeof(buf_msg));
}

void midi_setup()
{
    MIDI.begin(MIDI_CHANNEL_OMNI);
    MIDI.setHandleNoteOn(handleNoteOn);
    MIDI.setHandleNoteOff(handleNoteOff);
}

