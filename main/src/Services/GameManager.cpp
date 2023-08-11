#include "GameManager.h"
#include "Settings/Settings.h"
#include "Util/Services.h"

GameManager::GameManager() : Threaded("GameMan", 2 * 1024), events(12){
	auto set = (Settings*) Services.get(Service::Settings);
	const auto all = set->get();
	for(int i = 0; i < Robot::COUNT; i++){
		if(all.robotsSeen[i]){
			unlocked.insert((Robot) i);
		}
	}

	Events::listen(Facility::Robots, &events);
	start();
}

bool GameManager::isUnlocked(Robot rob){
	return unlocked.count(rob);
}

void GameManager::storeState(){
	auto set = (Settings*) Services.get(Service::Settings);
	auto all = set->get();

	// Only unlocks, doesn't relock
	for(const Robot rob : unlocked){
		all.robotsSeen[rob] = 1;
	}

	set->set(all);
	set->store();
}

void GameManager::loop(){
	::Event evt;
	if(!events.get(evt, portMAX_DELAY)) return;

	auto data = (Robots::Event*) evt.data;
	if(data->action == Robots::Event::Insert){
		bool isNew = false;
		Robot rob = data->robot;
		if(!unlocked.count(rob)){
			isNew = true;
			unlocked.insert(rob);
			storeState();
		}

		Events::post(Facility::Games, Event { .action = Event::Inserted, .rob = rob, .isNew = isNew });
	}

	free(evt.data);
}
