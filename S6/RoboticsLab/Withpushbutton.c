const int ledPin = 8;
const int buttonPin = 7;
void setup()
{
  Serial.begin(9600);
  pinMode(buttonPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop()
{
  int digitalVal = digitalRead(buttonPin);
  Serial.println(digitalVal);
  if (digitalVal == HIGH)
  {
  	digitalWrite(ledPin,HIGH);
  }
  else
  {
  digitalWrite(ledPin, LOW);
  }  
}
