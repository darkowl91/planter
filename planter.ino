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

void setup()
{
  Serial.begin(115200);
  delay(10);
  Serial.println("\nStart excecuting setup...");
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

  display.drawString(0, 15, "Temperature: " + String((int)t));
  display.drawString(0, 25, "Humidity: " + String((int)h));

  int moi = readMoisture();
  display.drawString(0, 35, "Moisture: " + String(moi));

  display.display();
  delay(10);

  blink();

  if (digitalRead(bntPin) == 1)
  {
    Serial.println("\nTouch");
  }
}

int readDHT(byte *temperature, byte *humidity)
{
  Serial.print("\nRead DHT11: ");

  int result = SimpleDHTErrSuccess;
  if ((result = dht11.read(temperature, humidity, NULL)) != SimpleDHTErrSuccess)
  {
    Serial.print("Error read dht ");
    Serial.println(result);
    delay(1000);
    return result;
  }

  Serial.print((int)*temperature);
  Serial.print(" C, ");
  Serial.print((int)*humidity);
  Serial.println(" H");

  // DHT11 sampling rate is 1HZ.
  delay(1500);
  return result;
}

int readMoisture()
{
  Serial.print("\nRead Moisture: ");
  int moi = analogRead(moiPin);
  Serial.println(moi);

  return moi;
}

void blink()
{
  digitalWrite(ledPin, HIGH);
  delay(300);
  digitalWrite(ledPin, LOW);
}
