const int ledPin = 8;
String password = "1234";

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  Serial.println("Enter Password:");
}

void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readString();
    input.trim();

    if (input == password) {
      Serial.println("Access Granted");
      blinkLED();
    } 
    else {
      Serial.println("Access Denied");
    }
  }
}

void blinkLED() {
  for (int i = 0; i < 5; i++) {
    digitalWrite(ledPin, HIGH);
    delay(200);
    digitalWrite(ledPin, LOW);
    delay(200);
  }
}
