#include <ESP32Servo.h>

const int PIR_SENSOR_OUTPUT_PIN = 19;  /* PIR sensor O/P pin */
int warm_up;

Servo myServo;
int servoPin = 18;

void setup() {
  pinMode(PIR_SENSOR_OUTPUT_PIN, INPUT);
  Serial.begin(9600); /* Define baud rate for serial communication */

  myServo.attach(servoPin);
  myServo.write(0); /* starting position*/

  Serial.println("Waiting For Power On Warm Up");
  delay(20000); /* Power On Warm Up Delay */
  Serial.println("Ready!");
}

void loop() {
  int sensor_output;
  sensor_output = digitalRead(PIR_SENSOR_OUTPUT_PIN);
 
  if( sensor_output == LOW ) {
    if( warm_up == 1 ) {
      Serial.print("Warming Up\n\n");
      warm_up = 0;
      delay(2000);
    }
    Serial.print("No object in sight\n\n");
    myServo.write(0); /* move servo back */
    delay(1000);
  }
  else
  {
    Serial.print("Object detected\n\n");   
    warm_up = 1;
    myServo.write(90); /* move servo when triggered */
    delay(1000);
  } 
}
