/*
  Button

 Turns on and off a light emitting diode(LED) connected to digital
 pin 12, when pressing a pushbutton attached to pin 11.

 The circuit:
 * LED attached from pin 12
 * push button attached to pin 11
 * other side of push button to ground.
 * 560 OHM resistor attached to LED from ground
*/



int ledPin = 13; // LED connected to digital pin 12

int switchState = 0; // a variable for reading pushbutton status, set initial value to 0

void setup() { 
  pinMode(ledPin, OUTPUT); // sets the digital pin as output 
  Serial.begin(9600); //starting listening serialport on 9600Hz baudrate
} 

void loop() { 

  switchState = analogRead(A0);  //read switch status
  Serial.println(switchState); //print out in serial monitor

}

