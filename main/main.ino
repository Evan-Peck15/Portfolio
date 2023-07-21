// include libraries
//Current 4/19/23

// ********************************************** //
// Main tab used to initialize variables, run setup, and loop through other tabs //
#include "ClearCore.h"

// initialize pins
const int piston_analog = IO0;        // Piston solenoid
const int press_reg_read = A12;       // Pressure regulator
const int VFD_read = A11;             // Incoming VFD data
const int string_pot_read = A10;      // Incoming string potentiometer data

// initialize some variables
int current_time = 0;
float vfd_analog_in = 0;
float press_reg_in = 0;
float string_pot_in = 0;
bool output_pist = false;
bool output_motor = false;
bool forward_motor = false;
bool change_press = false;
bool operating = false;
int16_t reed;
int16_t oldreed;

// Initialize for comms
String incomingString;
float setForce;
float setRotation;
float setRunTime;
bool input_switcher = false;
int switcher_var;
bool test_start = false;
bool test_stop = false;
bool rotOscil = false;
float oscilTime = 0;
bool timeStop = false;
bool pistonActive = false;
bool rotateActive = false;
float T;

// Initialize timing variables
int reed_counter = 0;
int data_counter = 0;
float startTime;
float runTime;
float lastOscil = 0;
float lastData = 0;

// Initialize the array of info              *******************************
String freqString = "Freq:";
String forceString = "Force:";
String heightString = "Height:";
String timeString = "Time:";
float freqResults[] = {0};
float forceResults[] = {0};
float heightResults[] = {0};
float timeResults[] = {0};

bool sent_stop = false;

void setup() {

  Serial.begin(9600);
  // initialize pin modes
  init_pin_modes();

  // initialize pin values
  ConnectorIO1.State(false);
  ConnectorIO2.State(false);
  ConnectorIO3.State(false);
  ConnectorIO4.State(false);
  analogWrite(piston_analog, 0, CURRENT);
  reed = false;
  oldreed = false;
  T = micros();

  
}

void loop() {

  // read input signals
  input_map();
  
  // perform operations
  operations();
  
  // output signals
  output_map();

  if (Serial.available() > 0){
    receive_comm();
  }
}
