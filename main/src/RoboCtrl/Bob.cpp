#include "Bob.h"
#include "Pins.hpp"

RoboCtrl::Bob::Bob() : RobotDriver(Robot::Capacitron), leds(CTRL_1){
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
	leds.blinkContinuous(255, 4, 1000, 300);
}

void RoboCtrl::Bob::blinkContinuousFast(){
	leds.blinkContinuous(255, -1, 300, 300);
}
