#include <Arduino.h>
#include <FR02A.h>

FR02A::FR02A(int address)
{
  _address = address;
}

FR02A::FR02A()
{
  _address = 0x60;
}


void FR02A::setFrequency(float frequency)
{
  unsigned int frequencyB = 4 * (frequency * 1000000 + 225000) / 32768; 
  byte frequencyH = frequencyB >> 8;
  byte frequencyL = frequencyB & 0xFF;
  Wire.beginTransmission(_address); 
  Wire.write(frequencyH);
  Wire.write(frequencyL);
  Wire.write(0xB0);
  Wire.write(0x10);
  Wire.write(0x00);
  Wire.endTransmission();
  delay(100);  
}


String FR02A::AnalogLvl()
{
  unsigned char buf[5];
  String SignalLvl;
  
  Wire.requestFrom(_address, 5);
  
  if (Wire.available ()) {
    for (int i = 0; i < 5; i++) {
      buf[i] = Wire.read ();
    }
  }
	
  buf[3] = (buf[3] & 0xF0) >> 4;
	
  if(buf[3] <= 0x05){
    SignalLvl = "LOW";}
	
  else if(buf[3] <= 0x0A){
    SignalLvl = "MEDIUM";}
	
  else if(buf[3] <= 0x0F){
    SignalLvl = "HIGH";}
	
	return SignalLvl;
}


void FR02A::SearchUp()
{
  double frequency = 0;

  frequency = Freq_Available();
  unsigned int frequencyB = 4 * (frequency * 1000000 + 225000) / 32768+1; 
  byte frequencyH = frequencyB >> 8; 
  byte frequencyL = frequencyB & 0xFF;
  Wire.beginTransmission(_address); 
  Wire.write(frequencyH + 0x40); // On Search mode
  Wire.write(frequencyL);
  Wire.write(0xD0);  // Search mode (UP)
  Wire.write(0x1F);
  Wire.write(0x00);
  
  Wire.endTransmission();
  delay(100);
}


void FR02A::SearchDown()
{
  double frequency = 0;

  frequency = Freq_Available();
  unsigned int frequencyB = 4 * (frequency * 1000000 + 225000) / 32768+1; 
  byte frequencyH = frequencyB >> 8;
  byte frequencyL = frequencyB & 0xFF;
  Wire.beginTransmission(_address); 
  Wire.write(frequencyH + 0x40);	// On Search mode
  Wire.write(frequencyL);
  Wire.write(0x50);  // Search mode (DOWN)
  Wire.write(0x1F);
  Wire.write(0x00);
  
  Wire.endTransmission();
  delay(100);
}


double FR02A::Freq_Available()
{
  unsigned char buffer[5];
  double freq_available = 0;
  
  Wire.requestFrom(_address, 5);
  if (Wire.available()) {
    for (int i=0; i<5; i++) {
      buffer[i]= Wire.read();
    }
  }
    freq_available = ((((buffer[0]&0x3F)<<8)+buffer[1])*32768/4)-225000;
	freq_available = freq_available/1000000;
    
    return freq_available;
}
