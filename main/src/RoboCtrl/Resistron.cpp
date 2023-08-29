#include "Resistron.h"

RoboCtrl::Resistron::Resistron() : RobotDriver(Robot::Resistron), led1(CTRL_1), led2(CTRL_2){
}

RoboCtrl::Resistron::~Resistron(){
	led1.end();
	led2.end();
}

void RoboCtrl::Resistron::blink(){
	repeatNum = 2;
	repeatCounter = 0;
	timer = 0;
	leftRightTime = BlinkTime;
	leftRightAnim = true;
}

void RoboCtrl::Resistron::blinkContinuous(){
	repeatNum = -1;
	repeatCounter = 0;
	timer = 0;
	leftRightTime = BlinkTime;
	leftRightAnim = true;
}

void RoboCtrl::Resistron::blinkTwice(){
	repeatNum = 4;
	repeatCounter = 0;
	timer = 0;
	leftRightTime = BlinkTime;
	leftRightAnim = true;
}

void RoboCtrl::Resistron::hello(){

}

void RoboCtrl::Resistron::init(){
	led1.begin();
	led2.begin();
}

void RoboCtrl::Resistron::deinit(){
	led1.end();
	led2.end();
}

void RoboCtrl::Resistron::onLoop(uint micros){
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
		repeatCounter++;
		if(repeatCounter > repeatNum){
			leftRightAnim = false;
			repeatCounter = 0;
			led1.clear();
			led2.clear();
			return;
		}
	}
}
