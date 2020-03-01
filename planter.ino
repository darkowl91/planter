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

#include <FirebaseESP8266.h>
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

//Firebase
FirebaseData firebaseData;
char firbaseAuth[] = FIREBASE_AUTH;
char firbaseHost[] = FIREBASE_HOST;

// sensors update timer
auto timer = timer_create_default();

// button state
int btnState = LOW;
long btnPressTime = -1;

// display frames
typedef void (*Frame)(void);

void drawTitle(String title)
{
  display.setFont(ArialMT_Plain_10);
  display.drawString(0, 0, title);
  if (WiFi.status() == WL_CONNECTED)
  {
    display.drawXbm(110, 0, img_wifi_on_width, img_wifi_on_height, img_wifi_on_bits);
  }
  else
  {
    display.drawXbm(110, 0, img_wifi_off_width, img_wifi_off_height, img_wifi_off_bits);
  }
}

void drawTemperature()
{
  drawTitle("Temperature");

  int x = 15;
  int y = 15;
  display.setFont(ArialMT_Plain_24);
  display.drawString(x + 15, y + 18, String(t));
  display.setFont(ArialMT_Plain_10);
  display.drawString(x + 40, y + 18, "O");
  display.setFont(ArialMT_Plain_16);
  display.drawString(x + 50, y + 25, "C");
  display.drawXbm(x + 70, y + 18, img_temp_width, img_temp_height, img_temp_bits);
}

void drawHumidity()
{
  drawTitle("Humidity");

  int x = 15;
  int y = 15;
  display.setFont(ArialMT_Plain_24);
  display.drawString(x + 15, y + 18, String(h));

  display.setFont(ArialMT_Plain_16);
  display.drawString(x + 45, y + 25, "%");
  display.drawXbm(x + 70, y + 18, img_hum_width, img_hum_height, img_hum_bits);
}

void drawSoilMoisture()
{
  drawTitle("Soil");

  int x = 15;
  int y = 15;
  display.setFont(ArialMT_Plain_24);
  display.drawString(x + 15, y + 18, String(m));
  display.drawXbm(x + 70, y + 18, img_soil_width, img_soil_height, img_soil_bits);
}

Frame frames[] = {drawTemperature, drawHumidity, drawSoilMoisture};
int frameSize = (sizeof(frames) / sizeof(Frame));
int frameNum = 0;

void setup()
{
  Serial.begin(115200);
  delay(10);
  Serial.println("\nStart excecuting setup...");
  Serial.print("MAC: ");
  Serial.println(WiFi.macAddress());

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

  // setup wifi connection
  connectWiFiAP();

  // setup firebase connection
  connectFirebase();
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

    Serial.println("Display frame: " + String(frameNum) + " from: " + String(frameSize));

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

  Firebase.set(firebaseData, "planters/planter-1/temperature", t);
  Firebase.set(firebaseData, "planters/planter-1/humidity", h);
  Firebase.set(firebaseData, "planters/planter-1/soil-moisture", m);

  return true;
}

void connectWiFiAP()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  int attempts = 0;

  while (WiFi.status() != WL_CONNECTED && attempts < 20)
  {
    digitalWrite(ledPin, LOW);
    delay(100);
    digitalWrite(ledPin, HIGH);
    attempts++;
  }

  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.print("Could not connect to: ");
    Serial.println(ssid);
    return;
  }

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void connectFirebase()
{
  Firebase.begin(firbaseHost, firbaseAuth);
  Firebase.reconnectWiFi(true);
  if (!Firebase.beginStream(firebaseData, "planters/planter-1"))
  {
    Serial.println("Could not begin stream");
    Serial.println("REASON: " + firebaseData.errorReason());
  }
}

bool blink(void *)
{
  digitalWrite(ledPin, !digitalRead(ledPin));
  return true;
}
