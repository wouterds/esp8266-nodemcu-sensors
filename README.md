# ESP8266 NodeMCU Sensors API

Basic example how to output sensor readings as a JSON API using an ESP8266 NodeMCU module and some sensors.

## Hardware

Everything on the picture below was bought on ebay for about $10 in total.

![Hardware Setup](https://i.imgur.com/mS9Tymc.gif)

### Sensors

- BME280 (temperature, pressure, humidity)
- HTU21DF (temperature & humidity; but more accurate than the BME280)
- TSL2561 (illuminance; full spectrum, ir spectrum & visible spectrum)

### RGB led

The led rotates through all colors on each request, just found it a funny effect.<br />
But it can be enabled / disabled using a `POST` call to the `/led` endpoint.

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
