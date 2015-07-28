//**********************************************************************************
// Project: Arduino Uno + FR02A + IR Remote Kit 
// Description: Remote control FM Radio and ability to save freq selected
//
//
// Created by: Tony Ng Wei Kang
// Cytron Technologies Sdn Bhd
//**********************************************************************************

#include <IRremote.h>
#include <IRremoteInt.h>
#include <Wire.h>
#include <FR02A.h>
#include <LiquidCrystal.h>
#include <EEPROM.h>

int RECV_PIN = 2;
const int ON_OFF = 3;

FR02A radio = FR02A();
IRrecv irrecv(RECV_PIN);

//======================== LCD ===============================================
LiquidCrystal lcd(8, 11, 9, 4, 5, 6, 7);
//============================================================================

decode_results results;

double Default_freq  = 8750;
double Current_Freq = 0;

double A = 0;
double B = 0;
byte count = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(ON_OFF, OUTPUT); 
  digitalWrite(ON_OFF, HIGH);  // Set the FR02A ON
  
  lcd.begin(16, 2);
  Wire.begin();
  irrecv.enableIRIn(); // Start the receiver 
  
  lcd.setCursor(0, 0);
  lcd.print("Freq:");
  lcd.setCursor(0, 1);
  lcd.print("Chn:");
}



//========== IR REMOTE ===========================================
//     HEX     DEC        Button            Function
//    FD30CF 16593103     // 0        FM Freq saved in 0
//    FD08F7 16582903     // 1        FM Freq saved in 1
//    FD8877 16615543     // 2        FM Freq saved in 2
//    FD48B7 16599223     // 3        FM Freq saved in 3
//    FD28D7 16591063     // 4        FM Freq saved in 4
//    FDA857 16623703     // 5        FM Freq saved in 5
//    FD6897 16607383     // 6        FM Freq saved in 6
//    FD18E7 16586983     // 7        FM Freq saved in 7
//    FD9867 16619623     // 8        FM Freq saved in 8
//    FD58A7 16603303     // 9        FM Freq saved in 9
//    FD20DF 16589023     // <<       FM Freq auto search UP
//    FD609F 16605343     // >>       FM Freq auto search Down
//           16584943     // ↓        FM Freq decrease 0.1 manually
//           16601263     // ↑        FM Freq increase 0.1 manually
//===============================================================
void loop() {
  if (irrecv.decode(&results)) {  //Check if IR receive anything 
      if(results.value == 16589023)  { // <<
      Current_Freq = (radio.Freq_Available() * 100) + 1;
        if(Current_Freq < Default_freq)  {          // If Freq is below 87.50, Set back to 87.50
          Current_Freq = Default_freq;
          radio.setFrequency(Current_Freq/100);
        }
        radio.SearchDown();    // Frequency search DOWN
        lcd.setCursor(5, 0);
        lcd.print("S.Dwn  "); 
        lcd.setCursor(4, 1);
        lcd.print(' ');
        while(1)  {
          A = radio.Freq_Available(); 
          delay(100);
          B = radio.Freq_Available(); 
          A = A - B;
          if(A == 0) break;
        }
        lcd.setCursor(5, 0);
        lcd.print(radio.Freq_Available());
      }
      
      if(results.value == 16605343)  { // >>
        Current_Freq = (radio.Freq_Available() * 100) + 1;          // If Freq is below 87.50, Set back to 87.50
        if(Current_Freq < Default_freq)  {
          Current_Freq = Default_freq;
          radio.setFrequency(Current_Freq/100);
        }
        radio.SearchUp();   // Frequency search UP  
        lcd.setCursor(5, 0);
        lcd.print("S.Up  ");
        lcd.setCursor(4, 1);
        lcd.print(' '); 
        while(1)  {
          A = radio.Freq_Available(); 
          delay(100);
          B = radio.Freq_Available(); 
          B = B - A;
          if(B == 0) break;
        };
        lcd.setCursor(5, 0);
        lcd.print(radio.Freq_Available());
      }

    if(results.value == 16593103)  { // 0
      radio.setFrequency(FreqSaved(0));     // Set Frequency
      lcd.setCursor(5, 0);                  // Display Freq selected
      lcd.print("      ");
      lcd.setCursor(5, 0); 
      lcd.print(radio.Freq_Available());
      lcd.setCursor(4, 1);
      lcd.print('0');
      }
      
    if(results.value == 16582903)  { // 1
      radio.setFrequency(FreqSaved(1));     // Set Frequency
      lcd.setCursor(5, 0);
      lcd.print("      ");
      lcd.setCursor(5, 0); 
      lcd.print(radio.Freq_Available());
      lcd.setCursor(4, 1);
      lcd.print('1');
      }

    if(results.value == 16615543)  { // 2
      radio.setFrequency(FreqSaved(2));     // Set Frequency
      lcd.setCursor(5, 0);
      lcd.print("      ");
      lcd.setCursor(5, 0); 
      lcd.print(radio.Freq_Available());
      lcd.setCursor(4, 1);
      lcd.print('2');
      }
      
    if(results.value == 16599223)  { // 3
      radio.setFrequency(FreqSaved(3));     // Set Frequency
      lcd.setCursor(5, 0);
      lcd.print("      ");
      lcd.setCursor(5, 0); 
      lcd.print(radio.Freq_Available());
      lcd.setCursor(4, 1);
      lcd.print('3');
      }
      
    if(results.value == 16591063)  { // 4
      radio.setFrequency(FreqSaved(4));     // Set Frequency
      lcd.setCursor(5, 0);
      lcd.print("      ");
      lcd.setCursor(5, 0); 
      lcd.print(radio.Freq_Available());
      lcd.setCursor(4, 1);
      lcd.print('4');
      }
      
    if(results.value == 16623703)  { // 5
      radio.setFrequency(FreqSaved(5));     // Set Frequency
      lcd.setCursor(5, 0);
      lcd.print("      ");
      lcd.setCursor(5, 0); 
      lcd.print(radio.Freq_Available());
      lcd.setCursor(4, 1);
      lcd.print('5');
      }
      
    if(results.value == 16607383)  { // 6
      radio.setFrequency(FreqSaved(6));     // Set Frequency
      lcd.setCursor(5, 0);
      lcd.print("      ");
      lcd.setCursor(5, 0); 
      lcd.print(radio.Freq_Available());
      lcd.setCursor(4, 1);
      lcd.print('6');
      }
      
    if(results.value == 16586983)  { // 7
      radio.setFrequency(FreqSaved(7));     // Set Frequency
      lcd.setCursor(5, 0);
      lcd.print("      ");
      lcd.setCursor(5, 0); 
      lcd.print(radio.Freq_Available());
      lcd.setCursor(4, 1);
      lcd.print('7');
      }
      
    if(results.value == 16619623)  { // 8
      radio.setFrequency(FreqSaved(8));     // Set Frequency
      lcd.setCursor(5, 0);
      lcd.print("      ");
      lcd.setCursor(5, 0); 
      lcd.print(radio.Freq_Available());
      lcd.setCursor(4, 1);
      lcd.print('8');
      }
      
    if(results.value == 16603303)  { // 9
      radio.setFrequency(FreqSaved(9));     // Set Frequency
      lcd.setCursor(5, 0);
      lcd.print("      ");
      lcd.setCursor(5, 0); 
      lcd.print(radio.Freq_Available());
      lcd.setCursor(4, 1);
      lcd.print('9');
      }

    if(results.value == 16584943)  { // ↓
      radio.setFrequency(radio.Freq_Available()-0.01);     // Set Frequency
      lcd.setCursor(5, 0);
      lcd.print("      ");
      lcd.setCursor(5, 0); 
      lcd.print(radio.Freq_Available());
      }
      
    if(results.value == 16601263)  { // ↑
      radio.setFrequency(radio.Freq_Available()+0.01);     // Set Frequency
      lcd.setCursor(5, 0);
      lcd.print("      ");
      lcd.setCursor(5, 0); 
      lcd.print(radio.Freq_Available());
      }
    irrecv.resume(); // Receive the next value
  }
}


//======================= Is the current freq Save in EEPROM ? ===========================================
// **Press the button and release (within 1 second)    --> select the FM Freq saved in the button number
// **Press the button for 1 second  --> Saved the FM Freq selected
//========================================================================================================

double FreqSaved (byte Channel)  {
    switch (Channel) {
      case 0:
        Current_Freq = (radio.Freq_Available() * 100) + 1;    // change th freq from eg 87.50 to 8750
        if(Current_Freq < Default_freq)  {                    // If Freq is below 8750, Set back to 8750
          Current_Freq = Default_freq;
        }
        else  {
          count = 0;                                        // reset the count to 0
          while(count < 7)  {                               // if count < than 7
            irrecv.resume();                                // resume IR receiver
            delay(100);                                     // delay 100us for IR receiver to back to operation
            if(irrecv.decode(&results))  {        
              if(results.value == 4294967295) {             // checn the result if button is still pressed
                count++;                                    // start the count
              }
            }
            else break;                                    // if count < 6; break the loop, do nothing
          }
            if(count == 6)  {                              // if count == 6; save the frequency
               int freq = radio.Freq_Available()*100;
               EEPROM.write(0, radio.Freq_Available());
               EEPROM.write(1, (freq%100));
               lcd.setCursor(10, 1);
               lcd.print("Saved");
               delay(1000);
               lcd.setCursor(10, 1);
               lcd.print("     ");
              }    
   
          Current_Freq = (EEPROM.read(0)*100 + EEPROM.read(1));   
            }   
        break;
        
      case 1:
        Current_Freq = (radio.Freq_Available() * 100) + 1;
        if(Current_Freq < Default_freq)  {          // If Freq is below 87.50, Set back to 87.50
          Current_Freq = Default_freq;
        }
        else  {
          count = 0;
          while(count < 7)  {
            irrecv.resume();
            delay(100);
            if(irrecv.decode(&results))  {
              if(results.value == 4294967295) {
                count++;
              }
            }
            else break;
          }
            if(count == 6)  {
               int freq = radio.Freq_Available()*100;
               EEPROM.write(2, radio.Freq_Available());
               EEPROM.write(3, (freq%100));
               lcd.setCursor(10, 1);
               lcd.print("Saved");
               delay(1000);
               lcd.setCursor(10, 1);
               lcd.print("     ");   
            }    
             
          Current_Freq = (EEPROM.read(2)*100 + EEPROM.read(3));
        }
        break;
        
      case 2:
        Current_Freq = (radio.Freq_Available() * 100) + 1;
        if(Current_Freq < Default_freq)  {          // If Freq is below 87.50, Set back to 87.50
          Current_Freq = Default_freq;
        }
        else  {
          count = 0;
          while(count < 7)  {
            irrecv.resume();
            delay(100);
            if(irrecv.decode(&results))  {
              if(results.value == 4294967295) {
                count++;
              }
            }
            else break;
          }
            if(count == 6)  {
               int freq = radio.Freq_Available()*100;
               EEPROM.write(4, radio.Freq_Available());
               EEPROM.write(5, (freq%100));
               lcd.setCursor(10, 1);
               lcd.print("Saved");
               delay(1000);
               lcd.setCursor(10, 1);
               lcd.print("     ");   
            } 
            
          Current_Freq = (EEPROM.read(4)*100 + EEPROM.read(5));
        }
        break;
        
      case 3:
        Current_Freq = (radio.Freq_Available() * 100) + 1;
        if(Current_Freq < Default_freq)  {          // If Freq is below 87.50, Set back to 87.50
          Current_Freq = Default_freq;
        }
        else  {
          count = 0;
          while(count < 7)  {
            irrecv.resume();
            delay(100);
            if(irrecv.decode(&results))  {
              if(results.value == 4294967295) {
                count++;
              }
            }
            else break;
          }
            if(count == 6)  {
               int freq = radio.Freq_Available()*100;
               EEPROM.write(6, radio.Freq_Available());
               EEPROM.write(7, (freq%100));
               lcd.setCursor(10, 1);
               lcd.print("Saved");
               delay(1000);
               lcd.setCursor(10, 1);
               lcd.print("     ");   
            } 
            
          Current_Freq = (EEPROM.read(6)*100 + EEPROM.read(7));
        }
        break;
        
      case 4:
        Current_Freq = (radio.Freq_Available() * 100) + 1;
        if(Current_Freq < Default_freq)  {          // If Freq is below 87.50, Set back to 87.50
          Current_Freq = Default_freq;
        }
        else  {
          count = 0;
          while(count < 7)  {
            irrecv.resume();
            delay(100);
            if(irrecv.decode(&results))  {
              if(results.value == 4294967295) {
                count++;
              }
            }
            else break;
          }
            if(count == 6)  {
               int freq = radio.Freq_Available()*100;
               EEPROM.write(8, radio.Freq_Available());
               EEPROM.write(9, (freq%100));
               lcd.setCursor(10, 1);
               lcd.print("Saved");
               delay(1000);
               lcd.setCursor(10, 1);
               lcd.print("     ");   
            } 
            
          Current_Freq = (EEPROM.read(8)*100 + EEPROM.read(9));
        }
        break;
        
      case 5:
        Current_Freq = (radio.Freq_Available() * 100) + 1;
        if(Current_Freq < Default_freq)  {          // If Freq is below 87.50, Set back to 87.50
          Current_Freq = Default_freq;
        }
        else  {
          count = 0;
          while(count < 7)  {
            irrecv.resume();
            delay(100);
            if(irrecv.decode(&results))  {
              if(results.value == 4294967295) {
                count++;
              }
            }
            else break;
          }
            if(count == 6)  {
               int freq = radio.Freq_Available()*100;
               EEPROM.write(10, radio.Freq_Available());
               EEPROM.write(11, (freq%100));
               lcd.setCursor(10, 1);
               lcd.print("Saved");
               delay(1000);
               lcd.setCursor(10, 1);
               lcd.print("     ");   
            } 
            
          Current_Freq = (EEPROM.read(10)*100 + EEPROM.read(11));
        }
        break;
        
      case 6:
        Current_Freq = (radio.Freq_Available() * 100) + 1;
        if(Current_Freq < Default_freq)  {          // If Freq is below 87.50, Set back to 87.50
          Current_Freq = Default_freq;
        }
        else  {
          count = 0;
          while(count < 7)  {
            irrecv.resume();
            delay(100);
            if(irrecv.decode(&results))  {
              if(results.value == 4294967295) {
                count++;
              }
            }
            else break;
          }
            if(count == 6)  {
               int freq = radio.Freq_Available()*100;
               EEPROM.write(12, radio.Freq_Available());
               EEPROM.write(13, (freq%100));
               lcd.setCursor(10, 1);
               lcd.print("Saved");
               delay(1000);
               lcd.setCursor(10, 1);
               lcd.print("     ");   
            } 
            
          Current_Freq = (EEPROM.read(12)*100 + EEPROM.read(13));
        }
        break;
        
      case 7:
        Current_Freq = (radio.Freq_Available() * 100) + 1;
        if(Current_Freq < Default_freq)  {          // If Freq is below 87.50, Set back to 87.50
          Current_Freq = Default_freq;
        }
        else  {
          count = 0;
          while(count < 7)  {
            irrecv.resume();
            delay(100);
            if(irrecv.decode(&results))  {
              if(results.value == 4294967295) {
                count++;
              }
            }
            else break;
          }
            if(count == 6)  {
               int freq = radio.Freq_Available()*100;
               EEPROM.write(14, radio.Freq_Available());
               EEPROM.write(15, (freq%100));
               lcd.setCursor(10, 1);
               lcd.print("Saved");
               delay(1000);
               lcd.setCursor(10, 1);
               lcd.print("     ");   
            } 
            
          Current_Freq = (EEPROM.read(14)*100 + EEPROM.read(15));
        }
        break;
        
      case 8:
        Current_Freq = (radio.Freq_Available() * 100) + 1;
        if(Current_Freq < Default_freq)  {          // If Freq is below 87.50, Set back to 87.50
          Current_Freq = Default_freq;
        }
        else  {
          count = 0;
          while(count < 7)  {
            irrecv.resume();
            delay(100);
            if(irrecv.decode(&results))  {
              if(results.value == 4294967295) {
                count++;
              }
            }
            else break;
          }
            if(count == 6)  {
               int freq = radio.Freq_Available()*100;
               EEPROM.write(16, radio.Freq_Available());
               EEPROM.write(17, (freq%100));
               lcd.setCursor(10, 1);
               lcd.print("Saved");
               delay(1000);
               lcd.setCursor(10, 1);
               lcd.print("     ");   
            } 
            
          Current_Freq = (EEPROM.read(16)*100 + EEPROM.read(17));
        }
        break;
        
      case 9:
        Current_Freq = (radio.Freq_Available() * 100) + 1;
        if(Current_Freq < Default_freq)  {          // If Freq is below 87.50, Set back to 87.50
          Current_Freq = Default_freq;
        }
        else  {
          count = 0;
          while(count < 7)  {
            irrecv.resume();
            delay(100);
            if(irrecv.decode(&results))  {
              if(results.value == 4294967295) {
                count++;
              }
            }
            else break;
          }
            if(count == 6)  {
               int freq = radio.Freq_Available()*100;
               EEPROM.write(18, radio.Freq_Available());
               EEPROM.write(19, (freq%100));
               lcd.setCursor(10, 1);
               lcd.print("Saved");
               delay(1000);
               lcd.setCursor(10, 1);
               lcd.print("     ");   
            } 
            
          Current_Freq = (EEPROM.read(18)*100 + EEPROM.read(19));
        }
        break;  
  }
  return Current_Freq/100;
}
