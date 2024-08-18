# LoRa-transceiver
DHT11 and MPU6050 live data transmission with lora


PINOUTS:

MPU6050:
VCC  -> 3.3V/5V  ||
GND  -> GND  ||
SDA  -> A4  ||
SCL  -> A5  ||
INT  -> D2 (optional)

DHT11:
VCC  -> 5V ||
GND  -> GND ||
DATA -> D7 ||

LoRa Module:
VCC  -> 3.3V ||
GND  -> GND ||
NSS  -> D10 ||
SCK  -> D13 ||
MISO -> D12 ||
MOSI -> D11 ||
RST  -> D9 ||
DIO0 -> D2 ||
