#ifndef BIT_FIRMWARE_MRBEE_H
#define BIT_FIRMWARE_MRBEE_H

#include "RobotDriver.h"
#include "Periph/PinOut.h"
#include "Devices/LEDController.h"

namespace RoboCtrl {

class MrBee : public RobotDriver {
public:
	MrBee();
	void blink();
	void hello() override;

protected:
	void init() override;
	void deinit() override;

private:
	PinOut ledPin;
	DigitalLEDController led;
};

}

#endif //BIT_FIRMWARE_MRBEE_H
