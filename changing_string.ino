#include<LiquidCrystal.h>
//lcd(rs,en,d4,d5,d6,d7)
LiquidCrystal lcd(13,12,4,5,6,7);
void setup()
{
  pinMode(9,INPUT);
  lcd.begin(16,2);
}

void loop()
{ 
  int mode=digitalRead(9);
  if(mode==1)
 {
 lcd.setCursor(1,0);
 lcd.print("HI GUYS!");
 delay(800); 
 lcd.clear();
 }
 else
 {
 lcd.setCursor(1,0);
 lcd.print("BYE GUYS!"); 
 }

}
