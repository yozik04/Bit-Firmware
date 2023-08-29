#include "Capacitron.h"
#include "Pins.hpp"

RoboCtrl::Capacitron::Capacitron() : RobotDriver(Robot::Capacitron), led1(CTRL_1), led2(CTRL_2){
	if(!checkRobot()) return;

	led1.off();
	led2.off();
}

void RoboCtrl::Capacitron::setLeftLED(bool state){
	if(!checkRobot()) return;
	state ? led1.on() : led1.off();
}

void RoboCtrl::Capacitron::setRightLED(bool state){
	if(!checkRobot()) return;
	state ? led2.on() : led2.off();
}
