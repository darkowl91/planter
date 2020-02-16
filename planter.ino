/*
 Smart Flower Controller based on LoLin new NodeMcu v3(ESP-12E) board
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
  display.clear();

  byte t = 0, h = 0;
  readDHT(&t, &h);

  display.drawString(0, 20, "Temperature: " + String((int)t));
  display.drawString(0, 30, "Humidity: " + String((int)h));

  display.display();
  delay(10);
}

int readDHT(byte *temperature, byte *humidity)
{
  Serial.println("Read DHT11...");

  int result = SimpleDHTErrSuccess;
  if ((result = dht11.read(temperature, humidity, NULL)) != SimpleDHTErrSuccess)
  {
    Serial.print("Error read dht: ");
    Serial.println(result);
    delay(1000);
    return result;
  }

  Serial.print("DHT11: ");
  Serial.print((int)*temperature);
  Serial.print(" C, ");
  Serial.print((int)*humidity);
  Serial.println(" H");

  // DHT11 sampling rate is 1HZ.
  delay(1500);
  return result;
}
