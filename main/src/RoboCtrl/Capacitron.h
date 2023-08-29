#ifndef BIT_FIRMWARE_CAPACITRON_H
#define BIT_FIRMWARE_CAPACITRON_H

#include "Periph/PinOut.h"
#include "RobotDriver.h"

namespace RoboCtrl {

class Capacitron : public RobotDriver{
public:
	Capacitron();
	void setLeftLED(bool state);
	void setRightLED(bool state);

private:
	PinOut led1;
	PinOut led2;
};
}

#endif //BIT_FIRMWARE_CAPACITRON_H
