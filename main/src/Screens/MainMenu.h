#ifndef BIT_FIRMWARE_MAINMENU_H
#define BIT_FIRMWARE_MAINMENU_H

#include "LV_Interface/LVScreen.h"
#include "MenuItem.h"
#include "LV_Interface/LVGIF.h"

class MainMenu : public LVScreen {
public:
	MainMenu();
	virtual ~MainMenu();

	static void loadCache();

private:
	void buildUI();

	std::vector<MenuItem*> items;
	lv_obj_t* itemCont;
	LVGIF* bg;
	lv_obj_t* padTop = nullptr;

	void onStarting() override;
	void onStart() override;
	void onStop() override;

	static constexpr const char* BgImgs[] = { "/bg/0.bin", "/bg/1.bin", "/bg/2.bin", "/bg/3.bin", };
	static void unloadCache();

};


#endif //BIT_FIRMWARE_MAINMENU_H
