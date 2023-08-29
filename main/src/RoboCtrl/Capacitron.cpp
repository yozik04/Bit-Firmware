#include "Capacitron.h"
#include "Pins.hpp"

RoboCtrl::Capacitron::Capacitron() : RobotDriver(Robot::Capacitron), led1(CTRL_1), led2(CTRL_2){

}

RoboCtrl::Capacitron::~Capacitron(){
	led1.end();
	led2.end();
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
	led1.setSolid(255);
	led2.setSolid(0);
	leftRightAnim = true;
	leftRightTime = period;
}

void RoboCtrl::Capacitron::allOn(){
	led1.setSolid(255);
	led2.setSolid(255);
	leftRightAnim = false;
}

void RoboCtrl::Capacitron::flashingContinuous(int32_t repeats){
	led1.blinkContinuous(255, repeats, 300, 300);
	led2.blinkContinuous(255, repeats, 300, 300);
	leftRightAnim = false;
}

void RoboCtrl::Capacitron::onLoop(uint micros){
	if(!leftRightAnim) return;

	timer += micros;
	if(timer >= leftRightTime * 1000){
		if(ledIndex){
			led1.setSolid(255);
			led2.setSolid(0);
		}else{
			led1.setSolid(0);
			led2.setSolid(255);
		}
		ledIndex = !ledIndex;
		timer = 0;
	}
}
