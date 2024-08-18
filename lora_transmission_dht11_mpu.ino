#include <Wire.h>
#include <MPU6050.h>
#include <LoRa.h>
#include <DHT.h>


#define DHTPIN 4        
#define DHTTYPE DHT11   
DHT dht(DHTPIN, DHTTYPE);

const int MPU6050InterruptPin = 3; 

MPU6050 mpu;

unsigned long previousMillis = 0;
const long interval = 500; 

void setup() {
  
  Wire.begin();
  Serial.begin(9600);

  mpu.initialize();
  pinMode(MPU6050InterruptPin, INPUT);
  if (mpu.testConnection()) {
    Serial.println("MPU6050 connection successful");
  } else {
    Serial.println("MPU6050 connection failed");
  }

  dht.begin();

  if (!LoRa.begin(433E6)) { 
    Serial.println("LoRa initialization failed");
    while (1);
  }
  Serial.println("LoRa initialized successfully");
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // Read MPU6050 data
    int16_t ax, ay, az;
    int16_t gx, gy, gz;
    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();

    String data = String("AX:") + ax + ", AY:" + ay + ", AZ:" + az;
    data += String(", GX:") + gx + ", GY:" + gy + ", GZ:" + gz;
    data += String(", Temp:") + temperature + "C, Humidity:" + humidity + "%";

    LoRa.beginPacket();
    LoRa.print(data);
    LoRa.endPacket();

    
    Serial.println("Data sent: " + data);
  }
}

 /*
MPU6050:
VCC  -> 3.3V or 5V
GND  -> GND
SDA  -> A4
SCL  -> A5
INT  -> D2 (op)

DHT11:
VCC  -> 5V
GND  -> GND
DATA -> D7

LoRa Module:
VCC  -> 3.3V
GND  -> GND
NSS  -> D10
SCK  -> D13
MISO -> D12
MOSI -> D11
RST  -> D9
DIO0 -> D2 
*/