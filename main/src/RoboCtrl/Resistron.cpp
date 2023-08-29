#include "Resistron.h"

RoboCtrl::Resistron::Resistron() : RobotDriver(Robot::Resistron), led1Pin(CTRL_1), led2Pin(CTRL_2), led1(led1Pin), led2(led2Pin){
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
