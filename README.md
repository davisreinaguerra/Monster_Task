# Open Source Monster Task Apparatus

The assessment of ethologically relevant foraging behaviors of mice requires behavior-experimental apparati which simultaneously offer rewards and introduce threats to the animal.  The Monster Task developed by Tsutsui-Kimura et al., (2022) is an open-top rectangular box with two chambers: a “nest” chamber which is kept under low illumination to mimic an environmental shelter, and a foraging chamber under high illumination to mimic a daytime foraging situation which requires the mouse leaves its shelter (figure 3). On the far side of the foraging chamber is a mock predator (“Monster”) attached to a motor and positioned behind a reward port which extends upwards from the floor to deliver a pre-set aliquot of water after a fixed number of licks. To get to the reward port, the mice must cross a threshold which is monitored by an infrared break-beam sensor, the crossing of which triggers rapid back and forth movement of the Monster, and a loud complex sound produced by an overhead speaker.  Presented here is an open source version of the Monster Task based on a custom C++/Arduino script uploaded to an Arduino Uno Microcontroller which both monitors the state of sensors via digital inputs and elicits changes in the state of actuators via digital outputs.  

### Pin Assignments

| Pin | name                     | description |
|-----|--------------------------|-------------|
| D0  | unused                   | |
| D1  | unused                   | |
| D2  | NestI                    | Infrared breakbeam sensor checking for the presence of the mouse in the nest |
| D3~ | EnterIR                  | Infrared breabeam sensor checking for the entry of the mouse into the foraging chamber |
| D4  | TriggerIR                | Infrared breakbeam sensor which checks for the crossing of a position which triggers Monster and sound |
| D5~ | Door                     | Hobby servo mounted with an arm connected to the door between the nest and foraging chambers |
| D6~ | Reward_Port              | Provides digital trigger pulses to control a small solenoid valve which opens to the lick port |
| D7  | Lick_Sensor              | Capacitive sensor breakout which checks for licks via a wired connection to the aluminum lick port |
| D8  | Sound_Trigger            | Writes HIGH when the animal crosses the TriggerIR, writes LOW when the animal re-enters the nest |
| D9~ | Threat_Trigger           | Writes HIGH when the animal crosses the TriggerIR, writes LOW when the animal re-enters the nest |
| D10~| Threat_Trigger_Alignment | Writes HIGH when threat is triggered, writes LOW when the animal re-enters the nest |
| D11~| Lick_Reward_Alignment    | Writes HIGH when the animal licks the reward port, writes LOW when reward is delivered |
| D12 | Start_Alignment          | Writes HIGH when trials starts, Writes LOW when trial ends |
| D13 | unused                   | |

### Initialization Code

```c++
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
LiquidCrystal_I2C lcd(0x27,20,4);

// ____________Variable Initializations_____________
const int flush_volume_delay 2000; // ms
long int delay_between_lick_and_deliver 50;
int current_trial = 0;
unsigned long start_time;
unsigned long lick_time;  
int state;
bool ready_to_begin = false;

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

monster_session trial[n_trials];

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
```

### Void Setup
```c++
void setup() {
  // Open serial port
  Serial.begin(9600);

  // PinModes
  pinMode(threat_trigger_pin, OUTPUT);
  pinMode(sound_trigger_pin, OUTPUT);
  doorServo.attach(door_pin);

  // Initialize LCD screen
  lcd.init();
  lcd.clear();
  lcd.backlight();

  // Configure Session
  lcd_write(0, 0, "Waiting 4 config...");

  n_trials = read_config();
  intertrial_interval = read_config();
  enter_time_limit = read_config();
  reward_volume = read_config();
  monster_qm = read_config();
  sound_qm = read_config();
  begin_qm = read_config();

  // Report Configuration
  lcd_write_2_lines(0, 0, "n_trials: ", 0, 2, String(n_trials));
  lcd_write_2_lines(0, 0, "intertrial_interval (ms): ", 0, 2, String(intertrial_interval));
  lcd_write_2_lines(0, 0, "enter_time_limit (ms): ", 0, 2, String(enter_time_limit));
  lcd_write_2_lines(0, 0, "reward_volume (ms): ", 0, 2, String(reward_volume));

  switch (monster_qm) {
    case 1: 
      lcd_write(0,0,"Monster: ON");
      break;
    case 0:
      lcd_write(0,0,"Monster: OFF");
      break;
  }

  switch (sound_qm) {
    case 1: 
      lcd_write(0,0,"Sound: ON");
      break;
    case 0:
      lcd_write(0,0,"Sound: OFF");
      break;
  }

  switch (begin_qm) {
    case 1: 
      lcd_write(0,0, "Session begun!");
      break;
    case 0:
      while(1);
  }
  
  start_time = millis();
  state = 0;
}
```

### Void Loop
```c++

```

### Function Declarations
```c++

```

### Schematic of the Box
![Monster_box](https://user-images.githubusercontent.com/105831652/233440444-31a570cd-8833-4d27-8929-179d749f7888.jpg)
