#ifndef BIT_FIRMWARE_HERTZ_H
#define BIT_FIRMWARE_HERTZ_H

#include "RobotDriver.h"
#include "Services/ChirpSystem.h"
#include "Devices/LEDController.h"

namespace RoboCtrl {

class Hertz : public RobotDriver {
public:
	Hertz();
	virtual ~Hertz();
	void playGood();
	void playBad();
	void playDone();

	void hello() override;
protected:
	void init() override;
	void deinit() override;
private:
	PWM pwm;
	ChirpSystem chirpSystem;
	DigitalLEDController led;
};

}

#endif //BIT_FIRMWARE_HERTZ_H
