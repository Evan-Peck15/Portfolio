// Function used to read incoming data //

void input_map(){
  // Read the analog signal coming from the VFD
  vfd_analog_in = analogRead(VFD_read);
  press_reg_in = analogRead(press_reg_read);
  string_pot_in = analogRead(string_pot_read);

  // Get current time
  current_time = micros();

  // Read the state of the reed switch
  if (ConnectorDI6.State()){
    reed = true;
  }
  else{
    reed = false;
  }

  
}
