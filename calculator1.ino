#include<Keypad.h>
#include<LiquidCrystal.h>

byte dig1,dig2;
char dig1char,dig2char,action;
float result;

LiquidCrystal lcd(13,12,11,10,9,8);

char keys[4][4]={
  {'7','8','9','/'},
  {'4','5','6','x'},
  {'1','2','3','-'},
  {'k','0','=','+'}};

char digits[10]={'0','1','2','3','4','5','6','7','8','9'};

byte row[4]={7,6,5,4};
byte col[4]={3,2,1,0};

Keypad keypad=Keypad(makeKeymap(keys),row,col,4,4);

void setup() {
  lcd.begin(16,2);
}

void loop() {
  dig1char=keypad.waitForKey();
  FindDig1(); 
  lcd.print(dig1);
  
  action=keypad.waitForKey();
  lcd.print(action);
  
  dig2char=keypad.waitForKey();
  FindDig2();
  lcd.print(dig2);
  
  keypad.waitForKey();
  lcd.print("=");
  
  calculations();
  keypad.waitForKey();
  lcd.clear();
}  

void calculations(){
  if(action =='/'){
    result=float((dig1)/(dig2));
    lcd.print(result);
  }
  else if(action=='x'){
    result=dig1*dig2;
    lcd.print(result);
  }
  else if(action=='-'){
    result=dig1-dig2;
    lcd.print(result);
  }
  else if(action=='+'){
    result=dig1+dig2;
    lcd.print(result);
  }
}

void FindDig1(){
  for(int i=0;i<=9;i++){
    if(digits[i]==dig1char){
      dig1=dig1char-'0';
      break;
    }
  }
}

void FindDig2(){
  for(int i=0;i<=9;i++){
    if(digits[i]==dig2char){
      dig2=dig2char-'0';
      break;
    }
  } 
}
