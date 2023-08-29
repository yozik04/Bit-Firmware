#include "Bob.h"
#include "Pins.hpp"

RoboCtrl::Bob::Bob() : RobotDriver(Robot::Bob), leds(CTRL_1, false){
}

RoboCtrl::Bob::~Bob(){
	leds.end();
}

void RoboCtrl::Bob::hello(){

}

void RoboCtrl::Bob::init(){
	leds.begin();
}

void RoboCtrl::Bob::deinit(){
	leds.end();
}

void RoboCtrl::Bob::blink(){
	leds.blink(255);
}

void RoboCtrl::Bob::blinkContinuousSlow(){
	leds.blinkContinuous(255, -1, 300, 100);
}

void RoboCtrl::Bob::blinkContinuousFast(){
	leds.blinkContinuous(255, -1, 100, 100);
}

void RoboCtrl::Bob::blinkTwice(){
	leds.blinkTwice(255);
}
