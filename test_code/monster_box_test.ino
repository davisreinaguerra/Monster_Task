#include "IR_sensor.h"
#include "lick_sensor.h"
#include "solenoid.h"

// Door
#include <Servo.h>
Servo doorServo;
#define door_open_pos 85
#define door_closed_pos 180

long int reward_duration = 200;

//_______________Pin Assignments_____________________
                                          // D0
                                          // D1
IR_sensor nestIR(2);                      // D2
IR_sensor enterIR(3);                     // D3 ~
IR_sensor threatIR(4);                    // D4
#define door_pin 5                        // D5 ~
solenoid reward(6);                       // D6 ~
lick_sensor lick(7);                      // D7
#define sound_trigger_pin 8               // D8 
#define threat_trigger_pin 9              // D9 ~
//alignment threat_trigger_alignment(10)  // D10 ~
//alignment lick_alignment(11)            // D11 ~
//alignment reward_alignment(12)          // D12
                                          // D13

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(sound_trigger_pin, OUTPUT);
  pinMode(threat_trigger_pin, OUTPUT);
  doorServo.attach(door_pin);

  // Door test
  fast_open();
  delay(500);
  fast_close();
  delay(500);
  slow_open();
  delay(500);
  slow_close();
  delay(500);

}

void loop() {
  // put your main code here, to run repeatedly:

  // IR tester
  switch (nestIR.is_broken()) {
    case true:
      Serial.println("nestIR broken");
      break;
    case false:
      break;
  }
  switch (enterIR.is_broken()) {
    case true:
      Serial.println("enterIR broken");
      break;
    case false:
      break;
  }
  switch (threatIR.is_broken()) {
    case true:
      Serial.println("triggerIR broken");
      break;
    case false:
      break;
  }



  // Lick sensor/ solenoid tester
  switch (lick.is_licked()) {
    case false:
      Serial.println("Dont release water!");
      reward.valve_off();
      delay(reward_duration);
      break;
    case true:
      Serial.println("Lick!");
      Serial.println("let's open this valve");
      reward.pulse_valve(reward_duration);
      break;
  }


}

void fast_open() {
  doorServo.write(door_open_pos);
}

void fast_close() {
  doorServo.write(door_closed_pos);
}

void slow_open() {
  for (int pos = door_closed_pos; pos >= door_open_pos; pos -= 1) {
    doorServo.write(pos);             
    delay(20);                       
  }
}

void slow_close() {
  for (int pos = door_open_pos; pos <= door_closed_pos; pos += 1) {
    doorServo.write(pos);              
    delay(20);                      
  }
}