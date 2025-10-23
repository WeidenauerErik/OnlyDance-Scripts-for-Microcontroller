#include <WiFi.h>
#include <WiFiUdp.h>

const char* ssid = "OnlyDance-AP";
const char* password = "12345678";

WiFiUDP Udp;
unsigned int localUdpPort = 4210;
char incomingPacket[255];

void setup() {
  Serial.begin(19200);
  delay(1000);

  Serial.println("")
  Serial.println("Starte Access Point...");
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP-Adresse: ");
  Serial.println(IP);

  Udp.begin(localUdpPort);
  Serial.println("UDP Server läuft.");
}

void loop() {
  int packetSize = Udp.parsePacket();
  if (packetSize) {
    int len = Udp.read(incomingPacket, 255);
    if (len > 0) {
      incomingPacket[len] = '\0';
    }

    String msg = String(incomingPacket);
    Serial.println("Empfangen: " + msg);  
  }
}