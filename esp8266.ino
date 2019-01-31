#include <Wire.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <TSL2561.h>

// WiFi configuration
const char *ssid = "";
const char *password = "";

// Web server
ESP8266WebServer webServer(80);

// Sensors
TSL2561 tsl2561(TSL2561_ADDR_FLOAT);

void setup()
{
  // Setup I2C
  Wire.begin(D2, D1);

  // Setup Serial
  Serial.begin(9600);
  Serial.println();

  setupWiFi();
  setupWebServer();
  setupSensors();
}

void loop()
{
  webServer.handleClient();
}

void handleRoot()
{
  Serial.println("[WebServer] Request: /");

  // Read illuminance
  float visible = tsl2561.getLuminosity(TSL2561_VISIBLE);
  float full = tsl2561.getLuminosity(TSL2561_FULLSPECTRUM);
  float ir = tsl2561.getLuminosity(TSL2561_INFRARED);

  // Build response
  String response = "";
  response += "{";
  response += "\"illuminance\":{";
  response += "\"visible\":";
  response += visible;
  response += ",\"full\":";
  response += full;
  response += ",\"ir\":";
  response += ir;
  response += "}";
  response += "}";

  // Send response
  webServer.send(200, "application/json", response);
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

void setupSensorTSL2561()
{
  Serial.println("[TSL2561] Setup");
  Serial.print("[TSL2561] Connecting..");

  while (!tsl2561.begin())
  {
    delay(200);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("[TSL2561] Connected!");
}

void setupSensors()
{
  setupSensorTSL2561();
}
