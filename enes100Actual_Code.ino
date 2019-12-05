#include "Enes100.h"
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
const int dis_sen_right = A0;  
const int dis_sen_left = A1;
int m1 = 4;
int e1 = 5;
int m2 = 7;
int e2 = 6;

bool faceTarget;
bool faceRight;
bool faceLeft;
bool faceUp;
bool faceDown;
bool forceStop;


void setup() {
	Enes100.begin("Aqua Terps", WATER, 15,10, 11);

	
	while(!location()){
  
	}
	destination_x= Enes100.destination.x; 
	destination_y= Enes100.destination.y; 
  pinMode(m1, OUTPUT);
  pinMode(e1, OUTPUT);
  pinMode(m2, OUTPUT);
  pinMode(e2, OUTPUT);

	faceTarget = false;
  faceRight =false;
  faceLeft = false;
  faceUp = false;
  faceDown = false;
  forceStop = false;

  speed_turning = 40;

  Enes100.println("Start");
  
}

void loop() {

 
  if(facingTarget()){
       
   Enes100.println("Starts");
   setLeftMotor(255);
   setRightMotor(255);
   
   while(!(obstacle_Detection_right()||obstacle_Detection_left())){

         setLeftMotor(255);
         setRightMotor(255);
        while(!location()){
                Enes100.println("Unable to update location");
                setLeftMotor(0);
                setRightMotor(0);
            }
        
       if(sqrt(pow(destination_x-x,2)+pow(destination_y-y,2)) <= 0.15){
          setLeftMotor(0);
          setRightMotor(0);
          while(1){
            
          }
       }
   }
  
   
   setLeftMotor(0);
   setRightMotor(0);
    while(!location()){
                Enes100.println("Unable to update location");
                setLeftMotor(0);
                setRightMotor(0);
   }
   avoid_obstacles();
  }else{
    setLeftMotor(255);
    setRightMotor(255);
    delay(1000);
    setLeftMotor(0);
    setRightMotor(0);
  }

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
			setLeftMotor(255);
			setRightMotor(-255);
      

		}
		else if (theta < -0.05 && theta >= -3.14){
			setLeftMotor(-255);
			setRightMotor(255);
      
		}else{
      setLeftMotor(-255);
      setRightMotor(255);
      
     
		}
   
   if((millis() -time) >= 10000){
     setLeftMotor(-255);
      setRightMotor(-255);
      delay(500);
      setLeftMotor(0);
      setRightMotor(0);
      Enes100.println("Facing Right Fail");
      faceRight = false;
      return false;
   }
   
//   setLeftMotor(0);
//   setRightMotor(0);
//   delay(detection_time);
   while(!location()){
    Enes100.println("Unable to update location");
    setLeftMotor(0);
      setRightMotor(0);
   }

	}
	setLeftMotor(0);
	setRightMotor(0);
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
	while(fabs(theta)<3.09){
  
    
		if(theta > 0.05 && theta <= 3.14){
			setLeftMotor(-255);
			setRightMotor(255);
     
     
		
		}else if(theta >= -3.14 && theta <= -0.05){
			setLeftMotor(255);
			setRightMotor(-255);
      
      
		}
   else{
      setLeftMotor(255);
      setRightMotor(-255);
      
      
   }
   if((millis() -time) >= 10000){
    setLeftMotor(0);
      setRightMotor(0);
      return false;
   }
//   setLeftMotor(0);
//   setRightMotor(0);
//   delay(detection_time);
   while(!location()){
    Enes100.println("Unable to update location");
    setLeftMotor(0);
      setRightMotor(0);
   }
 
    
   
	}

	setLeftMotor(0);
	setRightMotor(0);
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
	while(theta < 1.52 || theta > 1.62 ){
		
		if(theta >= -1.57 && theta < 1.57){
			setLeftMotor(-255);
			setRightMotor(255);
      
    
		
		}else if((theta >= 1.57 && theta <= 3.14 )|| (theta >=-3.14 && theta < -1.57)){
			setLeftMotor(255);
			setRightMotor(-255);
      
      
		}else{
      setLeftMotor(255);
      setRightMotor(-255);
      
      
		}
   if((millis() -time) >= 10000){
          setLeftMotor(-255);
          setRightMotor(-255);
          delay(500);
          setLeftMotor(0);
          setRightMotor(0);
          Enes100.println("Facing Up Fail");
          return false;
   }
   
//   setLeftMotor(0);
//   setRightMotor(0);
//   delay(detection_time);
   while(!location()){
    Enes100.println("Unable to update location");
    setLeftMotor(0);
      setRightMotor(0);
   }
   
	}
	
	setLeftMotor(0);
	setRightMotor(0);

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
	while(theta > -1.52 || theta < -1.62 ){
		
   
		if(theta >= -1.57 && theta < 1.57){
			setLeftMotor(255);
			setRightMotor(-255);
      
     
		
		}else if((theta >= 1.57 && theta <= 3.14) || (theta >=-3.14 && theta <= -1.57)){
			setLeftMotor(-255);
			setRightMotor(255);
     
      
		}else{
      setLeftMotor(255);
      setRightMotor(-255);
      
     
   }
   
   if((millis() -time) >= 10000){
    setLeftMotor(-255);
    setRightMotor(-255);
     delay(500);
    setLeftMotor(0);
    setRightMotor(0);
    Enes100.println("Facing Down Fail");
      return false;
   }
//   setLeftMotor(0);
//   setRightMotor(0);
//   delay(detection_time);
   while(!location()){
    Enes100.println("Unable to update location");
    setLeftMotor(0);
      setRightMotor(0);
   }
 
	}
	
	setLeftMotor(0);
	setRightMotor(0);
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
    
    while(fabs(theta - beta) > 0.05){
      
      setLeftMotor(-255);
      setRightMotor(255);

      
     
      if((millis() - time) >= 10000){
          
        setLeftMotor(0);
        setRightMotor(0);
        Enes100.println("Facing Target Fail");
        faceRight =false;
        faceLeft = false;
        faceUp = false;
        faceDown = false;
        faceTarget = false;
        return false;
      }
//      setLeftMotor(0);
//   setRightMotor(0);
//   delay(detection_time);
   while(!location()){
    Enes100.println("Unable to update location");
    setLeftMotor(0);
      setRightMotor(0);
   }
      
    }
    faceTarget = true;
    Enes100.println("Facing Target");
   
	}else if(beta <0){
    while(fabs(theta - beta) > 0.05){
      
      setLeftMotor(255);
      setRightMotor(-255);
      
      
      
      if((millis() -time) >= 10000){
        Enes100.println("Facing Target Fail");
        
      setLeftMotor(0);
      setRightMotor(0);
      faceRight =false;
        faceLeft = false;
        faceUp = false;
        faceDown = false;
        faceTarget = false;
      return false;
   }
//   setLeftMotor(0);
//   setRightMotor(0);
//   delay(detection_time);
   while(!location()){
    Enes100.println("Unable to update location");
    setLeftMotor(0);
      setRightMotor(0);
   }
     
    }
    faceTarget = true;
    Enes100.println("Facing Target");
    
	}

 faceTarget = true;
 Enes100.println("Facing Target");
 setLeftMotor(0);
 setRightMotor(0);
 
  faceRight =false;
  faceLeft = false;
  faceUp = false;
  faceDown = false;

  return true;
}

bool obstacle_Detection_right(){
  
	if( Enes100.readDistanceSensor(2)< 0.15){
    
    Enes100.print("Sensor Right: ");
    Enes100.println(Enes100.readDistanceSensor(2));
		return true;
	}
  Enes100.print("Sensor Right: ");
    Enes100.println(Enes100.readDistanceSensor(2));
   
	
	return false;
}

bool obstacle_Detection_left(){
  
	if( Enes100.readDistanceSensor(0) < 0.15){
    Enes100.print("Sensor Left: ");
    Enes100.println(Enes100.readDistanceSensor(0) );
    
		return true;
	}
	Enes100.print("Sensor Left: ");
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
  					setLeftMotor(255);
  					setRightMotor(255);
  					while(!location()){
                Enes100.println("Unable to update location");
                setLeftMotor(0);
                setRightMotor(0);
            }
  				}
  				setLeftMotor(0);
  				setRightMotor(0);
  				}
  				if(facingDown()){
  				length = y - 0.55;
  				while(y > length){
            if(obstacle_Detection_left() || obstacle_Detection_right()){
              break;
            }
  					setLeftMotor(255);
  					setRightMotor(255);
  					while(!location()){
                Enes100.println("Unable to update location");
                setLeftMotor(0);
                setRightMotor(0);
            }
  				}
  				setLeftMotor(0);
  				setRightMotor(0);
  				}
  				facingRight();
          
          while(obstacle_Detection_left() || obstacle_Detection_right()){
          if(facingDown()){
            length = y - 0.1;
            while(y >= length){
              if(obstacle_Detection_left()){
                  facingRight();
                  setLeftMotor(255);
                  setRightMotor(255);
                  delay(250);
                  setLeftMotor(0);
                  setRightMotor(0);
                  break;
                }
                setLeftMotor(255);
                setRightMotor(255);
                while(!location()){
                Enes100.println("Unable to update location");
                setLeftMotor(0);
                setRightMotor(0);
            }
              }
            }
             setLeftMotor(0);
             setRightMotor(0);
            facingRight();
        }
  
        width = x + 0.25;
        while(x < width){
            if(obstacle_Detection_left() || obstacle_Detection_right()){
              break;
            }
            setLeftMotor(255);
            setRightMotor(255);
            while(!location()){
                Enes100.println("Unable to update location");
                setLeftMotor(0);
                setRightMotor(0);
            }
          }
          setLeftMotor(0);
          setRightMotor(0);
        
  			 	
  			}else{
            while(obstacle_Detection_left() || obstacle_Detection_right()){
            if(facingDown()){
              length = y - 0.1;
              while(y >= length){
                if(obstacle_Detection_left()){
                    facingRight();
                    setLeftMotor(255);
                    setRightMotor(255);
                    delay(250);
                    setLeftMotor(0);
                    setRightMotor(0);
                    break;
                  }
                  setLeftMotor(255);
                  setRightMotor(255);
                  while(!location()){
                      Enes100.println("Unable to update location");
                      setLeftMotor(0);
                      setRightMotor(0);
                  }
                }
              }
               setLeftMotor(0);
               setRightMotor(0);
              facingRight();
          }
    
          width = x + 0.25;
          while(x < width){
              if(obstacle_Detection_left() || obstacle_Detection_right()){
                break;
              }
              setLeftMotor(255);
              setRightMotor(255);
              while(!location()){
                Enes100.println("Unable to update location");
                setLeftMotor(0);
                setRightMotor(0);
            }
            }
            setLeftMotor(0);
            setRightMotor(0);
          
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
  					setLeftMotor(255);
  					setRightMotor(255);
  					while(!location()){
                Enes100.println("Unable to update location");
                setLeftMotor(0);
                setRightMotor(0);
            }
  				}
  				setLeftMotor(0);
  				setRightMotor(0);
  				}
  				if(facingUp()){
  				length = y - 0.55;
  				while(y > length){
            if(obstacle_Detection_left() || obstacle_Detection_right()){
              break;
            }
  					setLeftMotor(255);
  					setRightMotor(255);
  					while(!location()){
                Enes100.println("Unable to update location");
                setLeftMotor(0);
                setRightMotor(0);
            }
  				}
  				setLeftMotor(0);
  				setRightMotor(0);
  				}
				  facingRight();
          
          while(obstacle_Detection_left() || obstacle_Detection_right()){
            if(facingUp()){
              length = y + 0.1;
              while(y <= length){
                if(obstacle_Detection_left()){
                    facingRight();
                    setLeftMotor(255);
                    setRightMotor(255);
                    delay(250);
                    setLeftMotor(0);
                    setRightMotor(0);
                    break;
                  }
                  setLeftMotor(255);
                  setRightMotor(255);
                  while(!location()){
                Enes100.println("Unable to update location");
                setLeftMotor(0);
                setRightMotor(0);
            }
                }
              }
               setLeftMotor(0);
               setRightMotor(0);
              facingRight();
          }
    
          width = x + 0.25;
          while(x < width){
              if(obstacle_Detection_left() || obstacle_Detection_right()){
                break;
              }
              setLeftMotor(255);
              setRightMotor(255);
              while(!location()){
                Enes100.println("Unable to update location");
                setLeftMotor(0);
                setRightMotor(0);
            }
            }
            setLeftMotor(0);
            setRightMotor(0);
      
			}else{
        
				while(obstacle_Detection_left() || obstacle_Detection_right()){
        if(facingUp()){
          length = y + 0.1;
          while(y <= length){
            if(obstacle_Detection_left()){
                facingRight();
                setLeftMotor(255);
                setRightMotor(255);
                delay(250);
                setLeftMotor(0);
                setRightMotor(0);
                break;
              }
              setLeftMotor(255);
              setRightMotor(255);
              while(!location()){
                Enes100.println("Unable to update location");
                setLeftMotor(0);
                setRightMotor(0);
            }
            }
          }
           setLeftMotor(0);
           setRightMotor(0);
          facingRight();
      }

      width = x + 0.25;
      while(x < width){
          if(obstacle_Detection_left() || obstacle_Detection_right()){
            break;
          }
          setLeftMotor(255);
          setRightMotor(255);
          while(!location()){
                Enes100.println("Unable to update location");
                setLeftMotor(0);
                setRightMotor(0);
            }
        }
        setLeftMotor(0);
        setRightMotor(0);
      
			}
			}
			
		}else if (beta >= 0){
      while(obstacle_Detection_left() || obstacle_Detection_right()){
        if(facingUp()){
          length = y + 0.1;
          while(y <= length){
            if(obstacle_Detection_left()){
                facingRight();
                setLeftMotor(255);
                setRightMotor(255);
                delay(250);
                setLeftMotor(0);
                setRightMotor(0);
                break;
              }
              setLeftMotor(255);
              setRightMotor(255);
              while(!location()){
                Enes100.println("Unable to update location");
                setLeftMotor(0);
                setRightMotor(0);
            }
            }
          }
           setLeftMotor(0);
           setRightMotor(0);
          facingRight();
      }

      width = x + 0.25;
      while(x < width){
          if(obstacle_Detection_left() || obstacle_Detection_right()){
            break;
          }
          setLeftMotor(255);
          setRightMotor(255);
          while(!location()){
                Enes100.println("Unable to update location");
                setLeftMotor(0);
                setRightMotor(0);
            }
        }
        setLeftMotor(0);
        setRightMotor(0);
      
      
		}
	}else if(beta < 0){
    while(obstacle_Detection_left() || obstacle_Detection_right()){
          if(facingDown()){
            length = y - 0.1;
            while(y >= length){
              if(obstacle_Detection_right()){
                  facingRight();
                  setLeftMotor(255);
                  setRightMotor(255);
                  delay(250);
                  setLeftMotor(0);
                  setRightMotor(0);
                  break;
                }
                setLeftMotor(255);
                setRightMotor(255);
                while(!location()){
                Enes100.println("Unable to update location");
                setLeftMotor(0);
                setRightMotor(0);
            }
              }
            }
             setLeftMotor(0);
             setRightMotor(0);
            facingRight();
        }
  
        width = x + 0.25;
        while(x < width){
            if(obstacle_Detection_left() || obstacle_Detection_right()){
              break;
            }
            setLeftMotor(255);
            setRightMotor(255);
            while(!location()){
                Enes100.println("Unable to update location");
                setLeftMotor(0);
                setRightMotor(0);
            }
          }
          setLeftMotor(0);
          setRightMotor(0);
	}
}

void setLeftMotor(char dir, int speed){
  digitalWrite(m1, dir);
  analogWrite(e1, speed);
}

void setRightMotor(char dir, int speed){
  digitalWrite(m2, dir);
  analogWrite(e2, speed);
}
