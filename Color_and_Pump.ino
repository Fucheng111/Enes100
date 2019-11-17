#include <Servo.h>
Servo myservo;

int pos = 0;
int pump = A1;
int sal =A2;
int S0 = 4;
int S1 = 5;
int S2 = 6;
int S3 = 7;
int sensorOut = 8;
int frequency;

void setup() {
  pinMode(pump, OUTPUT);
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  myservo.attach(9);
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
  Serial.begin(9600);
}
void loop() {
  analogWrite(pump, 0);
   for (pos = 180; pos >= 90; pos -= 1) {
    myservo.write(pos);
    delay(30);
  }
 
  analogWrite(pump, 255);
  delay(7000);
  analogWrite(pump, 0);



  if(analogRead(sal) >1){
    Serial.println("Water is salty");
    Serial.println(analogRead(sal));
  }else{
    Serial.println("Water is not salty");
    Serial.println(analogRead(sal));
  }


  for (pos = 90; pos <= 180; pos += 1) {
    myservo.write(pos);
    delay(30);
  }
  
  for (pos = 90; pos >= 0; pos -= 1) {
    myservo.write(pos);
    delay(30);
  }

  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);

  
  long time = millis();
  while(millis()-time < 5000){
    frequency = pulseIn(sensorOut, LOW);
  }
  if(frequency > 75){
    Serial.println("Water is green");
  }
  else{
    Serial.println("Water is clear");
  }

  
  while(1);
}
