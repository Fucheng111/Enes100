#include "Enes100.h"
#include "Tank.h"
#include <math.h>

double x;
double y;
double theta;
double destination_x;
double destination_y;
bool right_x;
bool faceTarget;
	
void setup() {
	Enes100.begin("Aqua Terps", WATER, 3, 8, 9);
	Tank.begin();
	Tank.setLeftMotorPWM(255);
	Tank.setRightMotorPWM(-255);
	if(Enes100.updateLocation()){
	  theta = Enes100.location.theta;
	  x = Enes100.location.x;
	  y = Enes100.location.y;
 	 }
	destination_x= Enes100.destination.x; 
	destination_y= Enes100.destination.y; 
	right_x = false;
	faceTarget = false;
}

void loop() {
	right_x = facingRight();
	if(facingTarget()){
		Tank.setLeftMotorPWM(0);
		Tank.setRightMotorPWM(0);
	}
	while(fabs(destination_x - x) >0){
		Tank.setLeftMotorPWM(255);
		Tank.setRightMotorPWM(255);
	}
}

void location(){
	if(Enes100.updateLocation()){
	  theta = Enes100.location.theta;
	  x = Enes100.location.x;
	  y = Enes100.location.y;
  	}
}

bool facingRight(){
	location();
	
	bool right = false;
	
	if(Enes100.location.theta > 0.05 && Enes100.location.theta <= 3.14){
		Tank.setLeftMotorPWM(255);
		Tank.setRightMotorPWM(-255);
		
  	}
  	else if(Enes100.location.theta >= -3.14 && Enes100.location.theta <= -0.05){
		Tank.setLeftMotorPWM(-255);
		Tank.setRightMotorPWM(255);
  	}
  	else{
		Tank.setLeftMotorPWM(0);
		Tank.setRightMotorPWM(0);
		right = true;
  	}
	
	return right;
}

bool facingTarget(){
	
	double x_diff = destination_x- x;
	double y_diff = destination_y- y;
	
	double  beta = atan2 (y_diff, x_diff);
	bool faceTarget = false;
	
	Enes100.print("theta");
	Enes100.println(theta);
	Enes100.println(beta);

	
	if(beta >=0){
		
		while(fabs(theta - beta) >= 0.05){
			location();
			Tank.setLeftMotorPWM(-255);
			Tank.setRightMotorPWM(255);
		}
		faceTarget = true;
		
	}else{
		beta = fabs(beta);
		while(fabs(theta - beta) >= 0.05){
			location();
			
			Tank.setLeftMotorPWM(255);
			Tank.setRightMotorPWM(-255);
		}
		faceTarget = true;
		
	}
	return faceTarget;
	
		
}
