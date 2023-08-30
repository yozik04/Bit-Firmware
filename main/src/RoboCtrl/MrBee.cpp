#include "MrBee.h"

RoboCtrl::MrBee::MrBee() : RobotDriver(Robot::MrBee), led(CTRL_1){

}

RoboCtrl::MrBee::~MrBee(){
	led.end();
}

void RoboCtrl::MrBee::blink(){
	led.blink(255);
}

void RoboCtrl::MrBee::hello(){

}

void RoboCtrl::MrBee::init(){
	led.begin();
}

void RoboCtrl::MrBee::deinit(){
	led.end();
}

void RoboCtrl::MrBee::blinkContinuousFast(){
	led.blinkContinuous(255, -1, 100, 100);
}

void RoboCtrl::MrBee::ledOff(){
	led.clear();
}
