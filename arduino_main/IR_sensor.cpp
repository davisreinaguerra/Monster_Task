#include "IR_sensor.h"
#include "Arduino.h"

bool current_state;
bool last_state;

// constructor
IR_sensor::IR_sensor(int pin) {
  pinMode(pin, INPUT);
  _pin = pin;
}

/*
bool IR_sensor::is_broken() {
  check1 = !digitalRead(_pin);
  check2 = !digitalRead(_pin);
  if (check1 == 1 && check2 == 1) {
    return true;
  } else {
    return false;  
  }
}

bool IR_sensor::isnt_broken() {
  check1 = !digitalRead(_pin);
  check2 = !digitalRead(_pin);
  if (check1 == 0 && check2 == 0) {
    return true;
  } else {
    return false;  
  }
}
*/


bool IR_sensor::is_broken() {
  return !digitalRead(_pin);
}

bool IR_sensor::isnt_broken() {
  return digitalRead(_pin);
}

/*
bool IR_sensor::is_rising() {
  current_state = !digitalRead(_pin);
  if (current_state > last_state) {
    return true;
  } else {
    return false;  
  }
  last_state = current_state;
}

bool IR_sensor::is_falling() {
  current_state = !digitalRead(_pin);
  if (check1 == 1 && check2 == 0) {
    return true;
  } else {
    return false;  
  }
  
}
*/
