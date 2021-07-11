 int ledPin = 8;
 int ldrPin = A0;


void setup() {
  Serial.begin(9600);
  
  pinMode(8, OUTPUT);
  pinMode(A0, INPUT);
 }


void loop() {
  int ldrStature = analogRead(A0);

  if (ldrStature >= 700) 
 {
   digitalWrite(8, HIGH);
   Serial.print(" Torch is ON : ");
   Serial.println(ldrStature);

 }
  else {

   digitalWrite(8, LOW);
   Serial.print("Torch is OFF: ");
   Serial.println(ldrStature);
 }
   delay(1200);   
 }
  
