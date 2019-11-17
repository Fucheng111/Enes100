#include "Enes100.h"

double x;
double y;
double destination_x;
double destination_y;
bool salty;
bool polluted;

void setup() {
  // put your setup code here, to run once:
  //Params: team name, team mission, marker #, TX Pin, RX Pin
  Enes100.begin("Aqua Terps", WATER, 15,10, 11);
  Enes100.println("Start");

  destination_x= Enes100.destination.x; 
  destination_y= Enes100.destination.y; 

  while(!Enes100.updateLocation()){
    Enes100.println("Fail to update location");
  }

  Enes100.println("Update Location");

  x = Enes100.location.x;
  y = Enes100.location.y;

  salty = false;
  polluted = false;

}

void loop() {

  while(!Enes100.updateLocation()){
    Enes100.println("Fail to update location");
  }

  Enes100.println("Update Location");

  x = Enes100.location.x;
  y = Enes100.location.y;

  // Change 0.15 to the correct threshold to find out the correct distance to stop
  if(sqrt(pow(destination_x-x,2)+pow(destination_y-y,2)) <= 0.15){
    //load the water code here

    //if salty change salty = true
    //if polluted, change polluted = true

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

}
