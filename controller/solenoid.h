#ifndef solenoid_h
#define solenoid_h

#include "Arduino.h"

class solenoid {
  public:
    solenoid(int pin); // Constructor
    void pulse_valve();
  private:
    int _pin;
}

#endif