int trigPin1 = 2, trigPin2 = 11;
int echoPin1 = 4, echoPin2 = 10;
float duration1, distance1, duration2, distance2;

void setup() {
 pinMode(trigPin1, OUTPUT);
 pinMode(echoPin1, INPUT);
 pinMode(trigPin2, OUTPUT);
 pinMode(echoPin2, INPUT);
}

void loop() {
  digitalWrite(trigPin1, LOW);
  digitalWrite(trigPin2, LOW);
  delay(2);
  digitalWrite(trigPin1, HIGH);
  digitalWrite(trigPin2, HIGH);
  delay(10);
  digitalWrite(trigPin1,LOW);
  digitalWrite(trigPin2,LOW);

  duration1 = pulseIn(echoPin1, HIGH);
  distance1 = (duration1 * .0343)/2;
  duration2 = pulseIn(echoPin2, HIGH);
  distance2 = (duration2 * .0343)/2;
  
  delay(100);
}
