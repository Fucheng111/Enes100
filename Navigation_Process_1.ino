#include "Enes100.h"
#include <math.h>

double x;
double y;
double theta;

int m1 = 4;
int e1 = 5;
int m2 = 7;
int e2 = 6;

void setup() {
  // put your setup code here, to run once:
    pinMode(m1, OUTPUT);
    pinMode(e1, OUTPUT);
    pinMode(m2, OUTPUT);
    pinMode(e2, OUTPUT);
   Enes100.begin("Aqua Terps", WATER, 15,10, 11);
   Enes100.println("Start");
   
//   while(!location()){
//  
//    }
//  

}

void loop() {
  // put your main code here, to run repeatedly:

  setLeftMotor(HIGH,255);
  setRightMotor(LOW,255);
  
//  facingRight();
//
//  setLeftMotor(HIGH,200);
//  setRightMotor(HIGH,200);
//  
//  while(x < 1.5){
//    Enes100.println("Driving Forward");
//    while(!location()){
//      Enes100.println("Unable to update location");
//      setLeftMotor(HIGH, 0);
//      setRightMotor(HIGH, 0);
//    }
//  }
//
//  setLeftMotor(HIGH, 0);
//  setRightMotor(HIGH, 0);
//
//  while(1){
//    
//  }
//  

}


bool location(){
  if(Enes100.updateLocation()){
      theta = Enes100.location.theta;
     Enes100.print("Theta, x, y: ");
      Enes100.print(theta);
      Enes100.print(",");
      x = Enes100.location.x;
     Enes100.print(x);
     Enes100.print(",");
      y = Enes100.location.y;
     Enes100.println(y);
     return true;
    }
   return false;
}

bool facingRight(){
  long time = millis();
  location();
  while (fabs(theta) > 0.05){
    
    if(theta > 0.05 && theta <= 3.14){
      setLeftMotor(HIGH,180);
      setRightMotor(LOW, 180);
      

    }
    else if (theta < -0.05 && theta >= -3.14){
      setLeftMotor(LOW,180);
      setRightMotor(HIGH, 180);
      
    }else{
      setLeftMotor(LOW,180);
      setRightMotor(HIGH, 180);
      
     
    }
   
   while(!location()){
    Enes100.println("Unable to update location");
    setLeftMotor(HIGH, 0);
    setRightMotor(HIGH, 0);
   }

  }
  setLeftMotor(HIGH, 0);
  setRightMotor(HIGH, 0);
  Enes100.println("Facing Right");
  
  return true;
  
}

void setLeftMotor(char dir, int speed){
  digitalWrite(m1, dir);
  analogWrite(e1, speed);
}

void setRightMotor(char dir, int speed){
  digitalWrite(m2, dir);
  analogWrite(e2, speed);
}
