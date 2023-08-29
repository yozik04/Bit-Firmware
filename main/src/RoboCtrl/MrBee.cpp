#include "MrBee.h"

RoboCtrl::MrBee::MrBee() : RobotDriver(Robot::MrBee), led(CTRL_1){
	if(!checkRobot()) return;

	led.off();
}

void RoboCtrl::MrBee::ledOn(){
	if(!checkRobot()) return;

	led.on();
}

void RoboCtrl::MrBee::ledOff(){
	if(!checkRobot()) return;

	led.off();
}
