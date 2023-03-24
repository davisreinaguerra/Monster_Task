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
alignment lick_reward_alignment(11);             // D11 ~
alignment start_alignment(12);           // D12
                                          // D13

//_____________Fixed Session Variables______________
#define n_trials 10
#define alignment_duration 50 // ms
#define solenoid_volume_delay 50 // ms
#define delay_between_lick_and_deliver 100 // ms

//_____________Initialize flexible variables________
long int intertrial_interval;
long int enter_time_limit;
bool monster_qm;
bool sound_qm;


// ____________Initialization Variables_____________
int current_trial = 0;
unsigned long start_time;
unsigned long lick_time;  
int state;
bool ready_to_begin = false;

//_______________Data Structure_____________________
typedef struct {
  // numerical data
  long int trial_duration;
  long int latency_to_enter; // NEW
  long int latency_to_trigger; // NEW
  long int latency_to_lick; // NEW
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

  // Configure flexible trial variables

  Serial.println("Intertrial interval (in ms) = "); intertrial_interval = trial_config();
  Serial.println("Enter time limit (in ms) = "); enter_time_limit = trial_config();
  Serial.println("Monster on? (1:yes, 0:no)"); monster_qm = trial_config();
  Serial.println("Sound on? (1:yes, 2:no)"); sound_qm = trial_config();

  Serial.println("\nCurrent Trial Parameters");
  Serial.print("intertrial_interval = "); Serial.print(intertrial_interval); Serial.print(" milliseconds or "); Serial.print(intertrial_interval /1000); Serial.println(" seconds"); 
  Serial.print("enter_time_limit = "); Serial.print(enter_time_limit); Serial.print(" milliseconds or "); Serial.print(enter_time_limit /1000); Serial.println(" seconds"); 
  Serial.print("Monster? = "); Serial.println(monster_qm);
  Serial.print("Sound? = "); Serial.println(sound_qm);

  Serial.println("Enter 1 to start");
  trial_config();

  // Begin
  Serial.println("State Switch -> Session Begun State");
  start_time = millis();
  state = 0;

}

//_______________Void Loop_____________________

void loop() {

  if (current_trial > n_trials) {state = 6;}

  //_______________STATE MAP___________________
  //    0 - Session Begun
  //    1 - Mouse Entered
  //    2 - Threat Triggered
  //    3 - Port Licked
  //    4 - Reward Delivered
  //    5 - Trial Ended
  //    6 - Session Complete

  switch (state) {
    
    case 0: // Session Begun

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
      digitalWrite(threat_trigger_pin, HIGH);
      digitalWrite(sound_trigger_pin, HIGH);
      
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

//________________Trial Configuration Function __________
long int trial_config() {
  while (Serial.available() == 0) {}
  long int x = Serial.parseInt();
  Serial.end(); Serial.begin(9600); // Empties serial input buffer
  return x;
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
