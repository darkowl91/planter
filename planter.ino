/*
 Smart Flower Controller based on LoLin new NodeMcu v3(ESP-12E) board
 Board Manager: http://arduino.esp8266.com/stable/package_esp8266com_index.json
 Upload speed: 115200

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
#include <SSD1306.h>
#include <timer.h>
#include "Secrets.h"
#include "Images.h"

// PIN
const int moiPin = 0;  // A0
const int sdaPin = 5;  // D1
const int sclPin = 4;  // D2
const int ledPin = 14; // D5
const int btnPin = 12; // D6
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

// sensors update timer
auto timer = timer_create_default();

// button state
int btnState = LOW;
long btnPressTime = -1;

// display frames
typedef void (*Frame)(void);

void drawTemperature()
{
  display.setFont(ArialMT_Plain_10);
  display.drawString(30, 0, "Temperature");

  int x = 15;
  display.setFont(ArialMT_Plain_24);
  display.drawString(x + 15, 18, String(t));

  display.setFont(ArialMT_Plain_10);
  display.drawString(x + 40, 18, "O");

  display.setFont(ArialMT_Plain_16);
  display.drawString(x + 50, 25, "C");

  display.drawXbm(x + 70, 18, img_temp_width, img_temp_height, img_temp_bits);
}

void drawHumidity()
{
  display.setFont(ArialMT_Plain_10);
  display.drawString(35, 0, "Humidity");

  int x = 15;
  display.setFont(ArialMT_Plain_24);
  display.drawString(x + 15, 18, String(h));

  display.setFont(ArialMT_Plain_16);
  display.drawString(x + 45, 25, "%");

  display.drawXbm(x + 60, 18, img_hum_width, img_hum_height, img_hum_bits);
}

void drawSoilMoisture()
{
  display.setFont(ArialMT_Plain_10);
  display.drawString(44, 0, "Soil");

  int x = 15;
  display.setFont(ArialMT_Plain_24);
  display.drawString(x + 15, 18, String(m));

  display.drawXbm(x + 60, 18, img_soil_width, img_soil_height, img_soil_bits);
}

Frame frames[] = {drawTemperature, drawHumidity, drawSoilMoisture};
int frameSize = (sizeof(frames) / sizeof(Frame));
int frameNum = 0;

void setup()
{
  Serial.begin(115200);
  delay(10);
  Serial.println("\nStart excecuting setup...");
  // set ledPin mode
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
  pinMode(btnPin, INPUT);
  // set display
  display.init();
  display.setFont(ArialMT_Plain_10);
  display.flipScreenVertically();

  // setup timer
  timer.every(3600, updateSensors);
}

void loop()
{
  timer.tick();

  bool isNextFrame = isBtnPressed();
  displayFrame(isNextFrame);
}

void displayFrame(bool isNextFrame)
{
  if (isNextFrame)
  {
    if (frameNum < frameSize - 1)
    {
      frameNum++;
    }
    else
    {
      frameNum = 0;
    }

    Serial.println("Display frame: " + String(frameNum) + "from: " + String(frameSize));

    display.clear();
    frames[frameNum]();
    display.display();
  }
}

bool isBtnPressed()
{
  int debounce = 20;
  bool isPressed = false;
  int value = digitalRead(btnPin);

  if (value == HIGH && btnState == LOW && (millis() - btnPressTime > debounce))
  {
    isPressed = true;
    Serial.println("Button pressed");
    btnPressTime = millis();
  }

  btnState = value;

  return isPressed;
}

bool updateSensors(void *)
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

  Serial.println("Update sensors -> t: " + String(t) + " h: " + String(h) + " m: " + String(m));
  return true;
}
