const int buzzer=3;
const int led=4;

#include<EEPROM.h>

String password = "";
String ipData = "";
unsigned char attempt = 3; 
bool hideIpData=0;
char ipChar = 0,baseAddr = 0;


void setup() 
{
  pinMode(buzzer,OUTPUT);
  pinMode(led,OUTPUT);
  Serial.begin(9600);
  
  if(EEPROM.read(baseAddr)==255) 
  {
    password="default"; 
    writepassword();
  }
  else
  {
    readpassword();
  }
}

void loop() 
{
  mainMenu();
}

void writepassword() 
{
  baseAddr=0;
  unsigned char index=0;
  unsigned char len=password.length();
  EEPROM.write(baseAddr,len);
  for(index=0;index<len;index++)
  {
    EEPROM.write(baseAddr+1,password[index]);
    baseAddr++;
  }
  baseAddr=0;
}

void readpassword() 
{
  baseAddr=0;
  password="";
  unsigned char len=EEPROM.read(baseAddr),i=0;
  for(i=0;i<len;i++)
  {
    password.concat((char) EEPROM.read(baseAddr+1));
    baseAddr++;
  }
  baseAddr=0;
}

void mainMenu()
{
  Serial.println("CHOOSE");
  Serial.println();
  Serial.println("1. Enter password.");
  Serial.println("2. Change password.");
  Serial.println();
  Serial.print("Enter your choice : ");
  hideIpData=0;
  takeIp();
  if(ipData=="1")
  {
    Serial.println();
    Serial.println();
    takeNCheckpassword();
  }
  else if(ipData=="2")
  {
    Serial.println();
    Serial.println();
    changepassword();
  }
  else
  {
    Serial.println();
    Serial.println("Invalid Entry");
    Serial.println();
  }
}

void takeNCheckpassword()
{
  Serial.println("PASSWORD SYSTEM");
  Serial.println();
  hideIp();
  Serial.print("Enter password : ");
  takeIp();
  Serial.println();
  if(ipData==password)
  {
    attempt=3; 
    Serial.println("Access Granted");
    Serial.println();
  }
  else
  {
    attempt--;
    Serial.println("Incorrect password");
    alarmOn();
    delay(1000);
    alarmOff();
    Serial.println();
    Serial.print(attempt);
    Serial.println(" attempts left to ENTER password");
    Serial.println();
    if(attempt==0)
    {
      Serial.println("System locked");
      Serial.println("Restart");
      while(1) 
      {
        alarmOn();
        delay(1000);
        alarmOff();
        delay(1000);
      }
    }
  }
}

void alarmOn()
{
  digitalWrite(led,HIGH);
  tone(buzzer,1000);
}

void alarmOff()
{
  digitalWrite(led,LOW);
  noTone(buzzer);
}

void hideIp() 
{
  Serial.print("Hide password (Y/N) : ");
  takeIp();
  while(1) 
  {
    if(ipData=="y")
    {
      hideIpData=1;
      Serial.println();
      Serial.println();
      break;
    }
    else if(ipData=="n")
    {
      hideIpData=0;
      Serial.println();
      Serial.println();
      break;
    }
    else
    {
      Serial.println();
      Serial.println("Invalid Entry");
      Serial.println();
      Serial.print("Hide password (Y/N) : ");
      takeIp();
    }
  }
}


void takeIp() 
{
  char ipChar=0;
  ipData="";
  unsigned short len=0;
  while(1)
  {
    while(!Serial.available());
    ipChar=Serial.read();
    if(ipChar=='\r')
    {
      break;
    }
    else
    {
      len=ipData.length();
      if(ipChar=='\b' and len!=0)
      {
        Serial.print(ipChar);
        ipData.remove(len-1,1);  
      }
      if(hideIpData==1 and ipChar!='\b') 
      {
        Serial.print("*");
        ipData.concat(ipChar);
      }
      if(hideIpData==0 and ipChar!='\b')
      {
        Serial.print(ipChar);
        ipData.concat(ipChar);
      }
    }
  }
}

void changepassword()
{
  Serial.println("Change password");
  Serial.println("");
  checkPrevpassword();
}

void checkPrevpassword()
{
  hideIp();
  Serial.print("Enter prev password : ");
  takeIp();
  Serial.println();
  if(ipData==password)
  {
    Serial.println();
    takeNewpassword();
  }
  else
  {
    Serial.println("Incorrect prev password");
    alarmOn();
    delay(1000);
    alarmOff();
    Serial.println();
  }
}

void takeNewpassword()
{
  String newpassword;
  hideIp();
  Serial.print("Enter new password : ");
  takeIp();
  newpassword=ipData;
  Serial.println();
  Serial.print("Re-Enter new password : ");
  takeIp();
 
  if(ipData==newpassword)
  {
    Serial.println("");
    Serial.println("password changed successfully");
    Serial.println("");
    password=newpassword;
    writepassword();
  }
  else
  {
    Serial.println("");
    Serial.println("Incorrect re-entered password");
    Serial.println("");
  }
}
