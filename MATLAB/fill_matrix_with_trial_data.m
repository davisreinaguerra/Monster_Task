%This code fills table with trial data, accepting the current_trial as a
%parameter



function fill_matrix_with_trial_data(current_trial)
    

    % Latency_to_trigger = threat_engage_stopwatch - door_open_stopwatch
    % Trigger_to_lick_interval = deliver_reward_stopwatch - trigger_stopwatch
    % Escape_duration = door_close_threat_disengage_stopwatch - deliver_reward_stopwatch

    
    
    % if threat_engage_stopwatch == deliver_reward_stopwatch (if both are zero)
        %trial_outcome = 0 (failure before threat_engage)
    % if threat_engage_stopwatch != 0 && deliver_reward-stopwatch == 0
        %trial_outcome = 1 (failure after threat_engage)
    % if threat_engage_stopwatch != 0 && deliver_reward_stopwatch != 0
        %trial_outcome = 2 (success)
        

    % populate a matrix with the following for a given trial:
    
    % Success (2), failure after threat_engage (1), failure before threat_engage (0)
    % Latency to trigger (ms)
    % Trigger to Lick Interval (ms)
    % Escape Duration (ms)
end

