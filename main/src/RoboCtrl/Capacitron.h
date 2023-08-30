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
	void flashingContinuous(int32_t repeats); //damage/death

protected:
	void onLoop(uint micros) override;

	void init() override;
	void deinit() override;

private:
	DigitalLEDController led1;
	DigitalLEDController led2;

	bool leftRightAnim = false;
	uint32_t leftRightTime = 0;
	uint32_t timer = 0;
	bool ledIndex = false;
};
}

#endif //BIT_FIRMWARE_CAPACITRON_H
