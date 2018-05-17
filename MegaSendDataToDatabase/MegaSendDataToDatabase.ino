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

String from = "a2";
String to = "a4";

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
    String PostData = "{\"source\": \"" + from + "\", \"target\": \"" + to + "\"}";

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
  }

  // DISCONNECT FROM THE SERVER IF CONNECT
  if (client.connected()) { 
    Serial.println("DISCONNECTED");
    client.stop();  
  }
}
