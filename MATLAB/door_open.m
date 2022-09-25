% This function, when called opens the door

function door_open
    % You should do this for every function that you want to align
    % photometry to
    
    % Write to door_open_alignment_pin
    
    %save time in door_open_stopwatch
    
    % write to servo to open door
    writePWMVoltage(a, door_pin, open_position)
    
    % pulse_door_open_UI_lantern
end 