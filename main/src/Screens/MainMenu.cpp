#include "MainMenu.h"
#include "MenuItem.h"
#include "LV_Interface/FSLVGL.h"
#include "LV_Interface/LVGIF.h"
#include "Util/stdafx.h"

struct Entry {
	const char* icon;
};

static constexpr Entry MenuEntries[] = {
		{ .icon = "S:/GameIcons/Blocks.bin" },
		{ .icon = "S:/GameIcons/Pong.bin" },
		{ .icon = "S:/GameIcons/Snake.bin" },
		{ .icon = "S:/GameIcons/Arte.bin" },
		{ .icon = "S:/GameIcons/Bee.bin" },
		{ .icon = "S:/GameIcons/Bob.bin" },
		{ .icon = "S:/GameIcons/Butt.bin" },
		{ .icon = "S:/GameIcons/Capa.bin" },
		{ .icon = "S:/GameIcons/Hertz.bin" },
		{ .icon = "S:/GameIcons/Marv.bin" },
		{ .icon = "S:/GameIcons/Resis.bin" },
		{ .icon = "S:/GameIcons/Robby.bin" }
};

MainMenu::MainMenu(){
	loadCache();
	buildUI();
}

MainMenu::~MainMenu(){
	unloadCache();
}

void MainMenu::buildUI(){
	lv_obj_set_size(*this, 128, 128);
	lv_obj_add_flag(*this, LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_scrollbar_mode(*this, LV_SCROLLBAR_MODE_OFF);

	auto bg = new LVGIF(*this, "S:/bg");
	lv_obj_add_flag(*bg, LV_OBJ_FLAG_FLOATING);
	lv_obj_set_pos(*bg, 0, 0);
	bg->start();

	auto container = lv_obj_create(*this);
	lv_obj_set_flex_flow(container, LV_FLEX_FLOW_ROW_WRAP);
	lv_obj_set_flex_align(container, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
	lv_obj_set_style_pad_gap(container, 6, 0);
	lv_obj_set_style_pad_hor(container, 19, 0);
	lv_obj_set_style_pad_ver(container, 13, 0);

	items.reserve(sizeof(MenuEntries) / sizeof(MenuEntries[0]));
	for(const auto& entry : MenuEntries){
		auto item = new MenuItem(container, entry.icon);
		lv_obj_add_flag(*item, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
		lv_group_add_obj(inputGroup, *item);
		items.push_back(item);
	}

	lv_group_focus_obj(*items.front());
	lv_obj_scroll_to(*this, 0, 0, LV_ANIM_OFF);
}

void MainMenu::loadCache(){
	auto time = millis();

	for(const auto& img : BgImgs){
		FSLVGL::addToCache(img);
	}

	for(const auto& entry : MenuEntries){
		std::string path(entry.icon + 2);
		FSLVGL::addToCache(path.c_str());
	}

	printf("Load time: %llu ms\n", millis() - time);
}

void MainMenu::unloadCache(){
	for(const auto& entry : MenuEntries){
		std::string path(entry.icon + 2);
		FSLVGL::removeFromCache(path.c_str());
	}

	for(const auto& img : BgImgs){
		FSLVGL::removeFromCache(img);
	}
}
