# Open Source Monster Task Apparatus

The assessment of ethologically relevant foraging behaviors of mice requires behavior-experimental apparati which simultaneously offer rewards and introduce threats to the animal.  The Monster Task developed by Tsutsui-Kimura et al., (2022) is an open-top rectangular box with two chambers: a “nest” chamber which is kept under low illumination to mimic an environmental shelter, and a foraging chamber under high illumination to mimic a daytime foraging situation which requires the mouse leaves its shelter (figure 3). On the far side of the foraging chamber is a mock predator (“Monster”) attached to a motor and positioned behind a reward port which extends upwards from the floor to deliver a pre-set aliquot of water after a fixed number of licks. To get to the reward port, the mice must cross a threshold which is monitored by an infrared break-beam sensor, the crossing of which triggers rapid back and forth movement of the Monster, and a loud complex sound produced by an overhead speaker.    

Presented here is an open source version of the Monster Task based on a custom C++/Arduino script uploaded to an Arduino Uno Microcontroller which both monitors the state of sensors via digital inputs and elicits changes in the state of actuators via digital outputs.  Listed below are the digital pins of the main arudino as well as the components with which they interface:

________Pin Assignments_________
D0 : unused\
D1 : unused\
D2 : NestIR : Infrared breakbeam sensor checking for the presence of the mouse in the nest
D3 : EnterIR : Infrared breabeam sensor checking for the entry of the mouse into the foraging chamber
D4 : TriggerIR : Infrared breakbeam sensor which checks for the crossing of a position which triggers the Monster and sound
D5
D6
D7
D8 
D9
D10
D11
D12
D13

![Monster_box](https://user-images.githubusercontent.com/105831652/233440444-31a570cd-8833-4d27-8929-179d749f7888.jpg)
