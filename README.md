# ESP8266 NodeMCU Sensors API

Basic example how to output sensor readings as a JSON API using an ESP8266 NodeMCU module and some sensors. Everything on the picture below was bought from ebay for no more than $10.

![Breadboard setup](https://i.imgur.com/wLqQVrZ.jpg)

## Sensors

- BME280 (temperature, pressure, humidity)
- TMP102 (temperature; but more accurate than the BME280)
- TSL2561 (illuminance; full spectrum, ir spectrum & visible spectrum)

## Output

When browsing to the IP of the module you will see a similar output as below.

```json
{
  "illuminance": {
    "visible": 10.0,
    "full": 11.0,
    "ir": 2.0
  },
  "temperature": 20.78,
  "humidity": 35.17,
  "pressure": 1023.67
}
```
