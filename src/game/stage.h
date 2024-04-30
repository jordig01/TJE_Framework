#pragma once
#include "framework/includes.h"
#include "framework/utils.h"
#include "framework/input.h"
#include "world.h"
#include "game.h"

class Camera;


enum eStages {

	MENU,
	INTRO,
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

class MenuStage {

	eStages type = MENU;



};