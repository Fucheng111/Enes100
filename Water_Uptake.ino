#include "Enes100.h"
#include <Servo.h>
Servo myservo;


double x;
double y;
double destination_x;
double destination_y;
bool salty;
bool polluted;

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
  // put your setup code here, to run once:
  //Params: team name, team mission, marker #, TX Pin, RX Pin
  Enes100.begin("Aqua Terps", WATER, 7,10, 11);
  Enes100.println("Start");

//  destination_x= Enes100.destination.x; 
//  destination_y= Enes100.destination.y; 
//
//  while(!Enes100.updateLocation()){
//    Enes100.println("Fail to update location");
//  }
//
//  Enes100.println("Update Location");
//
//  x = Enes100.location.x;
//  y = Enes100.location.y;

  salty = false;
  polluted = false;

  pinMode(pump, OUTPUT);
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  myservo.attach(9);
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

}

void loop() {

//  while(!Enes100.updateLocation()){
//    Enes100.println("Fail to update location");
//  }
//
//  Enes100.println("Update Location");
//
//  x = Enes100.location.x;
//  y = Enes100.location.y;

  // Change 0.15 to the correct threshold to find out the correct distance to stop
//  if(sqrt(pow(destination_x-x,2)+pow(destination_y-y,2)) <= 0.15){
    //load the water code here


   analogWrite(pump, 0);
   for (pos = 180; pos >= 90; pos -= 1) {
    myservo.write(pos);
    delay(30);
    }
 
    analogWrite(pump, 255);
    delay(7000);
    analogWrite(pump, 0);



  if(analogRead(sal) >1){
    salty = true;
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
    polluted = true;
  }
  
    //Remember to print to serial monitor to test the code
    if(!salty & !polluted){
      Enes100.mission(FRESH_UNPOLLUTED);
    }else if (!salty & polluted){
      Enes100.mission(FRESH_POLLUTED);
    }else if(salty &!polluted){
      Enes100.mission(SALT_UNPOLLUTED);
    }else{
       Enes100.mission(SALT_POLLUTED);
    }

    while(1);
  

}
