#include<LiquidCrystal.h>
LiquidCrystal lcd(13,12,4,5,6,7);
int r=0;
byte smiley[8]=
{
     0b00000,
     0b10001,
     0b00000,
     0b00000,
     0b10001,
     0b01110,
     0b00000,
     0b00000
};
void setup() {}

void loop() {
  lcd.createChar(1,smiley);
  lcd.begin(16,2);
  for(int a=1;a<=12;a++) 
  {
    lcd.setCursor(a,0);
    lcd.write(1);
    delay(300);
    lcd.clear();
  }  
 }
