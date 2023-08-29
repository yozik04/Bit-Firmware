#ifndef BIT_FIRMWARE_ROBOCOUNTER_H
#define BIT_FIRMWARE_ROBOCOUNTER_H

#include "Periph/PinOut.h"
#include "Util/Threaded.h"
#include "RobotDriver.h"
#include <atomic>

namespace RoboCtrl {

class RoboCounter {
public:
	RoboCounter(const PinOut& clockPin, const PinOut& resetPin, const RobotDriver& driver);
	void tick();
	void reset();
	void startRunning(uint32_t tickTime);
	void stopRunning();
	void setSpeed(uint32_t tickTime);

private:
	const RobotDriver& driver;
	PinOut clockPin;
	PinOut resetPin;

	std::atomic_uint32_t tickTime;
	ThreadedClosure thread;
	void threadFunc();
	std::mutex pulseMutex;
};
}

#endif //BIT_FIRMWARE_ROBOCOUNTER_H
