#ifndef BIT_FIRMWARE_RESISTRON_H
#define BIT_FIRMWARE_RESISTRON_H

#include "RobotDriver.h"
#include "Devices/LEDController.h"


namespace RoboCtrl {

class Resistron : public RobotDriver {
public:
	Resistron();
	virtual ~Resistron();
	void blink();
	void blinkTwice();
	void blinkContinuous();

private:
	DigitalLEDController led1;
	DigitalLEDController led2;

};

}

#endif //BIT_FIRMWARE_RESISTRON_H
