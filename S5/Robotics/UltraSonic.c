const int trigPin = 9;
const int echoPin = 10;

long duration;
float distance;

void setup()
{
	pinMode(trigPin,OUTPUT);
  	pinMode(echoPin,INPUT);
	Serial.begin(9600);
}

void loop()
{
	digitalWrite(trigPin,HIGH);
    delay(2);
    digitalWrite(trigPin,HIGH);
    delay(10);
    digitalWrite(trigPin,LOW);
  
    duration=pulseIn(echoPin,HIGH);
    distance = distance*0.034/2;
    
    Serial.print("Distance = ");
    Serial.print(distance);
    Serial.println("cm");
  
    delay(500);
      
}
