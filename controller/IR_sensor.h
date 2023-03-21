#ifndef IR_sensor_h
#define IR_sensor_h

#include "Arduino.h"

class IR_sensor {
  public:
    IR_sensor(int pin); // constructor
    bool is_broken();
  private:
    int _pin;
};

#endif