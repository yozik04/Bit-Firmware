#ifndef BIT_FIRMWARE_MRBEE_H
#define BIT_FIRMWARE_MRBEE_H

#include "RobotDriver.h"
#include "Periph/PinOut.h"

namespace RoboCtrl {

class MrBee : public RobotDriver {
public:
	MrBee();
	void ledOn();
	void ledOff();
private:
	PinOut led;
};

}

#endif //BIT_FIRMWARE_MRBEE_H
