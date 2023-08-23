#include "UIThread.h"
#include "Util/stdafx.h"
#include "GameEngine/Game.h"
#include "Devices/Display.h"
#include "Screens/PauseScreen.h"
#include "LV_Interface/FSLVGL.h"

UIThread::UIThread(LVGL& lvgl, GameRunner& gameRunner) : Threaded("UI", 4 * 1024, 5, 0), lvgl(lvgl), gamer(gameRunner){
	start();
}

UIThread::~UIThread(){
	stop();
}

void UIThread::loop(){
	if(active == Src::LVGL){
		lvgl.loop();
	}else if(active == Src::Game){
		gamer.loop();
	}else{
		delayMillis(100);
		return;
	}
}

void UIThread::startGame(Games game){
	lvgl.stopScreen();
	FSLVGL::unloadCache();
	gamer.startGame(game);
	active = Src::Game;
}

void UIThread::startScreen(std::function<std::unique_ptr<LVScreen>()> create){
	gamer.endGame();
	FSLVGL::loadCache();
	lvgl.startScreen(std::move(create));
	active = Src::LVGL;
}

void UIThread::pauseGame(){
	lvgl.startScreen([this](){ return std::make_unique<PauseScreen>(gamer.getCurrent()); });
	active = Src::LVGL;
}

void UIThread::resumeGame(){
	lvgl.stopScreen();
	gamer.resume();
	active = Src::Game;
}
