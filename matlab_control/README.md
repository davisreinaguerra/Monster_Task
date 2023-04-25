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

