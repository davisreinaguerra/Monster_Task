# MATLAB Control

Once the arduinos have been programmed with the code for the Monster Task, the entire experiment can be controlled by MATLAB.  matlab_control.mlx provides a GUI-based means to configure the experiment and reads the resulting data sent by arduino from the serial port.

### Trial configuration

The first step is to attach to the arduino (this happens within the setup function of the monsterapp.m code).  COMport may have to be changed depending on which port the arduino automatically attaches to.  

```matlab
app.arduino_Obj = serialport("COM13",9600);
configureTerminator(app.arduino_Obj,"CR");
```

The next step is to open the monsterapp, which provides this GUI:

![Screenshot 2023-04-25 130213](https://user-images.githubusercontent.com/105831652/234350192-90a2127b-22e2-44c7-b9f4-e17e40d26087.png)

Pressing the "Run" button after entering values for each field executes a function which write those configuration values to the serial port where they will be read by arduino.  

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
