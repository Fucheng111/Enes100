#include "Enes100.h"
#include "Tank.h"
#include <math.h>

double x;
double y;
double theta;
double lin_velocity;
double destination_x;
double destination_y;
double beta;
double speed_turning;
double detection_time;

bool faceTarget;
bool faceRight;
bool faceLeft;
bool faceUp;
bool faceDown;
bool forceStop;


void setup() {
	Enes100.begin();
	Tank.begin();
	location();
	destination_x= Enes100.destination.x; 
	destination_y= Enes100.destination.y; 

	faceTarget = false;
  faceRight =false;
  faceLeft = false;
  faceUp = false;
  faceDown = false;
  forceStop = false;

  speed_turning = 40;
  detection_time = 0;

  Enes100.println("Start");
  
}

void loop() {

 
  if(facingTarget()){
       
   Enes100.println("Starts");
   
   while(!(obstacle_Detection_right()||obstacle_Detection_left())){
        
    		Tank.setLeftMotorPWM(255);
    		Tank.setRightMotorPWM(255);
        

        
        location();
        
       if(sqrt(pow(destination_x-x,2)+pow(destination_y-y,2)) <= 0.15){
          Tank.setLeftMotorPWM(0);
          Tank.setRightMotorPWM(0);
          while(1){
            
          }
       }
   }
  
   
   Tank.setLeftMotorPWM(0);
   Tank.setRightMotorPWM(0);
   location();
   avoid_obstacles();
  }else{
    Tank.setLeftMotorPWM(255);
    Tank.setRightMotorPWM(255);
    delay(1000);
    Tank.setLeftMotorPWM(0);
    Tank.setRightMotorPWM(0);
  }

  

 
   
    
 }
  


void location(){
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
  	}
}

bool facingRight(){
  long time = millis();
  location();
	while (fabs(theta) > 0.07){
		
		if(theta > 0.05 && theta <= 3.14){
			Tank.setLeftMotorPWM(255);
			Tank.setRightMotorPWM(-255);
      delay(speed_turning);

		}
		else if (theta < -0.05 && theta >= -3.14){
			Tank.setLeftMotorPWM(-255);
			Tank.setRightMotorPWM(255);
      delay(speed_turning);
		}else{
      Tank.setLeftMotorPWM(-255);
      Tank.setRightMotorPWM(255);
      delay(speed_turning);
     
		}
   
   if((millis() -time) >= 10000){
     Tank.setLeftMotorPWM(-255);
      Tank.setRightMotorPWM(-255);
      delay(500);
      Tank.setLeftMotorPWM(0);
      Tank.setRightMotorPWM(0);
      Enes100.println("Facing Right Fail");
      faceRight = false;
      return false;
   }
   
   Tank.setLeftMotorPWM(0);
   Tank.setRightMotorPWM(0);
   delay(detection_time);
   location();

	}
	Tank.setLeftMotorPWM(0);
	Tank.setRightMotorPWM(0);
  Enes100.println("Facing Right");
  
  faceRight = true;
  
  faceTarget = false;
  faceLeft = false;
  faceUp = false;
  faceDown = false;
  
  return true;
	
}

bool facingLeft(){
  long time = millis();
  location();
	while(fabs(theta)<3.1){
  
    
		if(theta > 0.05 && theta <= 3.14){
			Tank.setLeftMotorPWM(-255);
			Tank.setRightMotorPWM(255);
     delay(speed_turning);
     
		
		}else if(theta >= -3.14 && theta <= -0.05){
			Tank.setLeftMotorPWM(255);
			Tank.setRightMotorPWM(-255);
      delay(speed_turning);
      
		}
   else{
      Tank.setLeftMotorPWM(255);
      Tank.setRightMotorPWM(-255);
      delay(speed_turning);
      
   }
   if((millis() -time) >= 10000){
    Tank.setLeftMotorPWM(0);
      Tank.setRightMotorPWM(0);
      return false;
   }
   Tank.setLeftMotorPWM(0);
   Tank.setRightMotorPWM(0);
   delay(detection_time);
   location();
 
    
   
	}

	Tank.setLeftMotorPWM(0);
	Tank.setRightMotorPWM(0);
  faceLeft = true;
  Enes100.println("Facing Left");

  faceTarget = false;
  faceRight =false;
  faceUp = false;
  faceDown = false;
  return true;
}

bool facingUp(){
  
  long time = millis();
  location();
	while(theta < 1.50 || theta > 1.65 ){
		
		if(theta >= -1.57 && theta < 1.57){
			Tank.setLeftMotorPWM(-255);
			Tank.setRightMotorPWM(255);
      delay(speed_turning);
    
		
		}else if((theta >= 1.57 && theta <= 3.14 )|| (theta >=-3.14 && theta < -1.57)){
			Tank.setLeftMotorPWM(255);
			Tank.setRightMotorPWM(-255);
      delay(speed_turning);
      
		}else{
      Tank.setLeftMotorPWM(255);
      Tank.setRightMotorPWM(-255);
      delay(speed_turning);
      
		}
   if((millis() -time) >= 10000){
          Tank.setLeftMotorPWM(-255);
          Tank.setRightMotorPWM(-255);
          delay(500);
          Tank.setLeftMotorPWM(0);
          Tank.setRightMotorPWM(0);
          Enes100.println("Facing Up Fail");
           return false;
   }
   
   Tank.setLeftMotorPWM(0);
   Tank.setRightMotorPWM(0);
   delay(detection_time);
   location();
   
	}
	
	Tank.setLeftMotorPWM(0);
	Tank.setRightMotorPWM(0);

 Enes100.println("Facing Up");
  faceUp = true;
  faceTarget = false;
  faceRight =false;
  faceLeft = false;
  faceDown = false;

  return true;
}

bool facingDown(){
  long time = millis();
  location();
	while(theta > -1.50 || theta < -1.65 ){
		
   
		if(theta >= -1.57 && theta < 1.57){
			Tank.setLeftMotorPWM(255);
			Tank.setRightMotorPWM(-255);
      delay(speed_turning);
     
		
		}else if((theta >= 1.57 && theta <= 3.14) || (theta >=-3.14 && theta <= -1.57)){
			Tank.setLeftMotorPWM(-255);
			Tank.setRightMotorPWM(255);
     delay(speed_turning);
      
		}else{
      Tank.setLeftMotorPWM(255);
      Tank.setRightMotorPWM(-255);
      delay(speed_turning);
     
   }
   
   if((millis() -time) >= 10000){
    Tank.setLeftMotorPWM(-255);
    Tank.setRightMotorPWM(-255);
     delay(500);
    Tank.setLeftMotorPWM(0);
    Tank.setRightMotorPWM(0);
    Enes100.println("Facing Down Fail");
      return false;
   }
   Tank.setLeftMotorPWM(0);
   Tank.setRightMotorPWM(0);
   delay(detection_time);
   location();
 
	}
	
	Tank.setLeftMotorPWM(0);
	Tank.setRightMotorPWM(0);
  Enes100.println("Facing Down");
  faceDown = true;
  faceTarget = false;
  faceRight =false;
  faceLeft = false;
  faceUp = false;

  return true;
}


bool facingTarget(){
	
	double x_diff = destination_x- x;
	double y_diff = destination_y- y;
	

  if(!faceRight){
    facingRight();
  }
  
  beta = atan2 (y_diff, x_diff);
  location();

  long time = millis();
  
	if(beta >0){
    
    while(fabs(theta - beta) >= 0.05){
      
      Tank.setLeftMotorPWM(-255);
      Tank.setRightMotorPWM(255);

      delay(speed_turning);
     
      if((millis() - time) >= 10000){
          
        Tank.setLeftMotorPWM(0);
        Tank.setRightMotorPWM(0);
        Enes100.println("Facing Target Fail");
        faceRight =false;
        faceLeft = false;
        faceUp = false;
        faceDown = false;
        faceTarget = false;
        return false;
      }
      Tank.setLeftMotorPWM(0);
   Tank.setRightMotorPWM(0);
   delay(detection_time);
   location();
      
    }
    faceTarget = true;
    Enes100.println("Facing Target");
   
	}else if(beta <0){
    while(fabs(theta - beta) >= 0.05){
      
      Tank.setLeftMotorPWM(255);
      Tank.setRightMotorPWM(-255);
      
      delay(speed_turning);
      
      if((millis() -time) >= 10000){
        Enes100.println("Facing Target Fail");
        
      Tank.setLeftMotorPWM(0);
      Tank.setRightMotorPWM(0);
      faceRight =false;
        faceLeft = false;
        faceUp = false;
        faceDown = false;
        faceTarget = false;
      return false;
   }
   Tank.setLeftMotorPWM(0);
   Tank.setRightMotorPWM(0);
   delay(detection_time);
   location();
     
    }
    faceTarget = true;
    Enes100.println("Facing Target");
    
	}

 faceTarget = true;
 Enes100.println("Facing Target");
 Tank.setLeftMotorPWM(0);
 Tank.setRightMotorPWM(0);
 
  faceRight =false;
  faceLeft = false;
  faceUp = false;
  faceDown = false;

  return true;
}

bool obstacle_Detection_right(){
  
	if(Enes100.readDistanceSensor(2) < 0.2){
    
    Enes100.print("Sensor 2: ");
    Enes100.println(Enes100.readDistanceSensor(2));
		return true;
	}
  Enes100.print("Sensor 2: ");
    Enes100.println(Enes100.readDistanceSensor(2));
   
	
	return false;
}

bool obstacle_Detection_left(){
  
	if(Enes100.readDistanceSensor(0) < 0.2){
    Enes100.print("Sensor 0: ");
    Enes100.println(Enes100.readDistanceSensor(0));
    
		return true;
	}
	Enes100.print("Sensor 0: ");
  Enes100.println(Enes100.readDistanceSensor(0));
    
	return false;
}

void avoid_obstacles(){
  double length;
  double width;
  faceTarget = false;
	if(beta >=0){
		
		if((2- y) <=0.3){
			if(facingDown()){
  			if(obstacle_Detection_left() || obstacle_Detection_right()){
  				if(facingLeft()){
  				width = x - 0.25;
  				while(x > width){
            if(obstacle_Detection_left() || obstacle_Detection_right()){
              break;
            }
  					Tank.setLeftMotorPWM(255);
  					Tank.setRightMotorPWM(255);
  					location();
  				}
  				Tank.setLeftMotorPWM(0);
  				Tank.setRightMotorPWM(0);
  				}
  				if(facingDown()){
  				length = y - 0.55;
  				while(y > length){
            if(obstacle_Detection_left() || obstacle_Detection_right()){
              break;
            }
  					Tank.setLeftMotorPWM(255);
  					Tank.setRightMotorPWM(255);
  					location();
  				}
  				Tank.setLeftMotorPWM(0);
  				Tank.setRightMotorPWM(0);
  				}
  				facingRight();
          
          while(obstacle_Detection_left() || obstacle_Detection_right()){
          if(facingDown()){
            length = y - 0.1;
            while(y >= length){
              if(obstacle_Detection_left()){
                  facingRight();
                  Tank.setLeftMotorPWM(255);
                  Tank.setRightMotorPWM(255);
                  delay(250);
                  Tank.setLeftMotorPWM(0);
                  Tank.setRightMotorPWM(0);
                  break;
                }
                Tank.setLeftMotorPWM(255);
                Tank.setRightMotorPWM(255);
                location();
              }
            }
             Tank.setLeftMotorPWM(0);
             Tank.setRightMotorPWM(0);
            facingRight();
        }
  
        width = x + 0.25;
        while(x < width){
            if(obstacle_Detection_left() || obstacle_Detection_right()){
              break;
            }
            Tank.setLeftMotorPWM(255);
            Tank.setRightMotorPWM(255);
            location();
          }
          Tank.setLeftMotorPWM(0);
          Tank.setRightMotorPWM(0);
        
  			 	
  			}else{
            while(obstacle_Detection_left() || obstacle_Detection_right()){
            if(facingDown()){
              length = y - 0.1;
              while(y >= length){
                if(obstacle_Detection_left()){
                    facingRight();
                    Tank.setLeftMotorPWM(255);
                    Tank.setRightMotorPWM(255);
                    delay(250);
                    Tank.setLeftMotorPWM(0);
                    Tank.setRightMotorPWM(0);
                    break;
                  }
                  Tank.setLeftMotorPWM(255);
                  Tank.setRightMotorPWM(255);
                  location();
                }
              }
               Tank.setLeftMotorPWM(0);
               Tank.setRightMotorPWM(0);
              facingRight();
          }
    
          width = x + 0.25;
          while(x < width){
              if(obstacle_Detection_left() || obstacle_Detection_right()){
                break;
              }
              Tank.setLeftMotorPWM(255);
              Tank.setRightMotorPWM(255);
              location();
            }
            Tank.setLeftMotorPWM(0);
            Tank.setRightMotorPWM(0);
          
  			}
			}
		}else if(y <= 0.3){
			if(facingUp()){
  			if(obstacle_Detection_left() || obstacle_Detection_right()){
  				if(facingLeft()){
  				width = x - 0.25;
  				while(x > width){
           if(obstacle_Detection_left() || obstacle_Detection_right()){
              break;
            }
  					Tank.setLeftMotorPWM(255);
  					Tank.setRightMotorPWM(255);
  					location();
  				}
  				Tank.setLeftMotorPWM(0);
  				Tank.setRightMotorPWM(0);
  				}
  				if(facingUp()){
  				length = y - 0.55;
  				while(y > length){
            if(obstacle_Detection_left() || obstacle_Detection_right()){
              break;
            }
  					Tank.setLeftMotorPWM(255);
  					Tank.setRightMotorPWM(255);
  					location();
  				}
  				Tank.setLeftMotorPWM(0);
  				Tank.setRightMotorPWM(0);
  				}
				  facingRight();
          
          while(obstacle_Detection_left() || obstacle_Detection_right()){
            if(facingUp()){
              length = y + 0.1;
              while(y <= length){
                if(obstacle_Detection_left()){
                    facingRight();
                    Tank.setLeftMotorPWM(255);
                    Tank.setRightMotorPWM(255);
                    delay(250);
                    Tank.setLeftMotorPWM(0);
                    Tank.setRightMotorPWM(0);
                    break;
                  }
                  Tank.setLeftMotorPWM(255);
                  Tank.setRightMotorPWM(255);
                  location();
                }
              }
               Tank.setLeftMotorPWM(0);
               Tank.setRightMotorPWM(0);
              facingRight();
          }
    
          width = x + 0.25;
          while(x < width){
              if(obstacle_Detection_left() || obstacle_Detection_right()){
                break;
              }
              Tank.setLeftMotorPWM(255);
              Tank.setRightMotorPWM(255);
              location();
            }
            Tank.setLeftMotorPWM(0);
            Tank.setRightMotorPWM(0);
      
			}else{
        
				while(obstacle_Detection_left() || obstacle_Detection_right()){
        if(facingUp()){
          length = y + 0.1;
          while(y <= length){
            if(obstacle_Detection_left()){
                facingRight();
                Tank.setLeftMotorPWM(255);
                Tank.setRightMotorPWM(255);
                delay(250);
                Tank.setLeftMotorPWM(0);
                Tank.setRightMotorPWM(0);
                break;
              }
              Tank.setLeftMotorPWM(255);
              Tank.setRightMotorPWM(255);
              location();
            }
          }
           Tank.setLeftMotorPWM(0);
           Tank.setRightMotorPWM(0);
          facingRight();
      }

      width = x + 0.25;
      while(x < width){
          if(obstacle_Detection_left() || obstacle_Detection_right()){
            break;
          }
          Tank.setLeftMotorPWM(255);
          Tank.setRightMotorPWM(255);
          location();
        }
        Tank.setLeftMotorPWM(0);
        Tank.setRightMotorPWM(0);
      
			}
			}
			
		}else if (beta >= 0){
      while(obstacle_Detection_left() || obstacle_Detection_right()){
        if(facingUp()){
          length = y + 0.1;
          while(y <= length){
            if(obstacle_Detection_left()){
                facingRight();
                Tank.setLeftMotorPWM(255);
                Tank.setRightMotorPWM(255);
                delay(250);
                Tank.setLeftMotorPWM(0);
                Tank.setRightMotorPWM(0);
                break;
              }
              Tank.setLeftMotorPWM(255);
              Tank.setRightMotorPWM(255);
              location();
            }
          }
           Tank.setLeftMotorPWM(0);
           Tank.setRightMotorPWM(0);
          facingRight();
      }

      width = x + 0.25;
      while(x < width){
          if(obstacle_Detection_left() || obstacle_Detection_right()){
            break;
          }
          Tank.setLeftMotorPWM(255);
          Tank.setRightMotorPWM(255);
          location();
        }
        Tank.setLeftMotorPWM(0);
        Tank.setRightMotorPWM(0);
      
      
		}
	}else if(beta < 0){
    while(obstacle_Detection_left() || obstacle_Detection_right()){
          if(facingDown()){
            length = y - 0.1;
            while(y >= length){
              if(obstacle_Detection_right()){
                  facingRight();
                  Tank.setLeftMotorPWM(255);
                  Tank.setRightMotorPWM(255);
                  delay(250);
                  Tank.setLeftMotorPWM(0);
                  Tank.setRightMotorPWM(0);
                  break;
                }
                Tank.setLeftMotorPWM(255);
                Tank.setRightMotorPWM(255);
                location();
              }
            }
             Tank.setLeftMotorPWM(0);
             Tank.setRightMotorPWM(0);
            facingRight();
        }
  
        width = x + 0.25;
        while(x < width){
            if(obstacle_Detection_left() || obstacle_Detection_right()){
              break;
            }
            Tank.setLeftMotorPWM(255);
            Tank.setRightMotorPWM(255);
            location();
          }
          Tank.setLeftMotorPWM(0);
          Tank.setRightMotorPWM(0);
	}
}
