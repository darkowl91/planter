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

#include <Arduino.h>
#include <FirebaseESP8266.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <SSD1306.h>
#include <timer.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include "Secrets.h"
#include "Images.h"

// PIN
const int moiPin = 0;  // A0
const int sdaPin = 5;  // D1
const int sclPin = 4;  // D2
const int ledPin = 14; // D5
const int btnPin = 12; // D6
const int dhtPin = 13; // D7

// logging
bool printSerail = false;

// WIFI
char ssid[] = SSID;
char password[] = PASSWORD;

// Climate sensor
Adafruit_BME280 bme;

// OLED Display
SSD1306Wire display(0x3c, sdaPin, sclPin);

// display idle timout: 2min
long displayIdleTime = 120000;

// display last time active
long displayLastUpdate = -1;

// updates timer: sensors refersh, push data to firebae
Timer<2, millis> timer;

float t(NAN);      // temperature
float h(NAN);      // humidity
float p(NAN);      // pressure

int m;             // soil moisture
int m_air = 625;   // air value for soil
int m_water = 197; // water value for soil

//Firebase
FirebaseData firebaseData;
FirebaseJson firebaseJSON;
char planterPath[] = PLANTER_PATH;
char firbaseAuth[] = FIREBASE_AUTH;
char firbaseHost[] = FIREBASE_HOST;

// button state
int btnState = LOW;
long btnPressTime = -1;

// NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "by.pool.ntp.org", 10800, 60000); // GTM+3

// display frames
typedef void (*Frame)(void);

void drawTitle(String title)
{
  display.setFont(ArialMT_Plain_10);
  display.drawString(0, 0, title);
  if (WiFi.status() == WL_CONNECTED)
  {
    display.drawString(70, 0, timeClient.getFormattedTime());
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

void drawPressure()
{
  drawTitle("Pressure");
  //  TODO  
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

Frame frames[] = {drawTemperature, drawHumidity, drawSoilMoisture, drawPressure};
int frameSize = (sizeof(frames) / sizeof(Frame));
int frameNum = 0;

void setup()
{
  Serial.begin(115200);
  delay(10);
  log("\nStart excecuting setup...");
  log("MAC: ");
  log(WiFi.macAddress());

  // set ledPin mode
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  pinMode(btnPin, INPUT);

  // setup bme280 sensor
  Wire.begin(sdaPin, sclPin);
  bme.begin(0x76, &Wire);

  // set display
  display.init();
  display.setFont(ArialMT_Plain_10);
  display.flipScreenVertically();

  // sensors update timer every 10s
  const int sensorsUpdateInterval = 10000;

  timer.every(sensorsUpdateInterval, updateSensors);

  // wifi connection
  connectWiFiAP();

  // firebase connection
  connectFirebase();

  // firebase udpdate interval 1h
  const int firebaseUpdateInterval = 360000;

  timer.every(firebaseUpdateInterval, udpateFirebaseData);

  // retrive time
  timeClient.begin();
}

void loop()
{
  timer.tick();
  timeClient.update();

  bool isNextFrame = isBtnPressed();

  if (isNextFrame)
  {
    updateFrameNum();
  }
}

void updateFrameNum()
{
  if (frameNum < frameSize - 1)
  {
    frameNum++;
  }
  else
  {
    frameNum = 0;
  }

  log("Update frame -> " + String(frameNum) + " from: " + String(frameSize));

  redraw(true);
}

bool isBtnPressed()
{
  int debounce = 20;
  bool isPressed = false;
  int value = digitalRead(btnPin);

  if (value == HIGH && btnState == LOW && (millis() - btnPressTime > debounce))
  {
    isPressed = true;
    log("Button pressed");
    btnPressTime = millis();
  }

  btnState = value;

  return isPressed;
}

void redraw(bool resetLastUpdateTime)
{
  if (resetLastUpdateTime)
  {
    displayLastUpdate = millis();
  }

  if (millis() - displayLastUpdate < displayIdleTime)
  {
    display.displayOn();
    display.clear();
    frames[frameNum]();
    display.display();
  }
  else
  {
    display.clear();
    display.displayOff();
  }
}

bool updateSensors(void *)
{
  // read climate values
  t = bme.readTemperature();
  p = bme.readPressure();
  h = bme.readHumidity();   
  // translate to moisture percentage
  m = map(analogRead(moiPin), m_air, m_water, 100, 0);
  log("Update sensors -> t: " + String(t) + " h: " + String(h) + "p: " + String(p) + " m: " + String(m));

  redraw(false);

  return true;
}

void connectWiFiAP()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  int attempts = 0;

  while (WiFi.status() != WL_CONNECTED && attempts < 10)
  {
    digitalWrite(ledPin, HIGH);
    delay(250);
    digitalWrite(ledPin, LOW);
    delay(250);
    
    attempts++;
  }

  if (WiFi.status() != WL_CONNECTED)
  {
    log("Could not connect to: ");
    log(ssid);
    return;
  }

  log("IP address: ");
  log(WiFi.localIP().toString());
}

void connectFirebase()
{
  Firebase.begin(firbaseHost, firbaseAuth);
  Firebase.reconnectWiFi(true);
  if (!Firebase.beginStream(firebaseData, planterPath))
  {
    log("Error Firebase: " + firebaseData.errorReason());
  }
}

bool udpateFirebaseData(void *)
{
  if (WiFi.status() == WL_CONNECTED)
  {

    firebaseJSON.clear();
    firebaseJSON.add("temperature", t);
    firebaseJSON.add("humidity", h);
    firebaseJSON.add("pressure", p);
    firebaseJSON.add("moisture", m);
    // convert to string, unsigned long not supported
    firebaseJSON.add("epoch", (String)timeClient.getEpochTime());

    if (!Firebase.pushJSON(firebaseData, planterPath, firebaseJSON))
    {
      log("Error Firebase: " + firebaseData.errorReason());
    }
  }

  return true;
}

bool blink(void *)
{
  digitalWrite(ledPin, !digitalRead(ledPin));
  return true;
}

void log(String str) {
  if (printSerail)
  {
    Serial.println(str);
  }
}