#include "Resistron.h"

RoboCtrl::Resistron::Resistron() : RobotDriver(Robot::Resistron), led1(CTRL_1), led2(CTRL_2){
}

RoboCtrl::Resistron::~Resistron(){
	led1.end();
	led2.end();
}

void RoboCtrl::Resistron::blink(){
	led1.blink(255);
	led2.blink(255);
}

void RoboCtrl::Resistron::blinkContinuous(){
	led1.blinkContinuous(255);
	led2.blinkContinuous(255);
}

void RoboCtrl::Resistron::blinkTwice(){
	led1.blinkTwice(255);
	led2.blinkTwice(255);
}
