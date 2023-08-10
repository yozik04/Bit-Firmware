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

	items.reserve(sizeof(MenuEntries) / sizeof(MenuEntries[0]));
	for(const auto& entry : MenuEntries){
		auto item = new MenuItem(itemCont, entry.icon);
		lv_obj_add_flag(*item, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
		lv_group_add_obj(inputGroup, *item);
		items.push_back(item);
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
	auto time = millis();

	for(const auto& img : BgImgs){
		FSLVGL::addToCache(img);
	}

	for(const auto& entry : MenuEntries){
		std::string path(entry.icon + 2);
		FSLVGL::addToCache(path.c_str());
	}
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
