#include "Capacitron.h"
#include "Pins.hpp"

RoboCtrl::Capacitron::Capacitron() : RobotDriver(Robot::Capacitron), led1(CTRL_1), led2(CTRL_2){

}

void RoboCtrl::Capacitron::hello(){

}

void RoboCtrl::Capacitron::init(){
	led1.begin();
	led2.begin();
}

void RoboCtrl::Capacitron::deinit(){
	led1.end();
	led2.end();
}

void RoboCtrl::Capacitron::leftRightContinuous(uint32_t period){
	led1.breathe(255, 0, period);
	led2.breathe(0, 255, period);
}

void RoboCtrl::Capacitron::allOn(){
	led1.setSolid(255);
	led2.setSolid(255);
}

void RoboCtrl::Capacitron::flashingContinuous(){
	led1.blinkContinuous(255, -1, 300, 300);
	led2.blinkContinuous(255, -1, 300, 300);
}
