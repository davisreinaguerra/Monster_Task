% This function closes the door and disengages the threat

function door_close_threat_disengage
    % You should do this for every function that you want to align
    % photometry to

    % Write to door_close_threat_disengage_alignment_pin

    writePWMVoltage(a, door_pin, close_position)
    % pulse_door_close_threat_disengage_UI_lantern
end