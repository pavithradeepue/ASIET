const int ledPin = 12;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    int number = Serial.parseInt();

    if (number % 2 == 0) {
      Serial.println("Even Number");
      blinkLED(2);
    } 
    else {
      Serial.println("Odd Number");
      blinkLED(3);
    }
  }
}

void blinkLED(int times) {
  for (int i = 0; i < times; i++) {
    digitalWrite(ledPin, HIGH);
    delay(300);
    digitalWrite(ledPin, LOW);
    delay(300);
  }
}
