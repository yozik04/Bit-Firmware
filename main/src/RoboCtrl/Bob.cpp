#include "Bob.h"
#include "Pins.hpp"

RoboCtrl::Bob::Bob() :  RobotDriver(Robot::Capacitron), leds(CTRL_1){
	if(!checkRobot()) return;

	leds.off();
}

void RoboCtrl::Bob::ledsOn(){
	if(!checkRobot()) return;

	leds.on();
}

void RoboCtrl::Bob::ledsOff(){
	if(!checkRobot()) return;

	leds.off();
}
