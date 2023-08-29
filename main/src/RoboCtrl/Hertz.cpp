#include "Hertz.h"

RoboCtrl::Hertz::Hertz() : RobotDriver(Robot::Hertz), pwm(CTRL_1, LEDC_CHANNEL_2), chirpSystem(pwm), led(CTRL_2){
	if(!checkRobot()) return;

	led.off();
}

void RoboCtrl::Hertz::play(std::initializer_list<Chirp> sound){
	if(!checkRobot()) return;
	chirpSystem.play(sound);
}

void RoboCtrl::Hertz::play(const Sound& sound){
	if(!checkRobot()) return;
	chirpSystem.play(sound);
}

void RoboCtrl::Hertz::stop(){
	chirpSystem.stop();
}

void RoboCtrl::Hertz::setMute(bool mute){
	chirpSystem.setMute(mute);
}

bool RoboCtrl::Hertz::isMuted() const{
	return chirpSystem.isMuted();
}

void RoboCtrl::Hertz::ledOn(){
	if(!checkRobot()) return;
	led.on();
}

void RoboCtrl::Hertz::ledOff(){
	if(!checkRobot()) return;
	led.off();
}
