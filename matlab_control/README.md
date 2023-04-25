# MATLAB Control

Once the arduinos have been programmed with the code for the Monster Task, the entire experiment can be controlled by MATLAB.  matlab_control.mlx provides a GUI-based means to configure the experiment and reads the resulting data sent by arduino from the serial port.

### Trial configuration

```matlab
app.arduino_Obj = serialport("COM13",9600);
configureTerminator(app.arduino_Obj,"CR");
```
