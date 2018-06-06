/*
 *  This sketch sends test data to the sense-chess turn database.
 *  sense-chess is a project by Marcus Schoch and Jan Schneider.
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
}

void checkbutton(){
  insertDB(23, 1234);
  delay(15000);
}
int valueInc = 0;

void insertDB(int sensor, int value){

  // Define the PORT of the TCP-Server
  const uint16_t port = 80;
  
  // Define the IP of the TCP-Server
  const char * host = "jan-patrick.de"; 
  
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
    client.println("POST /sense-chess/database/add.php HTTP/1.1"); 
    client.println("Host: jan-patrick.de"); 
    client.println("Content-Type: application/json");

    // Length of the JSON-String
    client.print("Content-Length: ");
    client.println(PostData.length());// number of bytes in the payload
    client.println();// important need an empty line here 
    
    // HTTP-POST JSON-STRING
    //printJson(PostData);
    client.println(printJson(PostData));
  }

  // DISCONNECT FROM THE SERVER IF CONNECT
  if (client.connected()) { 
    Serial.println("DISCONNECTED");
    client.stop();  
  }
}

String printJson(String jsonString){
  const size_t capacity = JSON_OBJECT_SIZE(3) + 61;
  DynamicJsonBuffer jsonBuffer(capacity);

  JsonObject& root = jsonBuffer.parseObject(jsonString);
  
  Serial.print(String("Sensor: ") + root["sensor"].as<char*>());
  Serial.println(String("Value: ") + root["value"].as<char*>());

  char jsonChar[100];
  root.printTo((char*)jsonChar, root.measureLength() + 1);
  Serial.println(jsonChar);
  return jsonChar;
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
