int pingPin = 3;
int echoPin = 2;
int PIRPin = 4;
long duration = 0;

long Ping(){
  digitalWrite(pingPin,LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin,HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin,LOW);
  duration = pulseIn(echoPin,HIGH);
  return duration;
}
void blinkLED(){
  for (int x=0;x < 10;x++){
    digitalWrite(13,HIGH);
    delay(250);
    digitalWrite(13,LOW);
    delay(250);
}
}
long microsecondstoinches(long microseconds){
  return microseconds / 74 / 2;
}

void setup() {
  pinMode(13,OUTPUT);
  pinMode(pingPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(PIRPin, INPUT);
  Serial.begin(9600);

}

void loop() {
  if (digitalRead(PIRPin) == HIGH){
    int distance = Ping();
    int lengths = microsecondstoinches(distance);
    Serial.println(lengths);
    Serial.println("Someone has been detected!");
    blinkLED();
    digitalWrite(13,LOW);
    delay(5000);
  }
}
