switch (state) {
    
    case 0: // Session Begun

      // Do this
      fast_open();
      
      // Check for state switching events
      if (enterIR.is_broken()) {
        state = 1;
        start_alignment.align_offset();
        Serial.println("State Switch -> Mouse Entered State");
        lcd_write("Mouse Entered");
      }
      if ((millis() - start_time) > enter_time_limit) {
        state = 5;
        Serial.println("State Switch -> Trial Ended State");
        lcd_write("Trial ended");
      }
      
      break; 

    case 1: // Mouse Entered

      // Report this
      trial[current_trial].mouse_entered = true;
      trial[current_trial].latency_to_enter = millis() - start_time;

      // Check for state switching events
      if (threatIR.is_broken()) {
        state = 2;
        Serial.println("State Switch -> Threat Triggered State");
        lcd_write("Threat triggered");
      }
      if (nestIR.is_broken()) {
        state = 5;
        Serial.println("State Switch -> Trial Ended State");
        lcd_write("Trial ended");
      }
      
      break;

    case 2: // Threat Triggered

      // Do this
      threat_trigger_alignment.align_onset();
      digitalWrite(threat_trigger_pin, monster_qm);
      digitalWrite(sound_trigger_pin, sound_qm);
      
      // Report this
      trial[current_trial].threat_triggered = true;
      trial[current_trial].latency_to_trigger = millis() - start_time;

      // Check for state switching events
      if (lick.is_licked()) {
        state = 3;
        lick_reward_alignment.align_onset(); 
        Serial.println("State Switch -> Port Licked State");
        lcd_write("Port Licked");
      }
      if (nestIR.is_broken()) {
        state = 5;
        threat_trigger_alignment.align_offset();
        Serial.println("State Switch -> Trial Ended State");
        lcd_write("Trial ended");
      }
      
      break;

    case 3: // Port_licked
            
      lick_time = millis();
  
      // Report this
      trial[current_trial].port_licked = true;
      trial[current_trial].latency_to_lick = millis() - start_time;

      lick_reward_alignment.align_offset();

      // Wait
      delay(delay_between_lick_and_deliver);      

      // Do this
      reward_port.pulse_valve(solenoid_volume_delay);
      lick_reward_alignment.align_onset();

      state = 4;
      Serial.println("State Switch -> Reward Delivered State");
      lcd_write("Reward Delivered");
      lick_reward_alignment.align_offset();

      break;
    
    case 4: // Reward Delivered

      // Check for state switching events
      if (nestIR.is_broken()) {
        trial[current_trial].escape_duration = millis() - lick_time;
        state = 5;
        threat_trigger_alignment.align_offset();
        Serial.println("State Switch -> Trial Ended State");
        lcd_write("Trial ended");
      }

      break;

    case 5: // Trial_ended
      
      // Close the door
      fast_close();
      
      // Report this
      Serial.println("# Trial has ended");
      trial[current_trial].trial_duration = millis() - start_time;

      // display trial outcomes to serial monitor
      Serial.print("Trial = "); Serial.println(current_trial); // Trial Number

      Serial.print("trial_duration = "); Serial.println(trial[current_trial].trial_duration);
      Serial.print("latency_to_enter = "); Serial.println(trial[current_trial].latency_to_enter);
      Serial.print("latency_to_trigger = "); Serial.println(trial[current_trial].latency_to_trigger);
      Serial.print("latency_to_lick = "); Serial.println(trial[current_trial].latency_to_lick);
      Serial.print("escape_duration = "); Serial.println(trial[current_trial].escape_duration);
      Serial.print("mouse_entered = "); Serial.println(trial[current_trial].mouse_entered);
      Serial.print("threat_triggered = "); Serial.println(trial[current_trial].threat_triggered);
      Serial.print("port_licked = "); Serial.println(trial[current_trial].port_licked);

      // Finalize this trial
      digitalWrite(threat_trigger_pin, LOW);
      digitalWrite(sound_trigger_pin, LOW);

      // Wait for the intertrial interval
      delay(intertrial_interval);

      //Move on to next trial
      current_trial += 1;
      state = 0;
      start_alignment.align_onset();
      Serial.println("State Switch -> Session Begun State");
      start_time = millis();
      break;

    case 6: // Session Complete
      Serial.println("Session Complete!");
      fast_close();
      while(1);
  }  
