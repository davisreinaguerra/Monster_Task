//______________ Custom Classes_____________________
#include "lick_sensor.h"
#include "solenoid.h"
#include "alignment.h"
#include "IR_sensor.h"

//_______________ Door Servo Setup _________________
#include <Servo.h>
Servo doorServo;
#define door_open_pos 85
#define door_closed_pos 180

// _______________LCD Display_______________________
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

// ____________Variable Initializations_____________
const int delay_between_lick_and_deliver = 50;
int current_trial = 1;
unsigned long start_time;
unsigned long lick_time;  
int previous_state;
int state = 0;
bool ready_to_begin = false;
const int max_trials = 30;

// Session config
long int n_trials;
long int intertrial_interval;
long int enter_time_limit;
long int reward_volume;
long int monster_qm;
long int sound_qm;
long int begin_qm;

//_______________Data Structure____________________
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

monster_session trial[max_trials];

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

//_______________Void Setup_____________________

void setup() {
  // Open serial port
  Serial.begin(9600);

  // PinModes
  pinMode(threat_trigger_pin, OUTPUT);
  pinMode(sound_trigger_pin, OUTPUT);
  doorServo.attach(door_pin);

  // close the door
  fast_close();

  // Initialize LCD screen
  lcd.init();
  lcd.clear();
  lcd.backlight();

  // Configure Session
  lcd_write("Waiting 4 config...");

  n_trials = read_config();
  intertrial_interval = read_config();
  enter_time_limit = read_config();
  reward_volume = read_config();
  monster_qm = read_config();
  sound_qm = read_config();
  begin_qm = read_config();

  // Report Configuration
  lcd_write_2_lines("n_trials: ", String(n_trials)); delay(2000);
  lcd_write_2_lines("iti (ms): ", String(intertrial_interval)); delay(2000);
  lcd_write_2_lines("enter_limit (ms): ", String(enter_time_limit)); delay(2000);
  lcd_write_2_lines("reward_volume (ms): ", String(reward_volume)); delay(2000);

  switch (monster_qm) {
    case 1: 
      lcd_write("Monster: ON"); delay(2000);
      break;
    case 0:
      lcd_write("Monster: OFF"); delay(2000);
      break;
  }

  switch (sound_qm) {
    case 1: 
      lcd_write("Sound: ON"); delay(2000);
      break;
    case 0:
      lcd_write("Sound: OFF"); delay(2000);
      break;
  }

  switch (begin_qm) {
    case 1: 
      lcd_write("Session begun!"); delay(2000);
      break;
    case 0:
      while(1);
  }
 
  state = 1;
}

//_______________Void Loop_____________________

void loop() {

  if (current_trial > n_trials) {state = 9;}

  switch (state) {
    
    case 1: // Trial Begun

      fast_open();
      start_alignment.align_onset();
      start_time = millis();
      
      // Check for state switching events
      if (enterIR.is_broken()) {
        previous_state = state;
        state = 2;
        lcd_write("Mouse going out");
      }
      if (threatIR.is_broken()) {
        previous_state = state; // mouse ran past the enter IR
        state = 3;
        lcd_write("Mouse entered");
        trial[current_trial].mouse_entered = true;
        trial[current_trial].latency_to_enter = millis() - start_time;
      }
      if ((millis() - start_time) > enter_time_limit) {
        previous_state = state;
        state = 8;
        lcd_write("Trial ended");
      }

      break; 
    
    case 2: // Mouse going out
      if (enterIR.is_broken() && nestIR.is_broken()) {}       // sticking around in the door
      if (enterIR.is_broken() && nestIR.isnt_broken()) {      // has actually entered
        previous_state = state;
        state = 3;
        lcd_write("Mouse Entered");
        trial[current_trial].mouse_entered = true;
        trial[current_trial].latency_to_enter = millis() - start_time;
      }
      if (enterIR.isnt_broken() && nestIR.is_broken()) {      // nose out and right back in
        previous_state = state;
        state = 1;
        lcd_write("Mouse went back");
      }
      if (enterIR.isnt_broken() && nestIR.isnt_broken()) {    //  ran ahead and entered
        previous_state = state;
        state = 3;
        lcd_write("Mouse Entered");
        trial[current_trial].mouse_entered = true;
        trial[current_trial].latency_to_enter = millis() - start_time;
      }

      break;

    case 3: // Mouse Entered

      // Check for state switching events
      if (threatIR.is_broken()) {
        previous_state = state;
        state = 4;
        lcd_write("Threat triggered");
        trial[current_trial].threat_triggered = true;
        trial[current_trial].latency_to_trigger = millis() - start_time;
        threat_trigger_alignment.align_onset();
        digitalWrite(threat_trigger_pin, monster_qm);
        digitalWrite(sound_trigger_pin, sound_qm);
      }
      if (nestIR.is_broken()) {
        previous_state = state;
        state = 7;
        lcd_write("Mouse going in");
      }
      
      break;

    case 4: // Threat Triggered

      // Check for state switching events
      if (lick.is_licked()) {
        previous_state = state;
        state = 5;
        lick_reward_alignment.align_onset(); 
        lcd_write("Port Licked");
        lick_time = millis();
        trial[current_trial].port_licked = true;
        trial[current_trial].latency_to_lick = millis() - start_time;
      }
      if (nestIR.is_broken()) {
        previous_state = state;
        state = 7;
        lcd_write("Mouse going in");
      }
      
      break;

    case 5: // Port_licked
  
      delay(delay_between_lick_and_deliver);      
      reward_port.pulse_valve(reward_volume);
      lick_reward_alignment.align_offset();
      previous_state = state;
      state = 6;
      lcd_write("Reward Delivered");

      break;
    
    case 6: // Reward Delivered

      // Check for state switching events
      if (nestIR.is_broken()) {
        previous_state = state;
        state = 7;
        lcd_write("Mouse going in");
      }

      break;

    case 7: // mouse going in
      if (enterIR.is_broken() && nestIR.is_broken()) {}       // lingering upon re-entry
      if (enterIR.isnt_broken() && nestIR.is_broken()) {      // has actually returned
        previous_state = state;
        state = 8;
      }
      if (enterIR.is_broken() && nestIR.isnt_broken()) {      // changed mind didnt re-enter
        state = previous_state;
      } 
      if (enterIR.isnt_broken() && nestIR.isnt_broken()) {
        state = previous_state;
      }

      break;

    case 8: // Trial_ended
      
      
      // Close the door and retract the monster
      slow_close();
      
      if (enterIR.is_broken()) { // dont finish up trial if they are on the wrong side of the doo once it closes
        state = previous_state;
        break;
      }


      start_alignment.align_offset();
      threat_trigger_alignment.align_offset();
      

      // Report this
      Serial.println("# Trial has ended");
      trial[current_trial].escape_duration = millis() - lick_time;
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

      lcd_write("Finished trial" + String(current_trial));

      // Wait for the intertrial interval
      delay(intertrial_interval);

      //Move on to next trial
      current_trial += 1;
      state = 1;

      lcd_write("Trial Begun");

      break;

    case 9: // Session Complete
      lcd_write("Complete!");
      fast_close();
      while(1);
  }  

}



//________________Function Declarations ________________________
void fast_open() {
  doorServo.write(door_open_pos);
}

void fast_close() {
  doorServo.write(door_closed_pos);
}

void slow_open() {
  for (int pos = door_closed_pos; pos >= door_open_pos; pos -= 1) {
    doorServo.write(pos);             
    delay(15);                       
  }
}

void slow_close() {
  for (int pos = door_open_pos; pos <= door_closed_pos; pos += 1) {
    doorServo.write(pos);              
    delay(10);                      
  }
}

long int read_config() {
  while (!Serial.available()) {}
  return Serial.parseInt();
}

void lcd_write(String message) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(message);
}

void lcd_write_2_lines(String message1, String message2) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(message1);
  lcd.setCursor(0, 1);
  lcd.print(message2);
}

void lcd_write_secondline(String message) {
  lcd.setCursor(0, 1);
  lcd.print(message);
}
