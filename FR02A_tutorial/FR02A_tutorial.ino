//**********************************************************************************
// Project: Arduino Uno + FR02A + IR Remote Kit 
// Description: Remote Control FM Radio
// Created by: Tony Ng Wei Kang
// Cytron Technologies Sdn Bhd
//**********************************************************************************
#include <IRremote.h>
#include <IRremoteInt.h>
#include <Wire.h>
#include <FR02A.h>
#include <LCD4Bit_mod.h>

int RECV_PIN = 2;
const int ON_OFF = 3;

FR02A radio = FR02A();
IRrecv irrecv(RECV_PIN);
LCD4Bit_mod lcd = LCD4Bit_mod(2);

//============================================================================
//List of FM Freq http://www.jobcity.my/malaysia-radio-channels-online/
// FM Freq below are North FM Freq
#define Hitz      92.8
#define Mix       91.0
#define NineEightEightFM     94.5
#define RedFM     98.1
#define FlyFM     89.9
#define LiteFM    104.4
#define MyFM      99.7
#define MelodiFM  106.5
#define HotFM     88.2
#define SinarFM   97.1
#define OFF  0
#define ON   1
//============================================================================

decode_results results;
char ONOFF;

void setup()
{
  pinMode(ON_OFF, OUTPUT); 
  digitalWrite(ON_OFF, LOW);  // Set the FR02A OFF
  ONOFF = 0;      // Indicate the FR02A are now OFF
  
  lcd.init();
  Wire.begin();
  irrecv.enableIRIn(); // Start the receiver 
}

//========== IR REMOTE ===========================================
//     HEX     DEC       Button
//    FD00FF 16580863 // ON_OFF
//    FD30CF 16593103 // 0
//    FD08F7 16582903 // 1
//    FD8877 16615543 // 2
//    FD48B7 16599223 // 3
//    FD28D7 16591063 // 4
//    FDA857 16623703 // 5
//    FD6897 16607383 // 6
//    FD18E7 16586983 // 7
//    FD9867 16619623 // 8
//    FD58A7 16603303 // 9
//    FD20DF 16589023 // <<
//    FD609F 16605343 // >>
//===============================================================
void loop() {
  if (irrecv.decode(&results)) {  //Check if IR receive anything
    
    if(results.value == 16580863)  {   // ON OFF Button
      if(ONOFF == OFF)  {      // If the FR02A is OFF
      digitalWrite(ON_OFF, HIGH);    // ON FR02A
      ONOFF = ON;
      lcd.clear();
      }
      else  {
      ONOFF = OFF;    // OFF FR02A
      digitalWrite(ON_OFF, LOW);
      lcd.clear();
      }
    }

  if(ONOFF == ON)  {
    if(results.value == 16593103)  { // 0
      radio.setFrequency(Hitz);     // Set Frequency
      lcd.clear();
      lcd.cursorTo(1, 0);
      lcd.printIn("Hitz FM");  
      }
      
    if(results.value == 16582903)  { // 1
      radio.setFrequency(Mix);
      lcd.clear();
      lcd.cursorTo(1, 0);
      lcd.printIn("Mix FM"); 
      }

    if(results.value == 16615543)  { // 2
      radio.setFrequency(NineEightEightFM);
      lcd.clear();
      lcd.cursorTo(1, 0);
      lcd.printIn("988 FM"); 
      }
      
    if(results.value == 16599223)  { // 3
      radio.setFrequency(RedFM);
      lcd.clear();
      lcd.cursorTo(1, 0);
      lcd.printIn("Red FM"); 
      }
      
    if(results.value == 16591063)  { // 4
      radio.setFrequency(FlyFM);
      lcd.clear();
      lcd.cursorTo(1, 0);
      lcd.printIn("Fly FM"); 
      }
      
    if(results.value == 16623703)  { // 5
      radio.setFrequency(LiteFM);
      lcd.clear();
      lcd.cursorTo(1, 0);
      lcd.printIn("Lite FM"); 
      }
      
    if(results.value == 16607383)  { // 6
      radio.setFrequency(MyFM);  
      lcd.clear();
      lcd.cursorTo(1, 0);
      lcd.printIn("My FM"); 
      }
      
    if(results.value == 16586983)  { // 7
      radio.setFrequency(MelodiFM); 
      lcd.clear();
      lcd.cursorTo(1, 0);
      lcd.printIn("Melodi FM"); 
      }
      
    if(results.value == 16619623)  { // 8
      radio.setFrequency(HotFM);
      lcd.clear();
      lcd.cursorTo(1, 0);
      lcd.printIn("Hot FM"); 
      }
      
    if(results.value == 16603303)  { // 9
      radio.setFrequency(SinarFM); 
      lcd.clear();
      lcd.cursorTo(1, 0);
      lcd.printIn("Sinar FM"); 
      }
      
    if(results.value == 16589023)  { // <<
      radio.SearchDown();    // Frequency search DOWN
      lcd.clear();
      lcd.cursorTo(1, 0);
      lcd.printIn("Search Down"); 
      }
      
    if(results.value == 16605343)  { // >>
      radio.SearchUp();   // Frequency search UP  
      lcd.clear();
      lcd.cursorTo(1, 0);
      lcd.printIn("Search Up"); 
      }
  }
    irrecv.resume(); // Receive the next value
  }
}
