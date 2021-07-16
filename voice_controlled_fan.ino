#define rx 13
#define tx 12
#define motor 9
#include<SoftwareSerial.h>
SoftwareSerial displayData(rx,tx);

String fanStatus;
unsigned char entry_no=1;
void setup() {
  displayData.begin(9600);
  Serial.begin(9600);
  pinMode(motor,OUTPUT);
}

void loop()
{
  while(!Serial.available());
  fanStatus=Serial.readString();
  displayData.print(entry_no);
  displayData.print(") ");
  displayData.print("Fan status = ");
  displayData.println(fanStatus); 
  
  entry_no++;
  if(fanStatus=="1")
  {
    digitalWrite(motor,HIGH);
  }
  else
  {
    digitalWrite(motor,LOW);
  }
}
