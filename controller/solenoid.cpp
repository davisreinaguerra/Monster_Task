#include <"solenoid.h">
#include <"Arduino.h">

// constructor
solenoid::solenoid(int pin) {
  pinMode(pin, OUTPUT);
  _pin = pin;
}

solenoid:: void pulse_valve() {
  digitalWrite(_pin, HIGH); 
}