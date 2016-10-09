/*
  Analog Read

 Turns on and off a light emitting diode(LED) connected to digital
 pin 12, when pressing a PHOTOCELL attached to pin A1.

 The circuit:
 * LED attached from pin 12
 * photo cell attached to pin A1
 * other side of push button to ground.
 * 560 OHM resistor attached to LED from ground
*/



int ledPin = 12; // LED connected to digital pin 12

int sensorPin = A1; // Switch connected to digital pin 11
int sensorState = 0; // a variable for reading pushbutton status, set initial value to 0

void setup() { 
  pinMode(ledPin, OUTPUT); // sets the digital pin as output 
  Serial.begin(9600); //starting listening serialport on 9600Hz baudrate
} 

void loop() { 

  sensorState = analogRead(sensorPin);  //read switch status
  Serial.println(sensorState); //print out in serial monitor
  if(sensorState > 600){
      digitalWrite(ledPin, HIGH);
    }

   else{
      digitalWrite(ledPin, LOW);
    }
}

