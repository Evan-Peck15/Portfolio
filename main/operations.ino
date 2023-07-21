// Function used to run system operations //

void operations() {

  // Print the current status of the reed switch
  if ((reed == false) && (operating == true)) {
    reed_counter += 1;
//    Serial.println(reed_counter);
  }
  else{
    reed_counter = 0;
  }
  oldreed = reed;


  // Check if all variables have been received and the test is ready to start
  // Turns on subsystems and runs test
  if (test_start == true && reed_counter == 0) {
    test_start = false;
    sent_stop = false;
    // Turn on systems
    ConnectorIO4.State(true);
    if (pistonActive == false) {
      //set Piston to pull up at ~500analog
      output_pist = false; //Direction up  ****************** Check if correct bool
      
      setForce = 500;                    //***************** Check if this force can keep piston up during vibration
    }
    else if (pistonActive == true) {
      output_pist = true;                //****************** Check if correct bool
    }

    if (setRotation == 999) {
      // Turn rotation motor off
      output_motor = false; //Motor off ******************** Check if correct bool
      rotOscil = false;
    }
    else if (setRotation != 999) {
      //Turn rotation motor on
      output_motor = true; //Motor on ********************** Check if correct bool
      forward_motor = true; //Motor direction, true=CW, false=CCW   *****************Check if correct
      if (setRotation != 0.00) {
        //Check if motor needs to oscillate
        rotOscil = true;
      }
      else if (setRotation == 0.00) {
        rotOscil = false;
      }
    }
    // Start tracking time
    startTime = current_time;
    operating = true;
  }

  // Check time dependent actions
  // Rotation and run time
  if (operating == true) {
    T = current_time;
    runTime = T - startTime;

    if (timeStop == true && runTime >= setRunTime){   //If run time has been exceeded, stop the test
      test_stop = true;
      operating = false;
    }
  }

  if (rotOscil == true && operating == true) {
    T = micros();
    if ((T-lastOscil) >= oscilTime){
      forward_motor = !forward_motor;
      lastOscil = micros();
    }
  }
  T=micros();
  if ((T-lastData) >= 500000 && operating == true){

    vfd_analog_in = (vfd_analog_in * 0.059) - 2.0804;     
    freqString.concat(vfd_analog_in);
    freqString.concat(',');
    
    press_reg_in = ((press_reg_in * 0.0252) + 0.0728) * 9.8;
    forceString.concat(press_reg_in);
    forceString.concat(',');
    
    heightString.concat(string_pot_in);   // May need to add conversion equation from analog to settling height
    heightString.concat(',');
    timeString.concat(runTime/1000000);
    timeString.concat(',');

    data_counter += 1;
    lastData = micros();
  }


  // Check stop conditions (STOP command received, time limit reached or reed switch is opened
  // If either condition is met, stop ALL subsystems
  if (test_stop == true || reed_counter >= 1000) {
//    Serial.println(test_stop);
//    Serial.println(reed);
    if (sent_stop == false) {
      vfd_analog_in = (vfd_analog_in * 0.059) - 2.0804;
      freqString.concat(vfd_analog_in);
      press_reg_in = ((press_reg_in * 0.0252) + 0.0728) * 9.8;
      forceString.concat(press_reg_in);
      heightString.concat(string_pot_in);
      timeString.concat(runTime/1000000);
      Serial.print("STOP\n");

      
      
      if(reed_counter >= 1000){
        Serial.print("BECAUSE OF REED\n");
      }
      Serial.print(freqString);
      Serial.print("\n");
      Serial.print(forceString);
      Serial.print("\n");
      Serial.print(heightString);
      Serial.print("\n");
      Serial.print(timeString);
      Serial.print("\n");
      // Turn off ALL systems
      operating = false;
      timeStop = false;
      test_stop = false;
      rotOscil = false;
      output_pist = false; //Direction up
      setForce = 300;
      setRunTime = 0;
      runTime = 0;
      reed_counter = 0;
      lastData = 0;
      output_motor = false;
      freqString = "Freq:";
      forceString = "Force:";
      heightString = "Height:";
      timeString = "Time:";
      
      // Set the piston to up or down
      ConnectorIO1.State(output_pist);
    
      // Change the direction of rotation of the rotation motor
      ConnectorIO2.State(forward_motor);

      // Turn the rotation motor on or off
      ConnectorIO3.State(output_motor);

      // Turn the pressure regulator off
      ConnectorIO4.State(false);
    
      sent_stop = true;
    }
  }

}
