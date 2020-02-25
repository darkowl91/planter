/*
 Smart Flower Controller based on LoLin new NodeMcu v3(ESP-12E) board
 Board Manager: http://arduino.esp8266.com/stable/package_esp8266com_index.json
 Upload speed: 115200
 CPU frequency: 80MHz

 PINS:
 * A0 - Soil moisture sensor
 * D1 - SDA
 * D2 - SLC
 * D5 - LED
 * D6 - Touch btn
 * D7 - DHT data
 */

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <SimpleDHT.h>
#include "SSD1306.h"
#include "Secrets.h"
#include "Images.h"

// PIN
const int moiPin = 0;  // A0
const int sdaPin = 5;  // D1
const int sclPin = 4;  // D2
const int ledPin = 14; // D5
const int bntPin = 12; // D6
const int dhtPin = 13; // D7

// WIFI
char ssid[] = SSID;
char password[] = PASSWORD;

// DHT
SimpleDHT11 dht11(dhtPin);

// OLED Display
SSD1306Wire display(0x3c, sdaPin, sclPin);

int t; // temperature
int h; // humidity
int m; // soil moisture

// sensors intervals
long lastTimeSensorUpdate = 0;
int updateInterval = 3600000; // 1h

void setup()
{
  Serial.begin(115200);
  delay(10);
  Serial.println("\nStart excecuting setup...");
  // set ledPin mode
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
  // set display
  display.init();
  display.setFont(ArialMT_Plain_10);
  display.flipScreenVertically();
}

void loop()
{
  display.clear();

  updateSensors();

  drawValues();
  display.display();

  delay(10);
}

void drawValues()
{
  display.drawString(0, 15, "Temperature: " + String(t));
  display.drawString(0, 25, "Humidity: " + String(h));
  display.drawString(0, 35, "Moisture: " + String(m));
}

void updateSensors()
{
  if ((millis() > lastTimeSensorUpdate + updateInterval) || lastTimeSensorUpdate == 0)
  {
    byte temperature = 0;
    byte humidity = 0;
    int err = SimpleDHTErrSuccess;
    if ((err = dht11.read(&temperature, &humidity, NULL)) == SimpleDHTErrSuccess)
    {
      t = (int)temperature;
      h = (int)humidity;
    }

    m = analogRead(moiPin);

    lastTimeSensorUpdate = millis();
  }
}
