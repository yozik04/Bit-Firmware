#ifndef BIT_FIRMWARE_RESISTRON_H
#define BIT_FIRMWARE_RESISTRON_H

#include "RobotDriver.h"
#include "Periph/PinOut.h"


namespace RoboCtrl {

class Resistron : public RobotDriver {
public:
	Resistron();
	void setLeftLED(bool state);
	void setRightLED(bool state);
private:
	PinOut led1;
	PinOut led2;
};

}

#endif //BIT_FIRMWARE_RESISTRON_H
