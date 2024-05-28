#pragma once
#include "framework/includes.h"
#include "framework/utils.h"
#include "framework/input.h"
#include "framework/entities/entityUI.h"
#include "world.h"
#include "game.h"


class Camera;


enum eStages {

	MENU,
	PLAY_STAGE,
	GAME_OVER,
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


	virtual void onButtonPressed(eButtonId buttonId) {};

};

//Implementar con el HUD
class MenuStage: public Stage {

	eStages type = MENU;

public:
	MenuStage();

	EntityUI* background = nullptr;
	EntityUI* play_button = nullptr;
	EntityUI* exit_button = nullptr;

	void render();
	void update(float seconds_elapsed);
	void onEnterStage() {};
	void onExitStage() {};
	void onButtonPressed(eButtonId buttonId);

};

class PlayStage : public Stage {

	eStages type = PLAY_STAGE;

public:
	PlayStage();
	void render() override;
	void update(float seconds_elapsed) override;
	void onEnterStage() {};
	void onExitStage() {};

};



//Implementar con el HUD
class GameOverStage : public Stage {

	eStages type = GAME_OVER;

public:
	GameOverStage();
	void render() {};
	void update(float seconds_elapsed) {};
	void onEnterStage() {};
	void onExitStage() {};
};