# Open Source Monster Task Apparatus

The assessment of ethologically relevant foraging behaviors of mice requires behavior-experimental apparati which simultaneously offer rewards and introduce threats to the animal.  The Monster Task developed by Tsutsui-Kimura et al., (2022) is an open-top rectangular box with two chambers: a “nest” chamber which is kept under low illumination to mimic an environmental shelter, and a foraging chamber under high illumination to mimic a daytime foraging situation which requires the mouse leaves its shelter (figure 3). On the far side of the foraging chamber is a mock predator (“Monster”) attached to a motor and positioned behind a reward port which extends upwards from the floor to deliver a pre-set aliquot of water after a fixed number of licks. To get to the reward port, the mice must cross a threshold which is monitored by an infrared break-beam sensor, the crossing of which triggers rapid back and forth movement of the Monster, and a loud complex sound produced by an overhead speaker.  Presented here is an open source version of the Monster Task based on a custom C++/Arduino script uploaded to an Arduino Uno Microcontroller which both monitors the state of sensors via digital inputs and elicits changes in the state of actuators via digital outputs.  

### Schematic of the Box
![Monster_box](https://user-images.githubusercontent.com/105831652/233440444-31a570cd-8833-4d27-8929-179d749f7888.jpg)

# Running a Monster Task Experiment

### Trial Configuration
Each experiment is configured via a MATLAB App which collects trial variables and writes the value of those variables to the serial port in sequential order.  Pressing the start button on the MATLAB GUI runs the below Serial port write function.  For further info on MATLAB configuration files, [click here](matlab_control)

```matlab
% Button pushed function: StartButton
function start(app, event)
    writeline(app.arduino_Obj, num2str(app.n_trials));
    writeline(app.arduino_Obj, num2str(app.intertrial_interval));
    writeline(app.arduino_Obj, num2str(app.enter_time_limit));
    writeline(app.arduino_Obj, num2str(app.reward_volume));
    writeline(app.arduino_Obj, num2str(app.monster_qm));
    writeline(app.arduino_Obj, num2str(app.sound_qm));
    writeline(app.arduino_Obj, "1");
    delete(app.UIFigure);
    delete(app);
end
```
Arduino then reads the trial configuration information with the below function

``` c++
long int read_config() {
  while (!Serial.available()) {}
  return Serial.parseInt();
}
```

And assigns those values to variables via: 

``` c++
n_trials = read_config();
intertrial_interval = read_config();
enter_time_limit = read_config();
reward_volume = read_config();
monster_qm = read_config();
sound_qm = read_config();
begin_qm = read_config();
```

For the main arduino code [click here](arduino_main/README.md)\
For the arduino code which controls threats [click here](arduino_treats/README.md)

### Arduino Pin Assignments

| Pin | Name                     | Description |
|-----|--------------------------|-------------|
| D0  | unused                   | |
| D1  | unused                   | |
| D2  | NestIR                   | Infrared breakbeam sensor checking for the presence of the mouse in the nest |
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
