#ifndef BIT_FIRMWARE_BOB_H
#define BIT_FIRMWARE_BOB_H

#include "Periph/PinOut.h"
#include "RobotDriver.h"

namespace RoboCtrl {

class Bob : public RobotDriver {
public:
	Bob();
	void ledsOn();
	void ledsOff();

private:
	PinOut leds;
};

}

#endif //BIT_FIRMWARE_BOB_H
