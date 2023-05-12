#include "IR_sensor.h"
#include "Arduino.h"

// constructor
IR_sensor::IR_sensor(int pin) {
  pinMode(pin, INPUT);
  _pin = pin;
}

bool IR_sensor::is_broken() {
  return !digitalRead(_pin);
}

bool IR_sensor::isnt_broken() {
  return digitalRead(_pin);
}
