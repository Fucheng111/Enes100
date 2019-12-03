#include <Enes100.h>
#include <Servo.h>

Servo myservo;

int pos = 0;
int depth = A0;
int pump = A1;
int sal = A2;
int S0 = 4;
int S1 = 5;
int S2 = 6;
int S3 = 7;
int color = 8;
int frequency;
int water;
int waterdepth;
float duration, distance;
double x,y,destination_x,destination_y;;

void setup() {
  pinMode(pump, OUTPUT);
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(color, INPUT);
  pinMode(depth, INPUT);
  myservo.attach(9);
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
  Serial.begin(9600);
  Enes100.begin("Aqua Terps", WATER, 5, 2, 3);
}
void loop() {

    while(!Enes100.updateLocation()){
    Enes100.println("Fail to update location");
  }

  destination_x= Enes100.destination.x; 
  destination_y= Enes100.destination.y;
   
  Enes100.print("Target at: ");
  Enes100.print(destination_x);
  Enes100.print(",");
  Enes100.println(destination_y);

  Enes100.println("Update Location");

  x = Enes100.location.x;
  y = Enes100.location.y;

  if(sqrt(pow(destination_x-x,2)+pow(destination_y-y,2)) <= 0.15){
  analogWrite(pump, 0);
   for (pos = 180; pos >= 90; pos -= 1) {
    myservo.write(pos);
    delay(30);
  }

  long time = millis();
  while(millis()-time < 5000){
    water = 0.0507 *analogRead(depth)-12.1;
  }
  Enes100.mission(water);
 
  analogWrite(pump, 255);
  delay(7000);
  analogWrite(pump, 0);

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
  
  time = millis();
  while(millis()-time < 5000){
    frequency = pulseIn(color, LOW);
  }
  
  if(frequency > 75){
    if(analogRead(sal) > 3){
      Enes100.mission(SALT_POLLUTED);
    }
    else{
      Enes100.mission(FRESH_POLLUTED);
    }
  }
  else{
    if(analogRead(sal) > 3){
      Enes100.mission(SALT_UNPOLLUTED);
    }
    else{
      Enes100.mission(FRESH_UNPOLLUTED);
    }
  }
  
  while(1){};
  }
}
