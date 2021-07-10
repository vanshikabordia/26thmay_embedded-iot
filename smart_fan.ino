const char tempSensor1=A1,tempSensor2=A0,fan=5,cooler=3;
const char maxSpeed=255,medSpeed=160,lowSpeed=80;
int temp=0;

void setup(){
  pinMode(fan,OUTPUT);
  pinMode(cooler,OUTPUT);
 
  Serial.begin(9600);
}

int getTemp(){ 
  int tempSensor1Val=analogRead(tempSensor1);
  int tempSensor2Val=analogRead(tempSensor2);
  int diff=tempSensor1Val-tempSensor2Val;
  float voltage=diff*5.0/1023;
  temp=voltage*100;
  return temp;
}

void tempToMode(){
  if(-5<=temp and temp<10){
    fanMode('x');
    coolerMode('x');
  }
  else if(10<=temp and temp<15){
    fanMode('s');
    coolerMode('x');
  }
  else if(15<=temp and temp<20){
    fanMode('m');
    coolerMode('x');
  }
  else if(20<=temp and temp<25){
    fanMode('h');
    coolerMode('x');
  }
  else if(25<=temp and temp<30){
    fanMode('h');
    coolerMode('s');
  }
  else if(30<=temp and temp<35){
    fanMode('h');
    coolerMode('m');
  }
  else if(35<=temp and temp<=40){
    fanMode('h');
    coolerMode('h');
  }
  else Serial.println("Limit of temperature exceeded!!!");
}

void fanMode(char mode){
  if(mode=='x'){
    Serial.println("FAN IS OFF");
    digitalWrite(fan,LOW);
  }
  else{
    Serial.println("FAN IS ON");
    if(mode=='h'){
      analogWrite(fan,maxSpeed);
      Serial.println("FAN Mode : HIGH");
    }
    else if(mode=='m'){
      analogWrite(fan,medSpeed);
      Serial.println("FAN Mode : MEDIUM");
    }
    else if(mode=='s'){
      analogWrite(fan,lowSpeed);
      Serial.println("FAN Mode : LOW");
    }
  }
}

void coolerMode(char mode){
  if(mode=='x'){
    Serial.println("COOLER IS OFF");
    digitalWrite(cooler,LOW);
  }
  else{
    Serial.println("COOLER IS ON");
    if(mode=='h'){
      analogWrite(cooler,maxSpeed);
      Serial.println("COOLER Mode : HIGH");
    }
    else if(mode=='m'){
      analogWrite(cooler,medSpeed);
      Serial.println("COOLER Mode : MEDIUM");
    }
    else if(mode=='s'){
      analogWrite(cooler,lowSpeed);
      Serial.println("COOLER Mode : LOW");
    }
  }
}


void loop(){
  int currentTemp=getTemp();
  int previousTemp=currentTemp;
  Serial.print("Temp.= ");
  Serial.print(currentTemp);
  Serial.println(" degree celsius");
  tempToMode();
  while(1){
    while(abs(previousTemp-currentTemp)<=1) currentTemp=getTemp();
    Serial.println();
    Serial.print("Temp.= ");
    Serial.print(currentTemp);
    Serial.println(" degree celsius");
    tempToMode();
    Serial.println();
    previousTemp=currentTemp;
  }
}
