/*
 CI Build Traffic Light Controller based on LoLin new NodeMcu v3(ESP-12E) board
 Board Manager: http://arduino.esp8266.com/stable/package_esp8266com_index.json
 Upload speed: 115200
 CPU frequency: 80MHz

 PINS:
 * D1 - SDA
 * D2 - SLC
 * D3 - DHT data
 * D4 - Soil moisture sensor
 * D5 - LED
 */

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <SimpleDHT.h>
#include "SSD1306.h"
#include "Secrets.h"
#include "Images.h"

// PIN
const int ledPin = 14; // D5
const int dhtPin = 0;  // D3
const int sdaPin = 5;  // D1
const int sclPin = 4;  // D2
const int moiPin = 2;  // D4

// WIFI
char ssid[] = SSID;
char password[] = PASSWORD;

// DHT
SimpleDHT11 dht11(dhtPin);

// OLED Display
SSD1306Wire display(0x3c, sdaPin, sclPin);

void setup()
{
  Serial.begin(115200);
  delay(10);
  Serial.println("\nStart excecuting setup");
  // set ledPin mode
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  // set display
  display.init();
  display.setFont(ArialMT_Plain_10);
  display.flipScreenVertically();
}

void loop()
{
}
