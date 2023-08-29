#ifndef BIT_FIRMWARE_BOB_H
#define BIT_FIRMWARE_BOB_H

#include "Devices/LEDController.h"
#include "RobotDriver.h"

namespace RoboCtrl {

class Bob : public RobotDriver {
public:
	Bob();

	void hello() override;

	void blink();
	void blinkContinuousSlow();
	void blinkContinuousFast();

protected:
	void init() override;
	void deinit() override;

private:
	PinOut ledsPinout;
	DigitalLEDController leds;
};

}

#endif //BIT_FIRMWARE_BOB_H
