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
	if(sqrt(pow(destination_x-x,2)+pow(destination_y-y,2)) >= 0.1){
		if(obstacle_Detection_right()||obstacle_Detection_left()){
			avoid_obstacles();
		}
		if(faceTarget){
			Tank.setLeftMotorPWM(255);
			Tank.setRightMotorPWM(255);
		}else{
			facingTarget();
			Tank.setLeftMotorPWM(255);
			Tank.setRightMotorPWM(255);
		}
	}else{
		Tank.setLeftMotorPWM(0);
		Tank.setRightMotorPWM(0);
		
	}

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
	while(theta > 1.52 && theta < 1.62 ){
		location();
		if(theta >= -1.57 && theta < 1.57){
			Tank.setLeftMotorPWM(-255);
			Tank.setRightMotorPWM(255);
		
		}else if(theta >= 1.57 && theta <= 3.14 && theta >=3.14 && theta < -1.57){
			Tank.setLeftMotorPWM(255);
			Tank.setRightMotorPWM(-255);
		}
	}
	
	Tank.setLeftMotorPWM(0);
	Tank.setRightMotorPWM(0);
}

void facingDown(){
	while(theta <-1.52 && theta > -1.62 ){
		location();
		if(theta >= -1.57 && theta < 1.57){
			Tank.setLeftMotorPWM(255);
			Tank.setRightMotorPWM(-255);
		
		}else if(theta >= 1.57 && theta <= 3.14 && theta >=3.14 && theta < -1.57){
			Tank.setLeftMotorPWM(-255);
			Tank.setRightMotorPWM(255);
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

bool obstacle_Detection_right(){
	if(Tank.readDistanceSensor(2) <0.1){
		return true;
	}
	
	return false;
}

bool obstacle_Detection_left(){
	if(Tank.readDistanceSensor(0) <0.1){
		return true;
	}
	
	return false;
}

void avoid_obstacles(){
	if(obstacle_Detection_left()){
		Tank.setLeftMotorPWM(0);
		Tank.setRightMotorPWM(0);
		location();
		
		faceTarget = false;
		if((2- y) <=0.3){
			facingDown();
			if(obstacle_Detection_left() || obstacle_Detection_right()){
				facingLeft();
				double width = x - 0.25;
				while(x > width){
					Tank.setLeftMotorPWM(255);
					Tank.setRightMotorPWM(255);
					location();
				}
				Tank.setLeftMotorPWM(0);
				Tank.setRightMotorPWM(0);
				facingDown();
				double length = y - 0.55;
				while(y > length){
					Tank.setLeftMotorPWM(255);
					Tank.setRightMotorPWM(255);
					location();
				}
				Tank.setLeftMotorPWM(0);
				Tank.setRightMotorPWM(0);
				facingRight();
			 	width = x + 0.25;
				while(x < width){
					Tank.setLeftMotorPWM(255);
					Tank.setRightMotorPWM(255);
					location();
				}
				Tank.setLeftMotorPWM(0);
				Tank.setRightMotorPWM(0);
			}else{
				double length = y - 0.55;
				while(y > length){
					Tank.setLeftMotorPWM(255);
					Tank.setRightMotorPWM(255);
					location();
				}
				Tank.setLeftMotorPWM(0);
				Tank.setRightMotorPWM(0);
				facingRight();
			 	double width = x + 0.25;
				while(x < width){
					Tank.setLeftMotorPWM(255);
					Tank.setRightMotorPWM(255);
					location();
				}
				Tank.setLeftMotorPWM(0);
				Tank.setRightMotorPWM(0);
			}
		}else if(y <= 0.3){
			facingUp();
			if(obstacle_Detection_left() || obstacle_Detection_right()){
				facingLeft();
				double width = x - 0.25;
				while(x > width){
					Tank.setLeftMotorPWM(255);
					Tank.setRightMotorPWM(255);
					location();
				}
				Tank.setLeftMotorPWM(0);
				Tank.setRightMotorPWM(0);
				facingUp();
				double length = y - 0.55;
				while(y > length){
					Tank.setLeftMotorPWM(255);
					Tank.setRightMotorPWM(255);
					location();
				}
				Tank.setLeftMotorPWM(0);
				Tank.setRightMotorPWM(0);
				facingRight();
			 	width = x + 0.25;
				while(x < width){
					Tank.setLeftMotorPWM(255);
					Tank.setRightMotorPWM(255);
					location();
				}
				Tank.setLeftMotorPWM(0);
				Tank.setRightMotorPWM(0);
			}else{
				double length = y - 0.55;
				while(y > length){
					Tank.setLeftMotorPWM(255);
					Tank.setRightMotorPWM(255);
					location();
				}
				Tank.setLeftMotorPWM(0);
				Tank.setRightMotorPWM(0);
				facingRight();
			 	double width = x + 0.25;
				while(x < width){
					Tank.setLeftMotorPWM(255);
					Tank.setRightMotorPWM(255);
					location();
				}
				Tank.setLeftMotorPWM(0);
				Tank.setRightMotorPWM(0);
			}
			
		}else{
			facingDown();
			double length = y - 0.25;
			while(y > length){
				Tank.setLeftMotorPWM(255);
				Tank.setRightMotorPWM(255);
				location();
			}
			Tank.setLeftMotorPWM(0);
			Tank.setRightMotorPWM(0);
			facingRight();
			double width = x + 0.25;
			while(x < width){
				Tank.setLeftMotorPWM(255);
				Tank.setRightMotorPWM(255);
				location();
			}
			Tank.setLeftMotorPWM(0);
			Tank.setRightMotorPWM(0);
		}
	}else if(obstacle_Detection_right()){
		Tank.setLeftMotorPWM(0);
		Tank.setRightMotorPWM(0);
		location();
		
		faceTarget = false;
		if((2- y) <=0.3){
			facingDown();
			if(obstacle_Detection_left() || obstacle_Detection_right()){
				facingLeft();
				double width = x - 0.25;
				while(x > width){
					Tank.setLeftMotorPWM(255);
					Tank.setRightMotorPWM(255);
					location();
				}
				Tank.setLeftMotorPWM(0);
				Tank.setRightMotorPWM(0);
				facingDown();
				double length = y - 0.55;
				while(y > length){
					Tank.setLeftMotorPWM(255);
					Tank.setRightMotorPWM(255);
					location();
				}
				Tank.setLeftMotorPWM(0);
				Tank.setRightMotorPWM(0);
				facingRight();
			 	width = x + 0.25;
				while(x < width){
					Tank.setLeftMotorPWM(255);
					Tank.setRightMotorPWM(255);
					location();
				}
				Tank.setLeftMotorPWM(0);
				Tank.setRightMotorPWM(0);
			}else{
				double length = y - 0.55;
				while(y > length){
					Tank.setLeftMotorPWM(255);
					Tank.setRightMotorPWM(255);
					location();
				}
				Tank.setLeftMotorPWM(0);
				Tank.setRightMotorPWM(0);
				facingRight();
			 	double width = x + 0.25;
				while(x < width){
					Tank.setLeftMotorPWM(255);
					Tank.setRightMotorPWM(255);
					location();
				}
				Tank.setLeftMotorPWM(0);
				Tank.setRightMotorPWM(0);
			}
		}else if(y <= 0.3){
			facingUp();
			if(obstacle_Detection_left() || obstacle_Detection_right()){
				facingLeft();
				double width = x - 0.25;
				while(x > width){
					Tank.setLeftMotorPWM(255);
					Tank.setRightMotorPWM(255);
					location();
				}
				Tank.setLeftMotorPWM(0);
				Tank.setRightMotorPWM(0);
				facingUp();
				double length = y + 0.55;
				while(y < length){
					Tank.setLeftMotorPWM(255);
					Tank.setRightMotorPWM(255);
					location();
				}
				Tank.setLeftMotorPWM(0);
				Tank.setRightMotorPWM(0);
				facingRight();
			    width = x + 0.25;
				while(x < width){
					Tank.setLeftMotorPWM(255);
					Tank.setRightMotorPWM(255);
					location();
				}
				Tank.setLeftMotorPWM(0);
				Tank.setRightMotorPWM(0);
			}else{
				double length = y - 0.55;
				while(y > length){
					Tank.setLeftMotorPWM(255);
					Tank.setRightMotorPWM(255);
					location();
				}
				Tank.setLeftMotorPWM(0);
				Tank.setRightMotorPWM(0);
				facingRight();
			 	double width = x + 0.25;
				while(x < width){
					Tank.setLeftMotorPWM(255);
					Tank.setRightMotorPWM(255);
					location();
				}
				Tank.setLeftMotorPWM(0);
				Tank.setRightMotorPWM(0);
			}
			
		}else{
			facingUp();
			double length = y + 0.25;
			while(y < length){
				Tank.setLeftMotorPWM(255);
				Tank.setRightMotorPWM(255);
				location();
			}
			Tank.setLeftMotorPWM(0);
			Tank.setRightMotorPWM(0);
			facingRight();
			double width = x + 0.25;
			while(x < width){
				Tank.setLeftMotorPWM(255);
				Tank.setRightMotorPWM(255);
				location();
			}
			Tank.setLeftMotorPWM(0);
			Tank.setRightMotorPWM(0);
		}
	}
}

