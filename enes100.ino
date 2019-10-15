#include "Enes100.h"
#include "Tank.h"

void setup() {
  Enes100.begin("Aqua Terps", WATER, 3, 8, 9);
  Tank.begin();
  Tank.setLeftMotorPWM(255);
  Tank.setRightMotorPWM(255);
}

void loop() {
  Enes100.updateLocation();
  Enes100.println(Enes100.location.theta);
  Enes100.println(Enes100.location.y);
  Enes100.println(Enes100.location.x);
  if(Enes100.location.theta > 0.05 && Enes100.location.theta <= 3.14){
    Tank.setLeftMotorPWM(255);
    Tank.setRightMotorPWM(-255);
  }
  else if(Enes100.location.theta >= -3.14 && Enes100.location.theta < -0.05){
    Tank.setLeftMotorPWM(-255);
    Tank.setRightMotorPWM(255);
  }
  else{
    Tank.setLeftMotorPWM(255);
    Tank.setRightMotorPWM(255);
  }
/*  if(Tank.readDistanceSensor(0) <= 0.3 || Tank.readDistanceSensor(2) <= 0.3){
    Tank.turnOffMotors();
    if((Tank.readDistanceSensor(0) < Tank.readDistanceSensor(2)) && (Enes100.location.y <= 1.5 && Enes100.location.y >= 0.2)){
      Tank.setLeftMotorPWM(255);
      Tank.setRightMotorPWM(-255);
    }
  } */
  if(Enes100.location.x  >= 3.2 && Enes100.location.x <= 3.6){
    if(Tank.readDistanceSensor(0) <= 0.15 || Tank.readDistanceSensor(2) <= 0.15){
      Tank.turnOffMotors();
    }
    else if(Tank.readDistanceSensor(0) < Tank.readDistanceSensor(2)){
      Tank.setLeftMotorPWM(255);
      Tank.setRightMotorPWM(-255);
    }
  }
}
