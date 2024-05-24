#pragma once
#include "framework/includes.h"
#include "framework/utils.h"
#include "framework/input.h"
#include "world.h"
#include "game.h"

class Camera;


enum eStages {

	MENU,
	PLAY,
	STAGES_SIZE
};



class Stage {

	eStages type = MENU;

public:


	Stage() {};
	virtual void render() {};
	virtual void update(float seconds_elapsed) {};
	virtual void onEnterStage() {};
	virtual void onExitStage() {};

};

class MenuStage: public Stage {

	eStages type = MENU;



};

class PlayStage : public Stage {

	eStages type = PLAY;

	PlayStage() {};
	virtual void render() {};
	virtual void update(float seconds_elapsed) {};
	virtual void onEnterStage() {};
	virtual void onExitStage() {};
};