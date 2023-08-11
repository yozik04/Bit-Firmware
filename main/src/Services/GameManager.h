#ifndef BIT_FIRMWARE_GAMEMANAGER_H
#define BIT_FIRMWARE_GAMEMANAGER_H

#include "Services/Robots.h"
#include "Util/Threaded.h"
#include "Util/Events.h"
#include <unordered_set>

class GameManager : private Threaded {
public:
	GameManager();

	struct Event {
		enum { Inserted } action;
		Robot rob;
		bool isNew;
	};

	bool isUnlocked(Robot rob);

private:
	std::unordered_set<Robot> unlocked;

	void storeState();

	EventQueue events;
	void loop() override;

};


#endif //BIT_FIRMWARE_GAMEMANAGER_H
