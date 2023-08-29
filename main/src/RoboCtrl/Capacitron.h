#ifndef BIT_FIRMWARE_CAPACITRON_H
#define BIT_FIRMWARE_CAPACITRON_H

#include "Devices/LEDController.h"
#include "RobotDriver.h"

namespace RoboCtrl {

class Capacitron : public RobotDriver{
public:
	Capacitron();
	virtual ~Capacitron();
	void hello() override;

	void leftRightContinuous(uint32_t period); //default
	void allOn(); //powerup
	void flashingContinuous(); //damage/death

protected:
	void init() override;
	void deinit() override;

private:
	DigitalLEDController led1;
	DigitalLEDController led2;
};
}

#endif //BIT_FIRMWARE_CAPACITRON_H
