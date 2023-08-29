#include "Marv.h"
#include "Pins.hpp"

RoboCtrl::Marv::Marv() :  RobotDriver(Robot::Marv), counter(PinOut(CTRL_1), PinOut(CTRL_2), *this){
}

void RoboCtrl::Marv::reset(){
	counter.reset();
}

void RoboCtrl::Marv::nextLED(){
	counter.tick();
}

void RoboCtrl::Marv::startRunning(uint32_t tickTime){
	counter.startRunning(tickTime);
}

void RoboCtrl::Marv::stopRunning(){
	counter.stopRunning();

}

void RoboCtrl::Marv::setSpeed(uint32_t tickTime){
	counter.setSpeed(tickTime);
}
