#ifndef BIT_FIRMWARE_ROBOTDRIVER_H
#define BIT_FIRMWARE_ROBOTDRIVER_H

#include "Services/Robots.h"

namespace RoboCtrl {

class RobotDriver {
public:
	RobotDriver(Robot type);

	/**
	 * Checks with Robots service whether the robot is inserted
	 * This needs to be checked before any robot HW control!
	 * @return True - robot is inserted, False - robot isn't inserted
	 */
	bool checkRobot() const;

	/**
	 * Called when robot is plugged in.
	 */
	virtual void hello() = 0;

private:
	const Robot type;
};

}


#endif //BIT_FIRMWARE_ROBOTDRIVER_H
