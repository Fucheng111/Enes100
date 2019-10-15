#include "Enes100.h"
#include "Tank.h"

void setup() {
	Enes100.begin("Aqua Terp", WATER, 3, 8, 9);
	Tank.begin();
	Tank.setLeftMotorPWM(255);
	Tank.setRightMotorPWM(255);
}

void loop() {

}
