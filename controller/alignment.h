#ifndef alignment_h
#define alignment_h

#include "Arduino.h"

class alignment {
  public:
    alignment(int pin); // constructor
    void send(); 
  private:
    int _pin;
}

#endif