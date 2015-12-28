/*

10/27/15 NCS : Changed Starter logic levels to reflect using a dead-man
               switch to start race (rather than gate switch)

 */

// digital pin 2 has a pushbutton attached to it. Give it a name:
int startSwitch = 2;
int sensorOne = 3;
int sensorTwo = 4;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // Initialize the gate switch & two sensors as inputs
  pinMode(startSwitch, INPUT);
  pinMode(sensorOne, INPUT); 
  pinMode(sensorTwo, INPUT); 
}

// Main program loop
void loop() {
  double oneTime = 0;  // To hold the final time the racers cross the gate
  double twoTime = 0;
  boolean oneFinished = false;  // If the racer has finished yet or not
  boolean twoFinished = false;
  
  Serial.println("Starting timer program");  // Print statement at beginning of program run
  // read the gate switch & sensors
  int starter = digitalRead(startSwitch);
  int one  = digitalRead(sensorOne);
  int two  = digitalRead(sensorTwo);
  
  // If the gate is low, the gate is still down and must be fixed, enter infinite loop
  // We have removed the gate switch (which was LOW in the gate down position) and inserted
  //  a pushbutton switch instead (which is LOW in the pressed position). We would like
  //  the starter to be a dead-man's switch, so we need to check for a HIGH state
  //  to see if the button is released
  if (starter == HIGH) 
  {
    //Serial.println("Gate is down, please set gate and press restart!!!");
    Serial.println("Hold starter button and press restart!!!");
    while(true)
    {}
  }
  
  // If sensor = low, something is blocking it, enter infinite loop
  if (one == LOW) 
  {
    Serial.println("Sensor 1 is not functioning properly, fix it and press restart");
    while(true)
    {}
  }
  
  // If sensor = low, something is blocking it, enter infinite loop
  if (two == LOW) 
  {
    Serial.println("Sensor 2 is not functioning properly, fix it and press restart");
    while(true)
    {}
  }

  // Confirm that the sensors are in the correct state before beginning
  if ( (two == HIGH) && (one == HIGH) && (starter == LOW) )  
  {
    Serial.println("Ready to race");
  }
  else 
  {
    Serial.println("Error has occurred");
    while(true)
    {}
  }
  
  // Wait for gate sensor to open
  while (starter == LOW) 
  {
    starter = digitalRead(startSwitch);
  }
  // Record starting time & print it
  double startTime = millis();
  Serial.println("The gate opened at");
  Serial.println(startTime/1000);

  // Wait for both racer one and two to finish
  while (!(oneFinished && twoFinished ))
  {
    one  = digitalRead(sensorOne);  // Input both sensors
    two  = digitalRead(sensorTwo);
    if ( (one == LOW) && (!oneFinished) )  // If racer crosses sensor, record time & change state to finished
    {
      oneTime = millis();
      oneFinished = 1;        
    }
    
    if ( (two == LOW) && (!twoFinished) ) // If racer crosses sensor, record time & change state to finished
    {
      twoTime = millis();
      twoFinished = 1;        
    }
  }  
  
  // Print the final times recorded
  Serial.println("Racer 1 time = ");
  Serial.println((oneTime - startTime)/1000);
  Serial.println("Racer 2 time = ");
  Serial.println((twoTime - startTime)/1000);
  while (true)
  {}

}
