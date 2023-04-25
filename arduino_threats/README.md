# Arduino based threats

Each threat is controlled by a different arduino uploaded with a unique code which is inactive unless the trigger input from the main arduino is written to high.  

### Monster Threat

The Monster threat uses a Teknic Clearpath motor to move a gear which (thanks to a system which converts roatry to linear motion) rapidly moves a large ficticious predator back and forth towards the mouse.  The teknic clearpath motor is powered by an external power source and controlled by a cable with 4 different wire pairs (signal and ground, so 8 wires in total).

|        |      |             | 
| Color  | name | arduino pin |    
