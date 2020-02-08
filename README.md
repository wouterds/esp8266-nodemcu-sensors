# ESP8266 NodeMCU Sensors API

Basic example how to output sensor readings as a JSON API using an ESP8266 NodeMCU module and some sensors.

## Hardware

Everything on the picture below was bought on ebay for about $10 in total.

![Hardware Setup](https://wouterdeschuyter.be/static/media/7d4b6e21-5a94-4166-9fff-55c653fbb57e.jpg)

### Sensors

- BME280 (temperature, pressure, humidity)
- TMP102 (temperature; but more accurate than the BME280)
- TSL2561 (illuminance; full spectrum, ir spectrum & visible spectrum)

## Output

When browsing to the IP of the module you will see a similar output as below.

```json
{
  "illuminance": {
    "visible": 905.0,
    "full": 1255.0,
    "ir": 347.0
  },
  "temperature": 24.51,
  "humidity": 37.49,
  "pressure": 1027.82
}
```
