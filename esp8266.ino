#include <Wire.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Adafruit_Sensor.h>
#include <TSL2561.h>
#include <Adafruit_BME280.h>
#include <SparkFunTMP102.h>

// Configuration
#define WIFI_SSID ""
#define WIFI_PASS ""
#define WEB_SERVER_PORT 80
#define I2C_ADDR_TSL2561 0x39
#define I2C_ADDR_BME280 0x76
#define I2C_ADDR_TMP102 0x48

// Web server
ESP8266WebServer webServer(WEB_SERVER_PORT);

// Sensors
TSL2561 tsl2561(I2C_ADDR_TSL2561);
Adafruit_BME280 bme280;
TMP102 tmp102(I2C_ADDR_TMP102);

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

  // Read illuminance (lx)
  float visible = tsl2561.getLuminosity(TSL2561_VISIBLE);
  float full = tsl2561.getLuminosity(TSL2561_FULLSPECTRUM);
  float ir = tsl2561.getLuminosity(TSL2561_INFRARED);

  // Read temperature (°C)
  float temperature = readTemperature();

  // Read humidity (%)
  float humidity = bme280.readHumidity();

  // Read pressure (hPa)
  float pressure = bme280.readPressure() / 100;

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
  response += ",\"temperature\":";
  response += temperature;
  response += ",\"humidity\":";
  response += humidity;
  response += ",\"pressure\":";
  response += pressure;
  response += "}";

  // Send response
  webServer.send(200, "application/json", response);
}

float readTemperature() {
  float bme280Temperature = bme280.readTemperature();
  float tmp102Temperature = tmp102.readTempC();

  return (tmp102Temperature + tmp102Temperature + bme280Temperature) / 3;
}

void setupWiFi()
{
  Serial.println("[WiFi] Setup");
  Serial.print("[WiFi] Connecting to: ");
  Serial.println(WIFI_SSID);

  WiFi.begin(WIFI_SSID, WIFI_PASS);
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

void setupSensors()
{
  setupSensorTSL2561();
  setupSensorBME280();
  setupSensorTMP102();
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

void setupSensorBME280()
{
  Serial.println("[BME280] Setup");
  Serial.print("[BME280] Connecting..");

  while (!bme280.begin(I2C_ADDR_BME280))
  {
    delay(200);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("[BME280] Connected!");
}

void setupSensorTMP102()
{
  Serial.println("[TMP102] Setup");
  Serial.println("[TMP102] Connecting..");

  tmp102.begin();

  Serial.println("[TMP102] Assuming connected!");
}
