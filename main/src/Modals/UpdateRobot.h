#ifndef BIT_FIRMWARE_UPDATEROBOT_H
#define BIT_FIRMWARE_UPDATEROBOT_H

#include "LV_Interface/LVModal.h"
#include "LV_Interface/LVStyle.h"

class UpdateRobot : public LVModal {
public:
	UpdateRobot(LVScreen* parent);

private:

	void buildUI();

	LVStyle labelStyle;

};


#endif //BIT_FIRMWARE_UPDATEROBOT_H
