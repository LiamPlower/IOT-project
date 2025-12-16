#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <DHT.h>
#include <ESP32Servo.h>
#include "homepage.h"

const char* ssid = "LiamsiPhone";
const char* password = "12345678";

WebServer server(80);

const int buzzerPin = 4;
const int buttonPin = 14;
const int PIR_SENSOR_OUTPUT_PIN = 19;
const int servoPin = 18;

#define DHTPIN 27
#define DHTTYPE DHT11

// ===== Objects =====
DHT dht(DHTPIN, DHTTYPE);
Servo myServo;

// ===== State Variables =====
bool buzzerOn = false;
bool lastButtonState = HIGH;
int pirState = 0;
int lastPIRState = LOW;

// Root page handler (HTML dashboard)
void handleRoot() {
  server.send(200, "text/html", homePage);
}

// JSON data endpoint for JavaScript fetch()
void handleData() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  String json = "{";
  json += "\"temp\":";
  json += isnan(temperature) ? "\"--\"" : String(temperature, 2);
  json += ",";
  json += "\"hum\":";
  json += isnan(humidity) ? "\"--\"" : String(humidity, 2);
  json += ",";
  json += "\"pir\":";
  json += pirState;
  json += "}";

  server.send(200, "application/json", json);
}

// =======================================================
// Setup
// =======================================================
void setup() {
  Serial.begin(115200);

  pinMode(buzzerPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(PIR_SENSOR_OUTPUT_PIN, INPUT);

  dht.begin();
  myServo.attach(servoPin);
  myServo.write(0);

  // ----- Wi-Fi -----
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // ----- mDNS -----
  if (MDNS.begin("esp32")) {
    Serial.println("mDNS responder started (http://esp32.local)");
  }

  // ----- Web Routes -----
  server.on("/", handleRoot);
  server.on("/data", handleData);

  server.begin();
  Serial.println("HTTP server started");
}

// Loop
void loop() {
  server.handleClient();

  // ===== BUTTON + BUZZER =====
  bool buttonState = digitalRead(buttonPin);
  if (buttonState == LOW && lastButtonState == HIGH) {
    buzzerOn = !buzzerOn;
    if (buzzerOn) {
      digitalWrite(buzzerPin, HIGH);
      delay(400);
      digitalWrite(buzzerPin, LOW);
      delay(200);
      digitalWrite(buzzerPin, HIGH);
      delay(400);
      digitalWrite(buzzerPin, LOW);
    }
  }
  lastButtonState = buttonState;

  // ===== PIR + SERVO =====
  int sensor_output = digitalRead(PIR_SENSOR_OUTPUT_PIN);
  if (sensor_output != lastPIRState) {
    if (sensor_output == HIGH) {
      myServo.write(90);
      pirState = 1;
    } else {
      myServo.write(0);
      pirState = 0;
    }
    lastPIRState = sensor_output;
  }

  delay(2);
}
