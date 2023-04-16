//______________ Custom Classes_____________________________
#include "IR_sensor.h"
#include "lick_sensor.h"
#include "solenoid.h"
#include "alignment.h"

//_______________ Door Servo Setup __________________
#include <Servo.h>
Servo doorServo;
#define door_open_pos 85
#define door_closed_pos 180

//_______________Pin Assignments_____________________
                                          // D0
                                          // D1
IR_sensor nestIR(2);                      // D2
IR_sensor enterIR(3);                     // D3 ~
IR_sensor threatIR(4);                    // D4
#define door_pin 5                        // D5 ~
solenoid reward_port(6);                  // D6 ~
lick_sensor lick(7);                      // D7
#define sound_trigger_pin 8               // D8 
#define threat_trigger_pin 9              // D9 ~
alignment threat_trigger_alignment(10);   // D10 ~
alignment lick_reward_alignment(11);      // D11 ~
alignment start_alignment(12);            // D12
                                          // D13


//_____________Session Configuration variables________
long int n_trials;
long int intertrial_interval;
long int enter_time_limit;
long int monster_qm = 0;
long int sound_qm = 0;
long int delay_between_lick_and_deliver;
long int solenoid_volume_delay;
long int flush_qm = 0;
long int begin_qm = 0;


// ____________Initialization Variables_____________
const int flush_volume_delay 2000; // ms
int current_trial = 0;
unsigned long start_time;
unsigned long lick_time;  
int state;
bool ready_to_begin = false;

//_______________Data Structure_____________________
typedef struct {
  // numerical data
  long int trial_duration;
  long int latency_to_enter;
  long int latency_to_trigger;
  long int latency_to_lick;
  long int escape_duration;
  // logical data  
  bool mouse_entered = false;
  bool threat_triggered = false;
  bool port_licked = false;
} monster_session;

monster_session trial[n_trials];

//_______________Void Setup_____________________

void setup() {
  Serial.begin(9600);
  
  // PinModes
  pinMode(threat_trigger_pin, OUTPUT);
  pinMode(sound_trigger_pin, OUTPUT);
  doorServo.attach(door_pin);

  n_trials = read_serial_config_line();
  intertrial_interval = read_serial_config_line();
  enter_time_limit = read_serial_config_line();
  monster_qm = read_serial_config_line();
  sound_qm = read_serial_config_line();
  delay_between_lick_and_deliver = read_serial_config_line();
  solenoid_volume_delay = read_serial_config_line();
  flush_qm = read_serial_config_line();
  begin_qm = read_serial_config_line();
  
  // Begins the experiment when begin_qm = false
  while(!begin_qm) {}
  start_time = millis();
  state = 0;
  Serial.println("State Switch -> Session Begun State");

}

//_______________Void Loop_____________________

void loop() {

  if (current_trial > n_trials) {state = 6;}

  switch (state) {
    
    case 0: // Trial begun

      // Do this
      fast_open();
      
      // Check for state switching events
      if (enterIR.is_broken()) {
        state = 1;
        start_alignment.align_offset();
        Serial.println("State Switch -> Mouse Entered State");
      }
      if ((millis() - start_time) > enter_time_limit) {
        state = 5;
        Serial.println("State Switch -> Trial Ended State");
      }
      
      break; 

    case 1: // Mouse Entered

      // Report this
      trial[current_trial].mouse_entered = true;
      trial[current_trial].latency_to_enter = millis() - start_time;

      // Check for state switching events
      if (threatIR.is_broken()) {
        state = 2;
        Serial.println("State Switch -> Threat Triggered State");
      }
      if (nestIR.is_broken()) {
        state = 5;
        Serial.println("State Switch -> Trial Ended State");
      }
      
      break;

    case 2: // Threat Triggered

      // Do this
      threat_trigger_alignment.align_onset();
      digitalWrite(threat_trigger_pin, monster_qm);
      digitalWrite(sound_trigger_pin, sound_qm);
      
      // Report this
      trial[current_trial].threat_triggered = true;
      trial[current_trial].latency_to_trigger = millis() - start_time;

      // Check for state switching events
      if (lick.is_licked()) {
        state = 3;
        lick_reward_alignment.align_onset(); 
        Serial.println("State Switch -> Port Licked State");
      }
      if (nestIR.is_broken()) {
        state = 5;
        threat_trigger_alignment.align_offset();
        Serial.println("State Switch -> Trial Ended State");
      }
      
      break;

    case 3: // Port_licked
            
      lick_time = millis();
  
      // Report this
      trial[current_trial].port_licked = true;
      trial[current_trial].latency_to_lick = millis() - start_time;

      lick_reward_alignment.align_offset();

      // Wait
      delay(delay_between_lick_and_deliver);      

      // Do this
      reward_port.pulse_valve(solenoid_volume_delay);
      lick_reward_alignment.align_onset();

      state = 4;
      Serial.println("State Switch -> Reward Delivered State");
      lick_reward_alignment.align_offset();

      break;
    
    case 4: // Reward Delivered

      // Check for state switching events
      if (nestIR.is_broken()) {
        trial[current_trial].escape_duration = millis() - lick_time;
        state = 5;
        threat_trigger_alignment.align_offset();
        Serial.println("State Switch -> Trial Ended State");
      }

      break;

    case 5: // Trial_ended
      
      // Close the door
      fast_close();
      
      // Report this
      Serial.println("# Trial has ended");
      trial[current_trial].trial_duration = millis() - start_time;

      // display trial outcomes to serial monitor
      Serial.print("Trial = "); Serial.println(current_trial); // Trial Number

      Serial.print("trial_duration = "); Serial.println(trial[current_trial].trial_duration);
      Serial.print("latency_to_enter = "); Serial.println(trial[current_trial].latency_to_enter);
      Serial.print("latency_to_trigger = "); Serial.println(trial[current_trial].latency_to_trigger);
      Serial.print("latency_to_lick = "); Serial.println(trial[current_trial].latency_to_lick);
      Serial.print("escape_duration = "); Serial.println(trial[current_trial].escape_duration);
      Serial.print("mouse_entered = "); Serial.println(trial[current_trial].mouse_entered);
      Serial.print("threat_triggered = "); Serial.println(trial[current_trial].threat_triggered);
      Serial.print("port_licked = "); Serial.println(trial[current_trial].port_licked);

      // Finalize this trial
      digitalWrite(threat_trigger_pin, LOW);
      digitalWrite(sound_trigger_pin, LOW);

      // Wait for the intertrial interval
      delay(intertrial_interval);

      //Move on to next trial
      current_trial += 1;
      state = 0;
      start_alignment.align_onset();
      Serial.println("State Switch -> Session Begun State");
      start_time = millis();
      break;

    case 6: // Session Complete
      Serial.println("Session Complete!");
      fast_close();
      while(1);
  }  

}

//________________Door Functions ________________________
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

/* 
//________________Trial Configuration Function __________
long int trial_config() {
  while (Serial.available() == 0) {} // wait for serial input
  long int x = Serial.parseInt(); // save the input
  Serial.end(); Serial.begin(9600); // Empties serial input buffer
  return x; // returns the value which was input
}  
*/

long int read_serial_config_line() {
  while (!Serial.available()) {}
  long int x = Serial.parseInt();
  return x;
}
