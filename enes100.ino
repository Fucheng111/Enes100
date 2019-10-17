#include "Enes100.h"
#include "Tank.h"
#include <math.h>

double x;
double y;
double theta;
double lin_velocity;
double destination_x;
double destination_y;
bool faceTarget;
	
void setup() {
	Enes100.begin("Aqua Terps", WATER, 3, 8, 9);
	Tank.begin();
	if(Enes100.updateLocation()){
	  theta = Enes100.location.theta;
	  x = Enes100.location.x;
	  y = Enes100.location.y;
 	 }
	destination_x= Enes100.destination.x; 
	destination_y= Enes100.destination.y; 

	faceTarget = false;
}

void loop() {
	facingLeft();
}

void location(){
	if(Enes100.updateLocation()){
	  theta = Enes100.location.theta;
	  x = Enes100.location.x;
	  y = Enes100.location.y;
  	}
}

void facingRight(){
	while (fabs(theta) < 0.05){
		location();
		if(theta > 0.05 && theta <= 3.14){
			Tank.setLeftMotorPWM(255);
			Tank.setRightMotorPWM(-255);

		}
		else if(theta >= -3.14 && theta <= -0.05){
			Tank.setLeftMotorPWM(-255);
			Tank.setRightMotorPWM(255);
		}
	}
	Tank.setLeftMotorPWM(0);
	Tank.setRightMotorPWM(0);
	
}

void facingLeft(){
	while(fabs(theta)>3){
		location();
		if(theta > 0.05 && theta <= 3.14){
			Tank.setLeftMotorPWM(-255);
			Tank.setRightMotorPWM(255);
		
		}else if(theta >= -3.14 && theta <= -0.05){
			Tank.setLeftMotorPWM(255);
			Tank.setRightMotorPWM(-255);
		}
	}
	
	Tank.setLeftMotorPWM(0);
	Tank.setRightMotorPWM(0);
}

void facingUp(){
	while(theta > 1.52 && theta < 1.66 ){
		location();
		if(theta > 0.05 && theta <= 3.14){
			Tank.setLeftMotorPWM(-255);
			Tank.setRightMotorPWM(255);
		
		}else if(theta >= -3.14 && theta <= -0.05){
			Tank.setLeftMotorPWM(255);
			Tank.setRightMotorPWM(-255);
		}
	}
	
	Tank.setLeftMotorPWM(0);
	Tank.setRightMotorPWM(0);
}

bool facingTarget(){
	
	double x_diff = destination_x- x;
	double y_diff = destination_y- y;
	
	double  beta = atan2 (y_diff, x_diff);
	bool faceTarget = false;
	
	if(beta >=0){
		
		while(fabs(theta - beta) >= 0.05){
			Tank.setLeftMotorPWM(-255);
			Tank.setRightMotorPWM(255);
			location();
		}
		faceTarget = true;
		
	}else{
		while(fabs(theta - beta) >= 0.05){
			Tank.setLeftMotorPWM(255);
			Tank.setRightMotorPWM(-255);
			location();
		}
		faceTarget = true;
		
	}
	return faceTarget;
}

void avoid_obstacles(){
	if(Tank.readDistanceSensor(0) < 0.1){
		if((2- Enes100.location.y) <=0.3){
			
		}else if(Enes100.location.y <= 0.3){
			
		}else{
			
		}
	}else if(Tank.readDistanceSensor(0) < 0.1){
		
	}
}

