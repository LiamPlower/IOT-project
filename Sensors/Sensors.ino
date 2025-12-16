#include "DHT.h"
#include <ESP32Servo.h>

// ===== Pins =====
const int buzzerPin = 4;
const int buttonPin = 14;

#define DHTPIN 27
#define DHTTYPE DHT11

const int PIR_SENSOR_OUTPUT_PIN = 19;
const int servoPin = 18;

// ===== Objects =====
DHT dht(DHTPIN, DHTTYPE);
Servo myServo;

// ===== States =====
bool buzzerOn = false;
bool lastButtonState = HIGH;
int lastPIRState = LOW;
int pirState = 0; // 0 = no motion, 1 = motion

// ===== Setup =====
void setup() {
  Serial.begin(115200);

  pinMode(buzzerPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(PIR_SENSOR_OUTPUT_PIN, INPUT);

  dht.begin();
  myServo.attach(servoPin);
  myServo.write(0);

  Serial.println("System Ready");
}

// ===== Loop =====
void loop() {

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
      Serial.println("Motion Detected");
    } else {
      myServo.write(0);
      pirState = 0;
      Serial.println("No Motion");
    }
    lastPIRState = sensor_output;
  }

  // ===== DHT SENSOR =====
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (!isnan(temperature) && !isnan(humidity)) {
    Serial.print("Temp: ");
    Serial.print(temperature);
    Serial.print(" °C  |  Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");
  } else {
    Serial.println("Failed to read DHT sensor");
  }

  delay(1000);
}
  