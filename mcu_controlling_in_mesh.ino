Code for Node1:
#include "painlessMesh.h"

#define   MESH_PREFIX     "whateverYouLike"       // WiFi Credentials
#define   MESH_PASSWORD   "somethingSneaky"
#define   MESH_PORT       5555
bool button1_status = 0;
bool button2_status = 0;

#define Button1 D5                               //Pin Declaration
#define Button2 D6
Scheduler userScheduler; 
painlessMesh  mesh;

void sendMessage() ; 
Task taskSendMessage( TASK_SECOND * 1 , TASK_FOREVER, &sendMessage );

void sendMessage() 
{

  if (digitalRead(Button1) == HIGH)               // Pushbutton
    button1_status = !button1_status;
  if (digitalRead(Button2) == HIGH)
    button2_status = !button2_status;
 
  DynamicJsonDocument doc(1024);                 // JSON 
  doc["Relay1"] = button1_status;
  doc["Relay2"] = button2_status;
  String msg ;
  serializeJson(doc, msg);
    mesh.sendBroadcast( msg );
  Serial.println(msg);
  taskSendMessage.setInterval((TASK_SECOND * 1));
}

void receivedCallback( uint32_t from, String &msg )
{
  String json;
  DynamicJsonDocument doc(1024);
  json = msg.c_str();
  DeserializationError error = deserializeJson(doc, json);
  if (error)
  {
    Serial.print("deserializeJson() failed: ");
    Serial.println(error.c_str());
  }
   String Temp = doc["TEMP"];
   String Hum = doc["HUM"];
  Serial.println("From node1");
   Serial.println("Temperature:");
   Serial.print(Temp);
    Serial.println("Humidity:");
   Serial.print(Hum);
}

void newConnectionCallback(uint32_t nodeId)
{
  Serial.printf("--> startHere: New Connection, nodeId = %u\n", nodeId);
}
void changedConnectionCallback() {
  Serial.printf("Changed connections\n");
}

void nodeTimeAdjustedCallback(int32_t offset) 
{
  Serial.printf("Adjusted time %u. Offset = %d\n", mesh.getNodeTime(), offset);
}

void setup() 
{
  Serial.begin(115200);
  pinMode(Button1, INPUT);
  pinMode(Button2, INPUT);
  mesh.setDebugMsgTypes( ERROR | STARTUP );  // set before init() so that you can see startup messages
  mesh.init( MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT );
  mesh.onReceive(&receivedCallback);
  mesh.onNewConnection(&newConnectionCallback);
  mesh.onChangedConnections(&changedConnectionCallback);
  mesh.onNodeTimeAdjusted(&nodeTimeAdjustedCallback);
  userScheduler.addTask( taskSendMessage );
  taskSendMessage.enable();
}

void loop()
{
  mesh.update();
}


Code for Node2:
#include "painlessMesh.h"
#include <DHT.h> 
                                                     // WiFi Credentials
#define   MESH_PREFIX     "whateverYouLike"
#define   MESH_PASSWORD   "somethingSneaky"
#define   MESH_PORT       5555
                                                     //Pin Declaration
#define Relay1 D6
#define DHTPIN D5
#define DHTTYPE DHT11                                // DHT 11
DHT dht(DHTPIN, DHTTYPE);
                                                     //Variables
bool relay1_status = 0;
Scheduler userScheduler; 
painlessMesh  mesh;
void sendMessage() ; 
Task taskSendMessage( TASK_SECOND * 1 , TASK_FOREVER, &sendMessage );
void sendMessage()
{
                                             // Serializing in JSON Format
  DynamicJsonDocument doc(1024);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  doc["TEMP"] = t;
  doc["HUM"] = h;
  String msg ;
  serializeJson(doc, msg);
  mesh.sendBroadcast( msg );
  Serial.println("from node2");
  Serial.println(msg);
  taskSendMessage.setInterval((TASK_SECOND * 10));
}
                                                                     //painless library
void receivedCallback( uint32_t from, String &msg ) {
  String json;
  DynamicJsonDocument doc(1024);
  json = msg.c_str();
  DeserializationError error = deserializeJson(doc, json);
  if (error)
  {
    Serial.print("deserializeJson() failed: ");
    Serial.println(error.c_str());
  }
  relay1_status = doc["Relay1"];
  digitalWrite(Relay1, relay1_status);
}
void newConnectionCallback(uint32_t nodeId) {
  Serial.printf("--> startHere: New Connection, nodeId = %u\n", nodeId);
}
void changedConnectionCallback() {
  Serial.printf("Changed connections\n");
}
void nodeTimeAdjustedCallback(int32_t offset)
{
  Serial.printf("Adjusted time %u. Offset = %d\n", mesh.getNodeTime(), offset);
}

void setup() 
{
  Serial.begin(115200);
  pinMode(Relay1, OUTPUT);
  mesh.setDebugMsgTypes( ERROR | STARTUP );                           // set before init() so that you can see startup messages
  mesh.init( MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT );
  mesh.onReceive(&receivedCallback);
  mesh.onNewConnection(&newConnectionCallback);
  mesh.onChangedConnections(&changedConnectionCallback);
  mesh.onNodeTimeAdjusted(&nodeTimeAdjustedCallback);
  userScheduler.addTask( taskSendMessage );
  taskSendMessage.enable();
}

void loop() 
{
  mesh.update();
}


Code for Node3:
#include "painlessMesh.h"
                                                       // WiFi Credentials
#define   MESH_PREFIX     "whateverYouLike"
#define   MESH_PASSWORD   "somethingSneaky"
#define   MESH_PORT       5555
                                                        //Pin Declaration
#define Relay2 D5
                                                         //Variables
bool relay2_status = 0;
Scheduler userScheduler; 
painlessMesh  mesh;
void sendMessage() ;
Task taskSendMessage( TASK_SECOND * 1 , TASK_FOREVER, &sendMessage );
void sendMessage()
{
}
                                                              //painless library

void receivedCallback( uint32_t from, String &msg ) {
  String json;
  DynamicJsonDocument doc(1024);
  json = msg.c_str();
  DeserializationError error = deserializeJson(doc, json);
  if (error)
  {
    Serial.print("deserializeJson() failed: ");
    Serial.println(error.c_str());
  }
  relay2_status = doc["Relay2"];
  digitalWrite(Relay2, relay2_status);
  Serial.printf("From Node3");
}

void newConnectionCallback(uint32_t nodeId)
{
  Serial.printf("--> startHere: New Connection, nodeId = %u\n", nodeId);
}

void changedConnectionCallback()
{
  Serial.printf("Changed connections\n");
}

void nodeTimeAdjustedCallback(int32_t offset) 
{
  Serial.printf("Adjusted time %u. Offset = %d\n", mesh.getNodeTime(), offset);
}

void setup() 
{
  Serial.begin(115200);
  pinMode(Relay2, OUTPUT);
  mesh.setDebugMsgTypes( ERROR | STARTUP );
  mesh.init( MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT );
  mesh.onReceive(&receivedCallback);
  mesh.onNewConnection(&newConnectionCallback);
  mesh.onChangedConnections(&changedConnectionCallback);
  mesh.onNodeTimeAdjusted(&nodeTimeAdjustedCallback);
  userScheduler.addTask( taskSendMessage );
  taskSendMessage.enable();
}

void loop()
{
  mesh.update();
}
