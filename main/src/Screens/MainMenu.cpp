#include "MainMenu.h"
#include "MenuItem.h"
#include "LV_Interface/FSLVGL.h"
#include "Services/GameManager.h"
#include "Util/Services.h"
#include "Util/stdafx.h"

struct Entry {
	const char* icon;
	Robot rob = Robot::COUNT;
};

static constexpr Entry MenuEntries[] = {
		{ .icon = "Blocks" },
		{ .icon = "Pong" },
		{ .icon = "Snake" },
		{ .icon = "Arte", .rob = Artemis },
		{ .icon = "Bee", .rob = MrBee },
		{ .icon = "Bob", .rob = Bob },
		{ .icon = "Butt", .rob = Buttons },
		{ .icon = "Capa", .rob = Capacitron },
		{ .icon = "Hertz", .rob = Hertz },
		{ .icon = "Marv", .rob = Marv },
		{ .icon = "Resis", .rob = Resistron },
		{ .icon = "Robby", .rob = Robby }
};

// Ordered by adress
static constexpr const char* RobotIcons[] = {
		"Bee",
		"Resis",
		"Arte",
		"Robby",
		"Marv",
		"Capa",
		"Bob",
		"Butt",
		"Hertz"
};

MainMenu::MainMenu() : events(12){
	loadCache();
	Events::listen(Facility::Games, &events);
	buildUI();
}

MainMenu::~MainMenu(){
	Events::unlisten(&events);
	unloadCache();
}

void MainMenu::onStarting(){
	const auto height = lv_obj_get_height(itemCont) + 128 + 2*13;
	lv_obj_scroll_to(*this, 0, 0, LV_ANIM_OFF); // set y to <height> to scroll from top. 0 to scroll from bottom
}

void MainMenu::onStart(){
	bg->start();
	lv_obj_scroll_to(*this, 0, 128, LV_ANIM_ON);
}

void MainMenu::onStop(){
	bg->stop();
}

void MainMenu::loop(){
	Event evt{};
	if(events.get(evt, 0)){
		auto data = (GameManager::Event*) evt.data;
		auto rob = data->rob;

		// TODO: show inserted popup
		// TODO: show unlock popup if new
		if(data->isNew && robGames.count(rob)){
			MenuItem* item = robGames.at(rob);
			const auto icon = RobotIcons[rob];
			const auto path = imgUnl(icon);
			item->setIcon(path.c_str());
		}

		free(evt.data);
	}
}

void MainMenu::buildUI(){
	lv_obj_set_size(*this, 128, 128);
	lv_obj_add_flag(*this, LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_scroll_dir(*this, LV_DIR_VER);
	lv_obj_set_scrollbar_mode(*this, LV_SCROLLBAR_MODE_OFF);

	bg = new LVGIF(*this, "S:/bg");
	lv_obj_add_flag(*bg, LV_OBJ_FLAG_FLOATING);
	lv_obj_set_pos(*bg, 0, 0);
	bg->start();

	padTop = lv_obj_create(*this);
	lv_obj_set_size(padTop, 128, 128);

	auto contentContainer = lv_obj_create(*this);
	lv_obj_set_size(contentContainer, 128, 128);
	lv_obj_set_pos(contentContainer, 0, 0);
	lv_obj_add_flag(contentContainer, LV_OBJ_FLAG_OVERFLOW_VISIBLE);
	lv_obj_set_style_pad_ver(contentContainer, 13, 0);

	itemCont = lv_obj_create(contentContainer);
	lv_obj_set_size(itemCont, 128, LV_SIZE_CONTENT);
	lv_obj_set_flex_flow(itemCont, LV_FLEX_FLOW_ROW_WRAP);
	lv_obj_set_flex_align(itemCont, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
	lv_obj_set_style_pad_gap(itemCont, 6, 0);
	lv_obj_set_style_pad_hor(itemCont, 19, 0);

	auto games = (GameManager*) Services.get(Service::Games);
	items.reserve(sizeof(MenuEntries) / sizeof(MenuEntries[0]));
	for(const auto& entry : MenuEntries){
		std::string path;
		if(entry.rob == COUNT || games->isUnlocked(entry.rob)){
			path = imgUnl(entry.icon);
		}else{
			path = imgLoc(entry.icon);
		}

		auto item = new MenuItem(itemCont, path.c_str());
		lv_obj_add_flag(*item, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
		lv_group_add_obj(inputGroup, *item);

		items.push_back(item);
		if(entry.rob != COUNT){
			robGames.insert(std::make_pair(entry.rob, item));
		}
	}

	lv_obj_refr_size(itemCont);
	lv_obj_refresh_self_size(itemCont);
	lv_group_focus_obj(*items.front());

	// Padding for intro scroll
	lv_obj_set_layout(*this, LV_LAYOUT_FLEX);
	lv_obj_set_flex_flow(*this, LV_FLEX_FLOW_COLUMN);

	auto padBot = lv_obj_create(*this);
	lv_obj_set_size(padBot, 128, lv_obj_get_height(itemCont));
}

void MainMenu::loadCache(){
	for(const auto& img : BgImgs){
		FSLVGL::addToCache(img);
	}

	// TODO: Only locked/unlocked icons for the games that are locked/unlocked
	// With this there is ~40kb free heap in MainMenu as of writing this
	for(const auto& entry : MenuEntries){
		auto lock = imgLoc(entry.icon); lock.erase(0, 2);
		auto unlock = imgUnl(entry.icon); unlock.erase(0, 2);
		FSLVGL::addToCache(lock.c_str());
		FSLVGL::addToCache(unlock.c_str());
	}
}

void MainMenu::unloadCache(){
	for(const auto& entry : MenuEntries){
		auto lock = imgLoc(entry.icon); lock.erase(0, 2);
		auto unlock = imgUnl(entry.icon); unlock.erase(0, 2);
		FSLVGL::removeFromCache(lock.c_str());
		FSLVGL::removeFromCache(unlock.c_str());
	}

	for(const auto& img : BgImgs){
		FSLVGL::removeFromCache(img);
	}
}

std::string MainMenu::imgUnl(const char* game){
	std::string path("S:/GameIcons/");
	path.append(game);
	path.append(".bin");
	return path;
}

std::string MainMenu::imgLoc(const char* game){
	std::string path("S:/GameIcons/");
	path.append(game);
	path.append("L.bin");
	return path;
}
