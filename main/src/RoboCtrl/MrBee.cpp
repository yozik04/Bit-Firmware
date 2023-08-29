#include "MrBee.h"

RoboCtrl::MrBee::MrBee() : RobotDriver(Robot::MrBee), ledPin(CTRL_1), led(ledPin){

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
