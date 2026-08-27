#include <WiFi.h>
#include <WebServer.h>

// --- WiFi Credentials ---
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// --- Relay Pins ---
#define RELAY1 26   // GPIO for Relay 1
#define RELAY2 27   // GPIO for Relay 2

WebServer server(80);

void handleOn() {
  digitalWrite(RELAY1, LOW);  // Active LOW relay
  digitalWrite(RELAY2, LOW);
  server.send(200, "text/plain", "Lights ON");
}

void handleOff() {
  digitalWrite(RELAY1, HIGH);
  digitalWrite(RELAY2, HIGH);
  server.send(200, "text/plain", "Lights OFF");
}

void setup() {
  Serial.begin(115200);

  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);

  digitalWrite(RELAY1, HIGH); // Default OFF
  digitalWrite(RELAY2, HIGH);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected!");
  Serial.print("ESP32 IP: ");
  Serial.println(WiFi.localIP());

  server.on("/on", handleOn);
  server.on("/off", handleOff);
  server.begin();
}

void loop() {
  server.handleClient();
}
