#include "lick_sensor.h"
#include "Arduino.h"

// constructor
lick_sensor::lick_sensor(int pin) {
  pinMode(pin, INPUT);
  _pin = pin;
}

bool lick_sensor::is_licked() {
  return digitalRead(_pin);
}