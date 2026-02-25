String inputString = "";

void setup() {
  Serial.begin(9600);
}

void loop() {
    inputString = Serial.readString();
  if(inputString.length() > 0){
    String reversed = "";
    for (int i = inputString.length() - 1; i >= 0; i--) {
      reversed += inputString[i];
    }

    Serial.print("Reversed String: ");
    Serial.println(reversed);
  }
  }
