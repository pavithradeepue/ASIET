#include <Servo.h>

const int touchPin = 8;   // Touch sensor pin
const int ledPin = 13;    // LED pin
int servoPin = 9;         // Servo pin

Servo servo;
int angle = 0;

void setup() {
  pinMode(touchPin, INPUT);
  pinMode(ledPin, OUTPUT);
  
  servo.attach(servoPin);
  
  Serial.begin(9600);
}

void loop() {

  int touchState = digitalRead(touchPin);

  if (touchState == HIGH) {
    
    digitalWrite(ledPin, HIGH);
    Serial.println("Touch Detected");

    // Servo rotate 0 → 180
    for(angle = 0; angle < 90; angle++) {
      servo.write(angle);
      delay(15);
    }

    // Servo rotate 180 → 0
    for(angle = 90; angle > 0; angle--) {
      servo.write(angle);
      delay(15);
    }

  } 
  else {

    digitalWrite(ledPin, LOW);
    Serial.println("No Touch");

  }

  delay(200);
}
