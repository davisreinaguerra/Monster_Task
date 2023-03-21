//______________ Modules_____________________________

#include <IR_sensor.h>
#include <lick_sensor.h>
#include <solenoid.h>
#include <Servo.h>

//_______________ Door Servo Setup __________________
Servo door;
int current_door_position = 0;
int open_position = 0;
int closed_position = 180;

//_______________Pin Assignments_____________________
                                          // D0
                                          // D1
IR_sensor nestIR(2);                      // D2
IR_sensor enterIR(3);                     // D3 ~
IR_sensor threatIR(4);                    // D4
#define door_servo_pin 5                  // D5 ~
solenoid reward_port(6);                  // D6 ~
lick_sensor lick(7);                      // D7
#define sound_trigger_pin 8               // D8 
#define threat_trigger_pin 9              // D9 ~
alignment threat_trigger_alignment(10)    // D10 ~
alignment lick_alignment(11)              // D11 ~
alignment reward_alignment(12)            // D12
#define start_button 13                   // D13

//_____________Fixed Session Variables______________
#define enter_time_limit = 60000 // ms
#define alignment_duration = 50 // ms
#define solenoid_volume_delay = 50 // ms
#define delay_between_lick_and_deliver = 50 // ms

// ____________Initialization Variables_____________
#define current_trial = 0
unsigned long start_time;  
string state;
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

//_______________Void Setup_____________________

void setup() {
  Serial.begin(9600);
  
  // PinModes
  pinMode(threat_trigger_pin, OUTPUT);
  pinMode(sound_trigger_pin, OUTPUT);
  pinMode(start_button, INPUT);
  door.attach(door_servo_pin);

  // Configure flexible trial variables
  while (ready_to_begin == false) {
    Serial.println("Number of trials = "); n_trials = trial_config();
    Serial.println("Intertrial interval (in ms) = "); intertrial_interval = trial_config();
    Serial.println("Enter time limit (in ms) = "); enter_time_limit = trial_config();
    Serial.println("Monster on? (1:yes, 0:no)"); monster_qm = trial_config();
    Serial.println("Sound on? (1:yes, 2:no)"); sound_qm = trial_config();

    Serial.println("\nCurrent Trial Parameters");
    Serial.print("n_trials = "); Serial.print(n_trials); Serial.println(" trials");
    Serial.print("intertrial_interval = "); Serial.print(intertrial_interval); Serial.print(" milliseconds or "); Serial.print(intertrial_interval /1000); Serial.println(" seconds"); 
    Serial.print("enter_time_limit = "); Serial.print(enter_time_limit); Serial.print(" milliseconds or "); Serial.print(enter_time_limit /1000); Serial.println(" seconds"); 
    Serial.print("Monster? = "); Serial.println(monster_qm);
    Serial.print("Sound? = "); Serial.println(sound_qm);

    Serial.println("\nIs this correct? (1: yes/2: no)"); config_correct = trial_config();
    if (config_correct == 1) {
      ready_to_begin == true;
    } else {
      Serial.println("ugh, fine, I'll let you try again but my processors are getting tired\n\nJust sayin...\n\n");  
    }
  };  

  // Begin
  monster_session trial[n_trials];
  state = "Session begun";

}

//_______________Void Loop_____________________

void loop() {

  if (current_trial > n_trials) {state = "Session complete"}

  switch (state) {
    case "Session begun":
      // Do this
      door.write(open_position);
      start_time = millis();
      
      // Check for state switching events
      if enterIR.is_broken() {state = "Mouse Entered";}
      if ((millis() - start_time) > enter_time_limit) {state = "Trial ended";}
      
      break; 

    case "Mouse Entered":
      // Report this
      trial[current_trial].mouse_entered = true;
      trial[current_trial].latency_to_enter = millis() - start_time;

      // Check for state switching events
      if threatIR.is_broken() {state = "Threat triggered";}
      if nestIR.is_broken() {state = "Trial ended";}
      
      break;

    case "Threat triggered":
      // Do this
      threat_trigger_alignment.send();
      if (monster_qm == 1 && sound_qm == 1) {
        digitalWrite(threat_trigger_pin, HIGH);
        digitalWrite(sound_trigger_pin, HIGH);
      }

      if (monster_qm == 1 && sound_qm == 0) {
        digitalWrite(threat_trigger_pin, HIGH);
        digitalWrite(sound_trigger_pin, LOW);
      }

      if (monster_qm == 0 && sound_qm == 1) {
        digitalWrite(threat_trigger_pin, LOW);
        digitalWrite(sound_trigger_pin, HIGH);
      }
      
      // Report this
      trial[current_trial].threat_triggered = true;
      trial[current_trial].latency_to_trigger = millis() - start_time;

      // Check for state switching events
      if nestIR.is_broken() {state = "Trial ended";}
      
      break;

    case "Port licked":
      // Do this
      lick_alignment.send(alignment_duration);   

      // Report this
      trial[current_trial].port_licked = true;
      trial[current_trial].latency_to_lick = millis() - start_time;

      // Wait
      delay(delay_between_lick_and_deliver);      

      // Do this
      reward_port.pulse_valve();
      reward_alignment.send(alignment_duration);

      break;

    case "Trial ended":
      // Close the door
      door.write(closed_position);
      
      // Report this
      Serial.println(current_trial + ": Trial has ended");
      trial[current_trial].trial_duration = millis() - start_time;

      // display trail outcomes to serial monitor
      showTrial(trial[current_trial]);

      // Finalize this trial
      digitalWrite(threat_trigger_pin, LOW);
      digitalWrite(sound_trigger_pin, LOW);

      // Wait for the intertrial interval
      delay(inter_trial_interval);

      //Move on to next trial
      current_trial++;
      state = "Session begun";
      break;

    case "Session complete":
      Serial.println("Session Complete!");
      while(1);
  }  

}

//_______________Show Trial Function_____________________

void showTrial(monster_session[arg]) {
  
  Serial.print("Trial = "); Serial.println(current_trial); // Trial Number

  Serial.print("Time_enter = "); Serial.println(arg.time_enter);
  Serial.print("Time_trigger = "); Serial.println(arg.time_trigger);
  Serial.print("Time_lick = "); Serial.println(arg.time_lick);
  Serial.print("Time_exit = "); Serial.println(arg.time_exit);
  Serial.print("Mouse_entered? = "); Serial.println(arg.mouse_entered);
  Serial.print("Threat_triggered? = "); Serial.println(arg.threat_triggered);
  Serial.print("Port_licked? = "); Serial.println(arg.port_licked);
}

//________________Trial Configuration Function __________
long int trial_config() {
  while (Serial.available() == 0) {}
  long int x = Serial.parseInt();
  Serial.end(); Serial.begin(9600); // Empties serial input buffer
  return x;
}  