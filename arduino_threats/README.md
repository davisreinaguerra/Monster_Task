# Arduino based threats

Each threat is controlled by a different arduino uploaded with a unique code which is inactive unless the trigger input from the main arduino is written to high.  

### Monster Threat

The Monster threat uses a Teknic Clearpath motor to move a gear which (thanks to a system which converts roatry to linear motion) rapidly moves a large ficticious predator back and forth towards the mouse.  The teknic clearpath motor is powered by an external power source and controlled by a cable with 4 different wire pairs (signal and ground, so 8 wires in total).

| Color  | name        | arduino pin |    
|--------|-------------|-------------|
| White  | A           | 10          |
| Brown  | A_GND       | GND         |
| Blue   | Enable      | 7           |
| Orange | Enable_GND  | GND         |
| Black  | B           | 5V          |
| Yellow | B_GND       | GND         |
| Green  | HLFB        | Unused      |
| Red    | HLFB_GND    | Unused      |

Enable must be written to high to allow the motor to move\
Writing A to HIGH moves the monster to position A\
Writing B to HIGH defaults the monster to home position when A is not HIGH
