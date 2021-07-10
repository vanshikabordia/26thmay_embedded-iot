#include<LiquidCrystal.h>
int rs=13,en=12,d4=11,d5=10,d6=1,d7=0;
LiquidCrystal lcd(13,12,11,10,1,0);
const char DPin=2,UPin=3;    // DPin=down pin & UPin = up pin  for IR
byte carCount=0;

 void setup(){
  pinMode(DPin,INPUT);
  pinMode(UPin,INPUT);
  lcd.begin(16,2);
}

 void Entering(){
  lcd.setCursor(0,0);
  lcd.print("Car is entering");
}

 void Leaving(){
  lcd.setCursor(0,0);
  lcd.print("Car is leaving");
}

 void Entered(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Car entered");
}

 void Exited(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Car exited");
}

void displayCarCount(){
  lcd.setCursor(0,0);
  lcd.print("Car count = ");
  lcd.print(carCount);
}

void loop(){
  displayCarCount();
  if(digitalRead(DPin)){
    lcd.clear();
    while(digitalRead(UPin) or digitalRead(DPin)) Entering();
    Entered();
    delay(500);
    carCount++;
    lcd.clear();
    displayCarCount();
  }
  if(digitalRead(UPin)){
    lcd.clear();
    while(digitalRead(UPin) or digitalRead(DPin)) Leaving();
    Exited();
    delay(500);
    carCount--;
    lcd.clear();
    displayCarCount();
  }
}
