/*
 *  This sketch receive a message to a TCP server
 *
 */

#include <WiFi.h>
#include <ArduinoJson.h>

const char* wlan_ssid     = "DESKTOP-Jan-MobilerHotspot";
const char* wlan_password = "L5;1n787";

void setup() {
  Serial.begin(115200);
  Serial.println("Welcome to CHESSCLOCK");
  setupWifi();
}

String req = "";

void loop() {
  checkbutton();
  checkincomping();
}

void checkbutton(){
  insertDB(23, 1234);
  delay(5000);
}
int valueInc = 0;

void insertDB(int sensor, int value){

  // Define the PORT of the TCP-Server
  const uint16_t port = 80;
  
  // Define the IP of the TCP-Server
  const char * host = "http://jan-patrick.de/chess/database"; 
  
  // WiFiClient instance
  WiFiClient client;

  if (!client.connected()) { 
    client.connect(host, 80);
  }

  // JSON-STRING FOR THE HTTP-POST
  value = value + valueInc;
  valueInc ++;
  String PostData = "{\"sensor\": \"" + String(sensor) + "\", \"value\": \"" + String(value) + "\"}"; // your JSON payload

  Serial.println(PostData);

  // CONNECT TO THE TCP-SERVER
  if (client.connected()) {

    // HTTP-POST URL
    client.println("POST /arduino/add.php HTTP/1.1"); 
    client.println("Host: http://jan-patrick.de/chess/database"); 
    client.println("Content-Type: application/json");

    // Length of the JSON-String
    client.print("Content-Length: ");
    client.println(PostData.length());// number of bytes in the payload
    client.println();// important need an empty line here 
    
    // HTTP-POST JSON-STRING
     
  }

  // DISCONNECT FROM THE SERVER IF CONNECT
  if (client.connected()) { 
    client.stop();  
  }
}

void printJson(String jsonString){
  const size_t capacity = JSON_OBJECT_SIZE(3) + JSON_ARRAY_SIZE(2) + 60;
  DynamicJsonBuffer jsonBuffer(capacity);

  JsonObject& root = jsonBuffer.parseObject(jsonString);
  
  Serial.print(String("Sensor: ") + root["sensor"].as<char*>());
  Serial.println(String(" – Value: ") + root["value"].as<char*>());
}

void setupWifi() 
{
  delay(100);
  // We start by connecting to a WiFi network
  Serial.print("Connecting to ");
  Serial.println(wlan_ssid);

  // Connect to the SSID and loop until connected
  // Connect to WiFi network
  WiFi.begin(wlan_ssid, wlan_password);
  Serial.print("\n\r \n\rWorking to connect");
 
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".\n");
  }
  
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}


