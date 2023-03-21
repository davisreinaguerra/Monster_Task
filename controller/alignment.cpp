#include <"alignment.h">
#include <"Arduino.h">

alignment::alignment(int pin) {
  pinMode(pin, OUTPUT);
  _pin = pin;
}

void alignment::send(x) {
  digitalWrite(_pin, HIGH);
  delay(x);
  digitalWrite(_pin, LOW);
}