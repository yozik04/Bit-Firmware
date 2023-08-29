#include "Hertz.h"

RoboCtrl::Hertz::Hertz() : RobotDriver(Robot::Hertz), pwm(CTRL_1, LEDC_CHANNEL_2), chirpSystem(pwm), led(CTRL_2){
}

void RoboCtrl::Hertz::hello(){

}

void RoboCtrl::Hertz::init(){
	led.begin();
}

void RoboCtrl::Hertz::deinit(){
	led.end();
	chirpSystem.stop();
}

void RoboCtrl::Hertz::playGood(){
	chirpSystem.play({ { 80,   800,  100 },
					   { 0,    0,    50 },
					   { 80,   1000, 150 },
					   { 1000, 80,   150 } });
	led.blinkTwice(255);
}

void RoboCtrl::Hertz::playBad(){
	chirpSystem.play({ { 400, 200, 100 },
					   { 0,   0,   100 },
					   { 200, 70,  100 } });
	led.blink(255);

}

void RoboCtrl::Hertz::playDone(){
	Sound s = { { 400, 300,  100 },
				{ 0,   0,    25 },
				{ 300, 200,  100 },
				{ 0,   0,    25 },
				{ 300, 200,  100 },
				{ 0,   0,    25 },
				{ 800, 1000, 200 } };
	chirpSystem.play(s);
	led.blinkContinuous(255);
}
