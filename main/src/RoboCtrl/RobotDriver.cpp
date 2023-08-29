#include "RobotDriver.h"
#include "Util/Services.h"

RoboCtrl::RobotDriver::RobotDriver(Robot type) : type(type){
}

bool RoboCtrl::RobotDriver::checkRobot() const{
	return ((Robots*) Services.get(Service::Robots))->getInserted() == type;
}
