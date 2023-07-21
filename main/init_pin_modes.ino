// Function used to initialize pin modes //

void init_pin_modes(){
  
  pinMode(piston_analog, OUTPUT);               // ANALOG OUTPUT PIN -- CONTROL PISTON FORCE
  pinMode(press_reg_read, INPUT);               // ANALOG INPUT PIN -- FROM PRESSURE REGULATOR
  pinMode(VFD_read, INPUT);                     // ANALOG INPUT PIN -- FROM VFD
  pinMode(string_pot_read, INPUT);              // ANALOG INPUT PIN -- FROM STRING POTENTIOMETER
  ConnectorIO1.Mode(Connector::OUTPUT_DIGITAL); // Digital PIN -- ENGAGE PISTON
  ConnectorIO2.Mode(Connector::OUTPUT_DIGITAL); // Digital PIN -- FORWARD ROTATION MOTOR
  ConnectorIO3.Mode(Connector::OUTPUT_DIGITAL); // Digital PIN -- ENGAGE ROTATION MOTOR
  ConnectorIO4.Mode(Connector::OUTPUT_DIGITAL); // DIGITAL PIN -- PRESSURE REGULATOR SWITCH
  ConnectorDI6.Mode(Connector::INPUT_DIGITAL);  // DIGITAL INPUT PIN -- REED SWITCH
}
