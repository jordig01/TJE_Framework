#pragma once
#include "includes.h"
#include "image.h"
#include "utils.h"
#include "synth.h"
#include "input.h"
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
	virtual void onExitStage() {}:

};