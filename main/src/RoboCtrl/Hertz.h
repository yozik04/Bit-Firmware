#ifndef BIT_FIRMWARE_HERTZ_H
#define BIT_FIRMWARE_HERTZ_H

#include "RobotDriver.h"
#include "Services/ChirpSystem.h"
#include "Periph/PinOut.h"

namespace RoboCtrl {

class Hertz : public RobotDriver {
public:
	Hertz();

	void play(std::initializer_list<Chirp> sound);
	void play(const Sound& sound);
	void stop();

	void setMute(bool mute);
	bool isMuted() const;

	void ledOn();
	void ledOff();


private:
	PWM pwm;
	ChirpSystem chirpSystem;
	PinOut led;
};

}

#endif //BIT_FIRMWARE_HERTZ_H
