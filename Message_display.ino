#include<Keypad.h>
#include<LiquidCrystal.h>
LiquidCrystal lcd(13,12,11,10,9,8);
String message="";

char keys[4][3]={
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
char row[4]={3,2,1,0};
char col[5]={4,5,6};

Keypad keypad=Keypad(makeKeymap(keys),row,col,4,3);

void setup(){
  lcd.begin(16,2);
}

void slideMessage(){
  unsigned char len=message.length();
  lcd.setCursor(0,1);
  lcd.print(message);
  delay(800);
  for(int i=-1;i>=-1*(len-16);i--)       //for sliding the message
  {
    lcd.setCursor(i,1);
    lcd.print(message);
    delay(300);
  }
  delay(1000);
}

void message1(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("MESSAGE 1");
  message="There will be a math class on Monday.";
  slideMessage();
}

void message2(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("MESSAGE 2");
  message="There will be a social class on Tuesday.";
  slideMessage();
}

void message3(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("MESSAGE 3");
  message="There will be a pe class on Wednesday.";
  slideMessage();
}

void message4(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("MESSAGE 4");
  message="There will be a english class on Thursday.";
  slideMessage();
}

void message5(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("MESSAGE 5");
  message="There will be a hindi class on Friday.";
  slideMessage();
}

void message6(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("MESSAGE 6");
  message="There will be no class on Saturday.";
  slideMessage();
}


void invalidInput(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("No message");
  lcd.setCursor(0,1);
  lcd.print("Press 1 to 6 key");
  delay(1000);
}

void displayMessage(){
  char k=keypad.waitForKey();
  if(k=='1') message1();
  else if(k=='2') message2();
  else if(k=='3') message3();
  else if(k=='4') message4();
  else if(k=='5') message5();
  else if(k=='6') message6();
  else invalidInput();
}

void loop() {
  lcd.setCursor(0,0);
  lcd.print("Digital Message");
  lcd.setCursor(0,1);
  lcd.print("Press 1 to 6 key");
  displayMessage();
}
