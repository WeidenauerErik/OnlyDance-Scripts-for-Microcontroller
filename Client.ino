#include <WiFi.h>
#include <WiFiUdp.h>

const char* ssid = "OnlyDance-AP";
const char* password = "12345678";

IPAddress localIP(192,168,4,2);
IPAddress gateway(192,168,4,1);
IPAddress subnet(255,255,255,0);

const char* esp32_ip = "192.168.4.1";
const unsigned int esp32_port = 4210;

WiFiUDP Udp;
unsigned long lastSend = 0;

void setup() {
  Serial.begin(4800);
  delay(2000);

  Serial.println("Verbinde mit Access Point...");
  WiFi.config(localIP, gateway, subnet);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Verbunden!");
  Serial.print("Arduino IP: ");
  Serial.println(WiFi.localIP());

  Udp.begin(4211);
  Serial.println("UDP Client gestartet.");
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - lastSend > 2000) {
    lastSend = currentMillis;

    int randomInt = random(1, 100);
    String msg = String(randomInt);

    Udp.beginPacket(esp32_ip, esp32_port);
    Udp.print(msg);
    Udp.endPacket();

    Serial.println("Gesendet: " + msg);
  }

  int packetSize = Udp.parsePacket();
  if (packetSize) {
    char buffer[255];
    int len = Udp.read(buffer, 255);
    if (len > 0) buffer[len] = '\0';
    Serial.print("Antwort: ");
    Serial.println(buffer);
  }
}