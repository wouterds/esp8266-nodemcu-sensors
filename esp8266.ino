#include <Wire.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// WiFi configuration
const char *ssid = "";
const char *password = "";

// Web server
ESP8266WebServer webServer(80);

void setup()
{
  // Setup I2C
  Wire.begin(D1, D2);

  // Setup Serial
  Serial.begin(9600);
  Serial.println();

  setupWiFi();
  setupWebServer();
}

void loop()
{
  webServer.handleClient();
}

void handleRoot()
{
  Serial.println("[WebServer] Request: /");
  webServer.send(200, "text/plain", "Hello World!");
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

void setupWebServer()
{
  Serial.println("[WebServer] Setup");
  webServer.on("/", handleRoot);

  Serial.println("[WebServer] Starting..");
  webServer.begin();
  Serial.println("[WebServer] Running!");
}
