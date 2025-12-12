const int buzzerPin = 4;   // buzzer
const int buttonPin = 14;   // push button

bool buzzerOn = false;     // track buzzer state
bool lastButtonState = HIGH;

void setup() {
  pinMode(buzzerPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP); // use internal pull-up resistor
}

void loop() {
  bool buttonState = digitalRead(buttonPin);

  // Detect button press (edge detection)
  if (buttonState == LOW && lastButtonState == HIGH) {
    // Toggle buzzer state
    buzzerOn = !buzzerOn;

    if (buzzerOn) {
      // Doorbell sound: “ding-dong”
      digitalWrite(buzzerPin, HIGH);
      delay(400);
      digitalWrite(buzzerPin, LOW);
      delay(200);
      digitalWrite(buzzerPin, HIGH);
      delay(400);
      digitalWrite(buzzerPin, LOW);
    }
  }

  lastButtonState = buttonState; // save for next loop
}