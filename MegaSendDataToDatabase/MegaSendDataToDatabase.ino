/*
 send test data to E-CHESS test database

 This sketch sends test data to the e-chess turn database.
 e-chess is a project by Marcus Schoch and Jan Schneider.

 https://www.jan-patrick.de/e-chess
 */

#include <SPI.h>
#include <Ethernet.h>
#include <ArduinoJson.h>

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
char server[] = "www.jan-patrick.de";    // name address for Google (using DNS)

// Set the static IP address to use if the DHCP fails to assign
IPAddress ip(192, 168, 0, 177);

// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;

String from = "";
String to = "";
String PostData = "";
char* SQUARESbestMOVE[] = {"a8","b8","c8","d8","e8","f8","g8","h8","a7","b7","c7","d7","e7","f7","g7","h7","a6","b6","c6","d6","e6","f6","g6","h6","a5","b5","c5","d5","e5","f5","g5","h5","a4","b4","c4","d4","e4","f4","g4","h4","a3","b3","c3","d3","e3","f3","g3","h3","a2","b2","c2","d2","e2","f2","g2","h2","a1","b1","c1","d1","e1","f1","g1","h1"};

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip);
  }
  // give the Ethernet shield a second to initialize:
  delay(1000);
  Serial.print("My IP address: ");
  Serial.println(Ethernet.localIP());
  Serial.println("connecting...");
}

void loop() {
  // if there's incoming data from the net connection.
  // send it out the serial port.  This is for debugging
  // purposes only:
  if (client.available()) {
    char c = client.read();
    Serial.print(c);
  }

  // if ten seconds have passed since your last connection,
  // then connect again and send data:
  httpRequest();
  delay(15000);
}

// this method makes a HTTP connection to the server:
void httpRequest() {
  if (!client.connected()) { 
    client.connect(server, 80);
  }
  // if there's a successful connection:
  if (client.connected()) {
    Serial.println("starting printing");
    createValues();

    // HTTP-POST URL
    client.println("POST /e-chess/database/add.php HTTP/1.1"); 
    client.println("Host: jan-patrick.de"); 
    client.println("Content-Type: application/json");

    // Length of the JSON-String
    client.print("Content-Length: ");
    client.println(PostData.length());// number of bytes in the payload
    client.println();// important need an empty line here 
    
    // HTTP-POST variables
    client.println(PostData);
    Serial.println("printing ended");
  }

  // DISCONNECT FROM THE SERVER IF CONNECT
  if (client.connected()) { 
    Serial.println("DISCONNECTED");
    client.stop();  
  }
}

void createValues(){
  from = SQUARESbestMOVE[random(sizeof(SQUARESbestMOVE))];
  to = SQUARESbestMOVE[random(sizeof(SQUARESbestMOVE))];
  while(from == to){
    to = SQUARESbestMOVE[random(sizeof(SQUARESbestMOVE))];
  }
  PostData = "{\"source\": \"" + from + "\", \"target\": \"" + to + "\"}";
  Serial.println(PostData);
}
