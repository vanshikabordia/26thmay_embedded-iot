#include<Servo.h>
Servo door;
int positn = 0;
void setup() 
{
  Serial.begin(9600);
  door.attach(2);
  Serial.println(" Enter the password : ");
}

void loop() {
  
  if(Serial.available())
  {
    int password = Serial.read();
    Serial.write(password);
    delay(100);
    if(password == 8)
    {
      for (positn = 0; positn <= 180; positn = (positn + 1)) 
      {
        door.write(positn);              
        delay(2500);                      
      }
      for (positn = 180; positn >= 0; positn = (positn -1)) 
      { 
        door.write(positn);             
        delay(2500);                       
      }
    }
    else
    {
      Serial.println(" Wrong password,try again ");
    }
    
  }

}
