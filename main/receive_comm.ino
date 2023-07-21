void receive_comm() {
 
  incomingString = Serial.readStringUntil(':');

  if (incomingString == "Force") {
    switcher_var = 1;
  }
  else if (incomingString == "Rotation") {
    switcher_var = 2;
  }
  else if (incomingString == "Time"){
    switcher_var = 3;
  }
  else if(incomingString == "Go"){
    switcher_var = 4;
  }
  else if(incomingString == "STOPNOW"){
    switcher_var = 5;
  }

  switch (switcher_var){

    case 1:
    setForce = Serial.readStringUntil(',').toFloat();
    if (setForce == 999){
      pistonActive = false;
    }
    else if (setForce != 999){
      pistonActive = true;
      setForce = ((setForce / 9.81) - 0.0254) / 0.0253;         // Receive desired force[N] and convert to force[kg] then convert to analog
    }

    break;

    case 2:
    setRotation = Serial.readStringUntil(',').toFloat();
    if (setRotation == 999){
      rotateActive = false;
      
    }
    else if (setRotation != 0 && setRotation != 999){
      rotateActive = true;
      oscilTime = 1000000.0 * (1.0/ setRotation);   // Oscillation time [sec]
    }
    else if (setRotation == 0){
      rotateActive = true;
      
    }

    break;

    case 3:
    setRunTime = Serial.readStringUntil(',').toFloat();
    if (setRunTime == 999){
      timeStop = false;
    }
    else if (setRunTime != 999){
      timeStop = true;
      setRunTime = setRunTime * 1000000.0; //Convert sec to micro
    }

    break;

    case 4:
    test_start = true;
    break;

    case 5:
    test_stop = true;
    break;
  }

}
