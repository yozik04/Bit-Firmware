#include "RoboCounter.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

RoboCtrl::RoboCounter::RoboCounter(const PinOut& clockPin, const PinOut& resetPin, const RobotDriver& driver) :
		driver(driver), clockPin(clockPin), resetPin(resetPin),
		thread([this](){ threadFunc(); }, "RoboCounter", 2048, 1){
	reset();
	this->clockPin.on();
}

void RoboCtrl::RoboCounter::tick(){
	if(!driver.checkRobot()) return;

	std::lock_guard lockGuard(pulseMutex);
	clockPin.off();
	vTaskDelay(1);
	clockPin.on();
}

void RoboCtrl::RoboCounter::reset(){
	if(!driver.checkRobot()) return;

	std::lock_guard lockGuard(pulseMutex);
	resetPin.on();
	vTaskDelay(1);
	resetPin.off();
}

void RoboCtrl::RoboCounter::startRunning(uint32_t tickTime){
	if(!driver.checkRobot()) thread.stop();
	if(thread.running()) return;

	this->tickTime = tickTime;
	thread.start();
}

void RoboCtrl::RoboCounter::stopRunning(){
	thread.stop();
}

void RoboCtrl::RoboCounter::setSpeed(uint32_t tickTime){
	if(!driver.checkRobot()) thread.stop();

	this->tickTime = tickTime;
}


void RoboCtrl::RoboCounter::threadFunc(){
	tick();
	vTaskDelay(tickTime);
}
