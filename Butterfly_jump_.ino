#include<LiquidCrystal.h>
const int rs=2,en=3,d4=4,d5=5,d6=6,d7=7;
int JUMP_UP= 1;
int START =0;

int i=0;
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);

byte butterfly[8]{
  B000100,
  B010101,
  B001110,
  B010101,
  B001110,
  B000100,
  B001110,
  B010101
  };
  byte obstacle[8]{
  B011111,
  B011111,
  B011111,
  B011111,
  B011111,
  B011111,
  B011111,
  B011111,
  
  };
void setup() {

  lcd.createChar(0,butterfly);
  lcd.begin(16,2);
  pinMode(JUMP_UP,INPUT_PULLUP);
  pinMode(START,INPUT_PULLUP);
}

void loop() {
  if(digitalRead(START)==LOW)
  {
    for(i=0;i<=15;i++)
    {
    lcd.setCursor(i,1);
    lcd.write(byte(0));
    delay(200);
    lcd.clear();
    if(digitalRead(JUMP_UP)==LOW)
    {
      lcd.setCursor(i,0);
      lcd.write(byte(0));
      delay(200);
    }
  }
 }

}
