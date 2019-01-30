#include <ESP8266WiFi.h>

// WiFi configuration
const char *ssid = "";
const char *password = "";

void setup()
{
  // Setup Serial
  Serial.begin(9600);
  Serial.println();

  setupWiFi();
}

void loop()
{
}

void setupWiFi()
{
  Serial.println("[WiFi] Setup");
  Serial.print("[WiFi] Connecting to: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(200);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("[WiFi] Connected!");
  Serial.print("[WiFi] IP: ");
  Serial.println(WiFi.localIP());
}
