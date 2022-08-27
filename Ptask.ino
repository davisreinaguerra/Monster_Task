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




/*

3. Global Timer
___________________________________________________________________________*/


// figure out how to do the elapsed millis thing here



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

// add sound_filename_asker(); //function g
// add volume_asker(); //function h

void establish_config(); // function i
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
        sound_filename = sound_filename_asker();
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

void run_trials() 
{
  for (int i = 1; i < trial_number; i++) {
    start_trial_stopwatch();
    open_door();
    wait_for_broken_beam();
    
    }


// Open door
// initialize breakbeam breakbeam
  
}

void start_trial_stopwatch() 
{

// this function starts a stopwatch at the beginning of the trial

}

void open_door() 
{

// this function opens the door at the beginning of the trial
// this function calls wait_for_broken_beam()

}

void wait_for_broken_beam() 
{

// this function keeps the monster and sound at bay until the beam is broken

}

void is_there_a_monster() 
{

// this function has two portions:
// if monster_trial = true, move the monster and make the sound at predefined intervals
// if monster_trial = false, dont move anything and dont play the sound

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
