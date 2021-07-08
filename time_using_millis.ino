#include<LiquidCrystal.h>
LiquidCrystal lcd(13,12,11,10,9,8);
byte sec=0,minutes=0,hours=0;
unsigned long millis_out=0;
void setup() {
  lcd.begin(16,2);
}

void loop() {
  if(millis()>=millis_out){
    sec=millis()/1000;
    sec=sec%60;
     if(sec==0 and millis_out!=0){
      sec=0;
      minutes++;
      lcd.clear();
       if(minutes>=60){
        minutes=0;
        hours++;
        lcd.clear();
         if(hours>=24){
          hours=0;
          lcd.clear();
        }
      }
    }
   lcd.print(hours);
   lcd.print(":");
   lcd.print(minutes);
   lcd.print(":");
   lcd.print(sec);
   lcd.setCursor(0,0); 
   millis_out+=1000; 
  }
}
