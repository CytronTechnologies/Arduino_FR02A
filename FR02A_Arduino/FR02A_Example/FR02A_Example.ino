#include <Wire.h>
#include <FR02A.h>

FR02A radio = FR02A();

void setup()
{
  Serial.begin(9600);  //Begin Serial communication in 9600 baudrate
  Wire.begin();
  
  radio.setFrequency(92.8); // pick your own frequency
}

void loop()
{   
  unsigned button = Serial.read();
 
  if(button == '1')  {		// enter ASCII '1' to search up
    radio.SearchUp();   // Frequency search UP
  }
  
 else if(button == '2')  {	// enter ASCII '2' to search up
    radio.SearchDown();    // Frequency search DOWN
  }
  
   Serial.print(radio.Freq_Available());  // Current Frequency
   Serial.println(radio.AnalogLvl());  // Frequency Level
   delay(100); 
}
