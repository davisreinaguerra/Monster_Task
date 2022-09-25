% This code serves as the control center for the box

% initialization
pause('on')
arduino_handle = arduino('COM4', 'Uno')

%RUN User Interface and Gather information from it

%define othernecessary global variables here




For current_trial = 1:1:number_of_trials
    reset_stopwatches()
    start_timer()
    
    % four phases of the experiment
    door_open()
    threat_engage()
    deliver_reward()
    door_close_threat_disengage()
    
    % data handling
    fill_matrix_with_trial_data(current_trial)
    deliver_data_to_UI()
    
    % pause 
    pause(intertrial_interval)
    
    