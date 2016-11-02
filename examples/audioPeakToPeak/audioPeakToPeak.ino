#include <Adafruit_NeoPixel.h>

/****************************************
Example Sound Level Sketch
****************************************/
 
const int sampleWindow = 50; // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;

#define PIN            6
// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      100

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() 
{
   Serial.begin(9600);
     pixels.begin(); // This initializes the NeoPixel library.

}
 
 
void loop() 
{
   unsigned long startMillis= millis();  // Start of sample window
   unsigned int peakToPeak = 0;   // peak-to-peak level
 
   unsigned int signalMax = 0;
   unsigned int signalMin = 1024;
 
   // collect data for 50 mS
   while (millis() - startMillis < sampleWindow)
   {
      sample = analogRead(0);
      if (sample < 1024)  // toss out spurious readings
      {
         if (sample > signalMax)
         {
            signalMax = sample;  // save just the max levels
         }
         else if (sample < signalMin)
         {
            signalMin = sample;  // save just the min levels
         }
      }
   }
   peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude
//   double volts = (peakToPeak * 3.3) / 1024;  // convert to volts
 
//   Serial.println(volts);

  Serial.println(peakToPeak);
 
  if(peakToPeak>10){
    int color = map(peakToPeak,0,1024,0,255);
    
    for(int i=0;i<NUMPIXELS;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255

    pixels.setPixelColor(i, pixels.Color(color,0,0)); // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.

    }
  }else{
    for(int i=0;i<NUMPIXELS;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255

    pixels.setPixelColor(i, pixels.Color(0,0,0)); // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.

  }
  }
  delay(10);
}
