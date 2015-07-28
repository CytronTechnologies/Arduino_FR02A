#include <Wire.h>
#include <Arduino.h>

#ifndef TEA5767Radio_h
#define TEA5767Radio_h


class FR02A
{
private:
	int _address;

public:
  FR02A();
  FR02A(int address);
  void setFrequency(float frequency);
  void setFrequency();
  String AnalogLvl();
  void SearchUp();
  void SearchDown();
  double Freq_Available();
};


#endif
