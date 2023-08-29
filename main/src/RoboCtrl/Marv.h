#ifndef BIT_FIRMWARE_MARV_H
#define BIT_FIRMWARE_MARV_H

#include "RoboCounter.h"
#include "RobotDriver.h"

namespace RoboCtrl {

class Marv : public RobotDriver{
	Marv();
	void reset();
	void nextLED();
	void startRunning(uint32_t tickTime);
	void stopRunning();
	void setSpeed(uint32_t tickTime);

private:
	RoboCounter counter;
};

}
#endif //BIT_FIRMWARE_MARV_H
