/*



Ptask

The following code was written to control the Monster Ptask, 
an expansion upon the Monster Task designed by Iku Kimura (2022)

Table of Contents:
1. Including Libraries
2. Pin number assignments
3. Global Timer
4. Configuration Input Functions
5. Debugging Functions
6. Trial Functions
___________________________________________________________________________*/


/*

1. Including Libraries
___________________________________________________________________________*/

#include <Wire.h> // required for I2C devices, delete if not using them



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

4. Main Functions in the Order they are run

----> a. initialization_debug_routine();
----> b. trial_scheduler_and_configuration();
----> c. reward_delivery_prob_asker();
----> d. trial_number_asker();
----> e. intertrial_interval_asker();
----> f. sound_filename_asker();
----> g. volume_asker();
----> h. report_config();
----> i. start_experiment();

The first thing that happens when you power up the arduino is the Initialization Debugging Protocol
This part of the code accepts user input to configure a trial
A trial cannot start until this step has been achieved
___________________________________________________________________________*/

void initialization_debug_routine() //function a.
{
  
  
}

// here make a big function that runs through each of the devices one by one
  

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

// add sound_filename_asker(); //function f
// add volume_asker(); //function g

void report_config(); // function h
{
    Serial.println("The reward delivery probability is: "); Serial.print(reward_delivery_probability_asker());
    Serial.println("The trial number is: "); Serial.print()
    Serial.println("The intertrial interval is: "); Serial.print(intertrial_interval_asker());
    //Serial.println("The sound type is: "); Serial.print(sound_filename_asker());
    //Serial.println("The volume of the sound is: "); Serial.print(volume_asker());

    Serial.println ("Is this correct?")
    char c = Serial.read();
    switch (c) 
    {
      case 'y':
        reward_delivery_probability = reward_delivery_probability_asker();
        intertrial_interval = intertrial_interval_asker();
        sound = sound_asker();
        volume = volume asker();
        break;
      case 'n':
        Serial.println("Let's try that again");
        trial_scheduler_and_configuration();
        break;
    }
}   
   

/*

5. Debugging Functions



This part of the code accepts user input to configure a trial
A trial cannot start until this step has been achieved
___________________________________________________________________________*/


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



//?? How do I make it so that the below functions are run only once when I press the reset button, and only one after the other

initialization_debug_routine();
trial_scheduler_and_configuration();
reward_delivery_prob_asker();
trial_number_asker();
intertrial_interval_asker();
sound_filename_asker();
volume_asker();
report_config();
start_experiment();

/*

?. LED DEBUGGING READOUT (VOID LOOP)

The LED Debugging part of the PCB will constantly monitor the responsiveness of sensor
___________________________________________________________________________*/

}

void loop() {


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
