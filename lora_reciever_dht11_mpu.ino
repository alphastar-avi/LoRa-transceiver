#include <SPI.h>
#include <LoRa.h>

#define NSS 10
#define SCK 13
#define MISO 12
#define MOSI 11
#define RST 9
#define DIO0 2

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Set up LoRa transceiver module
  LoRa.setPins(NSS, RST, DIO0);
  if (!LoRa.begin(433E6)) {  // Initialize LoRa at 433 MHz
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  Serial.println("LoRa receiver initialized.");
}

void loop() {
  // Check if there are any incoming LoRa packets
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    String receivedData = "";
    
    // Read the packet into a String
    while (LoRa.available()) {
      receivedData += (char)LoRa.read();
    }
    
    // Print the received data to the Serial Monitor
    Serial.print("Received packet: ");
    Serial.println(receivedData);
    
    // Here, you could parse the received data if needed
    // For example, split by commas and print individual sensor values
    parseAndPrintData(receivedData);
  }
}


void parseAndPrintData(String data) {
  Serial.println("Parsing data...");
  

  int startIndex = 0;
  int endIndex = data.indexOf(',', startIndex);
  
  while (endIndex > 0) {
    Serial.println(data.substring(startIndex, endIndex));
    startIndex = endIndex + 1;
    endIndex = data.indexOf(',', startIndex);
  }
  Serial.println(data.substring(startIndex)); 
  
  Serial.println("Data parsed.");
}