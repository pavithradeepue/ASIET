//code

void setup()
{
  pinMode(13, OUTPUT);
  pinMode(2, INPUT);
}

void loop()
{
  int switchState = digitalRead(2);
  if (switchState == HIGH)
  {
  	digitalWrite(13,HIGH);
  }
  else
  {
  	digitalWrite(13,LOW);
  }
}
