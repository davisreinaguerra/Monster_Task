/*



Ptask

The following code was written to control the Monster Ptask, 
an expansion upon the Monster Task designed by Iku Kimura (2022)

Table of Contents:
1. Including Libraries
2. Pin number assignments
3. Global Timer
4. Initialization Debug Functions
5. Configuration Input Functions
6. Trial Functions
7. Void Setup
8. Void loop
___________________________________________________________________________*/


/*

1. Including Libraries
___________________________________________________________________________*/

#include <Wire.h> // required for I2C devices, delete if not using them
#include <SPI.h> // Serial Peripheral Interface
#include <Adafruit_VS1053.h> // Adafruit MusicMaker Library
#include <SD.h> // SD card library

/*

2. Pin Number Assignments
___________________________________________________________________________*/

// IR Sensor Input Pins
#define NEST_IR_PIN
#define TRIGGER_IR_PIN

// Mouse in Door Logic gate - 1: Mouse in Door, 0: Mouse not in Door
#define MOUSE_IN_DOORWAY_PIN

// Door Control Pin (must be PWM capable)
#define DOOR_CONTROL_PIN

// Solonoid Control Pin (must be PWM capable)
#define SOLONOID_PWM_PIN

// Lick port
#define LICK_PIN


// LED Debugging Readout Pins
#define NEST_IR_PIN_LED_READOUT
#define TRIGGER_IR_PIN_LED_READOUT
#define MOUSE_IN_DOORWAY_PIN_LED_READOUT
#define TRIAL_IN_PROGRESS_LED_READOUT
#define LICK_PIN_LED_READOUT

// Audio stuff

#define BREAKOUT_RESET  9      // VS1053 reset pin (output)
#define BREAKOUT_CS     10     // VS1053 chip select pin (output)
#define BREAKOUT_DCS    8      // VS1053 Data/command select pin (output)
#define SHIELD_RESET  -1      // VS1053 reset pin (unused!)
#define SHIELD_CS     7      // VS1053 chip select pin (output)
#define SHIELD_DCS    6      // VS1053 Data/command select pin (output)
#define CARDCS 4     // Card chip select pin
#define DREQ 3 

Adafruit_VS1053_FilePlayer musicPlayer = 
  Adafruit_VS1053_FilePlayer(SHIELD_RESET, SHIELD_CS, SHIELD_DCS, DREQ, CARDCS);

monster_sound = "/godzilla.wav"
pink_sound = "/pink.wav"
no_sound = "/.wav"


/*

3. Global Timer
___________________________________________________________________________*/


// any time you store a millisecond time point into a variable, you must initialize that variable as an unsigned long
unsigned long experiment_start_stopwatch;
unsigned long trial_start_stopwatch;
unsigned long latency_to_trigger;
unsigned long trial_duration;
unsigned long escape_duration;
unsigned long latency_to_lick;




/*

4. Initialize Debugging Functions


These functions are called by the first configuration function initialization_debug_routine

___________________________________________________________________________*/

void debug_door() 
{
  

}

void debug_breakbeams() 
{
  
  
}

void debug_pterodactyl()
{
  // include sound and movement

}

void debug_touch() 
{


}

void debug_solenoid()
{
  


}

/*

5. Configuration Input Functions in the Order they are run

----> a. initialization_debug_routine();
----> b. trial_scheduler_and_configuration();
----> c. reward_delivery_prob_asker();
----> d. trial_number_asker();
----> e. intertrial_interval_asker();
----> f. monster_trial_or_not();
----> g. sound_filename_asker();
----> h. volume_asker();
----> i. report_config();

The first thing that happens when you power up the arduino is the Initialization Debugging Protocol
This part of the code accepts user input to configure a trial
A trial cannot start until this step has been achieved
___________________________________________________________________________*/

void initialization_debug_routine() //function a.
{
  
// here make a big function that runs through each of the configuration debug functions one by one
// end this block by calling to the trial_scheduler_and_configuration function

}
  

void trial_scheduler_and_configuration() //function b.
{
  Serial.println("Ready to begin?");
  char c = Serial.read();
  switch (c) 
  {
    case 'y':
      reward_delivery_prob_asker();
      break;
    case 'n':
      Serial.println("It's okay, I'll wait :/");
      break;
  }
}


int reward_delivery_prob_asker() //function c.
{
   Serial.println("What is the reward probability (0-100)?");
   int i = Serial.parseInt();
   if i // is outside the bounds 0-100
      {Serial.println("Please enter a number between 0 and 100");}
   trial_number_asker();
   return i;
}

int trial_number_asker() //function d
{
   Serial.println("How many trials do you want to run?");
   int i = Serial.parseInt();
   if i // is outside the bounds 1-30
      {Serial.println("Please enter a number between 1 and 30");}
   intertrial_interval_asker();
   return i;
  
}

int intertrial_interval_asker() //function e
{
   Serial.println("What is the intertrial interval (in seconds)?");
   int i_seconds = Serial.parseInt();
   if i // is outside the bounds 1-1000
      {Serial.println("Please enter a number between 1-1000");}
   i_milliseconds = i_seconds * 1000;
   return i_milliseconds; 
}

int monster_trial_or_not() // function f 
{
  Serial.println("Will this be a monster trial? (y/n)");
  char c = Serial.read();
  if c = "y" 
  {
    bool monster_trial = true;
  } 
  else
  {
    bool monster_trial = false;
  }
}


void experiment_filename_asker() // function g
{
    Serial.println("What sound would you like to play? (m = monster, p = pink noise, n = no sound)")
    char c = Serial.read();
    switch (c) 
    {
      case 'm': ]
        experiment_sound = monster_sound;
        break;
      case 'p': 
        experiment_sound = pink_sound;
        break;
      case 'n':
        experiment_sound = no_sound;
        break;
    }


}

// add volume_asker(); //function h

void establish_config() // function i
{
    Serial.println("The reward delivery probability is: "); Serial.print(reward_delivery_probability_asker());
    Serial.println("The trial number is: "); Serial.print()
    Serial.println("The intertrial interval is: "); Serial.print(intertrial_interval_asker());
    Serial.println("It is _____ that the monster will move"); // how to do this?
    //Serial.println("The sound type is: "); Serial.print(sound_filename_asker());
    //Serial.println("The volume of the sound is: "); Serial.print(volume_asker());

    Serial.println ("Is this correct?")
    char c = Serial.read();
    switch (c) 
    {
      case 'y': // here, you want to define all of the variables as the output of the function only if the configuration is correct
        reward_delivery_probability = reward_delivery_probability_asker();
        trial_number = trial_number_asker();
        intertrial_interval = intertrial_interval_asker();
        expeirment_filename = experiment_filename_asker();
        volume = volume asker();

        ready_to_go(); // this moves on to the trial portion of the code
        break;
      case 'n':
        Serial.println("Let's start over");
        trial_scheduler_and_configuration(); // start over
        break;
    }
}   
   

/*

6. Trial Functions
___________________________________________________________________________*/

void ready_to_go() 
{

// ready to start the experiment?  
// If yes, move to next function: run_trials()

}

void run_trials() // have to add escape routes for if trial fails
{
  experiment_start_stopwatch = millis();
  for (int i = 1; i < trial_number; i++) {
    trial_start_stopwatch = millis() - experiment_start_stopwatch;
    Serial.print("Trial "); Serial.print(trial_number);
    
    open_door();
    
    while (wait_for_broken_beam()); // pause until wait_for_broken_beam returns 1
    latency_to_trigger = millis() - trial_start_stopwatch;

    is_there_a_monster();

    while (port_not_licked()); // wait until the port is licked
    latency_to_lick = millis() - latency_to_trigger;

    get_water();

    while (wait_for_return()); // wait until mouse breaks nest pin
    escape_duration = millis() - latency to lick;

    total_trial_duration = millis() - trial_start_stopwatch;

    // reporting on the trial
    Serial.print("The latency to trigger was "); Serial.print(latency_to_trigger); Serial.println(" milliseconds");
    Serial.print("The latency to lick was "); Serial.print(latency_to_lick); Serial.println(" milliseconds");
    Serial.print("The escape duration was"); Serial.print(escape_duration); Serial.println("milliseconds");
    Serial.print("The Total trial duration was"); Serial.print(total_trial_duration); Serial.println("milliseconds");

    delay(intertrial_interval);
    
    }

}

void open_door() 
{
  // servo.write(open)
// this function opens the door at the beginning of the trial
// this function calls wait_for_broken_beam()

}

// this function keeps the monster and sound at bay until the beam is broken
int wait_for_broken_beam() 
{
  // time out after a preset amount of time
  while (TRIGGER_IR_PIN == HIGH) {return 0}; 
  return 1;
}

void is_there_a_monster() 
{
  if (monster_trial == true) 
  {
   digitalWrite(monster, move);
   musicPlayer.playFullFile(experiment_sound);
  }
  if monster_trial == false {}
}

int port_not_licked() 
{
  // return 1 the moment the port is licked
}

int get_water() 
{
  // if cap sensor is touched 5 times, deliver this much water by pulsing open the solonoid  
  while (port_not_licked()) {return 0};
  digitalWrite(give the mf some water);
}

int wait_for_return()
{
  while (NEST_IR_PIN == HIGH) {return 0};
  

}

int return_to_nest() 
{
  

}

/*

?. Void Setup
___________________________________________________________________________*/

void setup() {

  Serial.begin(9600);

  // IR Sensor INPUT Pins
  pinMode(NEST_IR_PIN, INPUT);
  pinMode(TRIGGER_IR_PIN, INPUT)

  // Mouse in Door Logic gate - 1: Mouse in Door, 0: Mouse not in Door
  pinMode(MOUSE_IN_DOOR, INPUT);
  
  // Door Control Pin (must be PWM capable)
  pinMode(DOOR_CONTROL_PIN, OUTPUT);
  
  // Solonoid control
  pinMode(SOLONOID_PWM_PIN, OUTPUT);

  //Lick Port
  pinMode(LICK_PIN, OUTPUT);
  
  //LED Debugging Readout Pins
  pinMode(NEST_IR_PIN_LED_READOUT, OUTPUT);
  pinMode(TRIGGER_IR_PIN_LED_READOUT, OUTPUT);
  pinMode(MOUSE_IN_DOORWAY_PIN_LED_READOUT, OUTPUT);
  pinMode(TRIAL_IN_PROGRESS_LED_READOUT, OUTPUT);
  pinMode(LICK_PIN_LED_READOUT, OUTPUT);




/*

?. LED DEBUGGING READOUT (VOID LOOP)

The LED Debugging part of the PCB will constantly monitor the responsiveness of sensor
___________________________________________________________________________*/

}

void loop() {

//?? How do I make it so that the below functions are run only once when I press the reset button, and only one after the other

initialization_debug_routine();
trial_scheduler_and_configuration();
ready_to_go(); // this begins an exeriment


  // the NEST IR LED lights up when a beam is broken
  while NEST_IR_PIN == LOW {
    digitalWrite(NEST_IR_PIN_LED_READOUT, HIGH);
    }
  while NEST_IR_PIN == HIGH {
    digitalWrite(NEST_IR_PIN_LED_READOUT, LOW)
    }


  // the Mouse in door LED lights up when the mouse is in the doorway
  while MOUSE_IN_DOORWAY_PIN == LOW {
    digitalWrite(MOUSE_IN_DOORWAY_PIN_LED_READOUT, LOW);
    }
  while MOUSE_IN_DOORWAY_PIN == HIGH {
    digitalWrite(MOUSE_IN_DOORWAY_PIN_LED_READOUT, HIGH)
    }

}
