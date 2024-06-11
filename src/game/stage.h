#pragma once
#include "framework/includes.h"
#include "framework/utils.h"
#include "framework/input.h"
#include "framework/entities/entityUI.h"
#include "world.h"
#include "game.h"
#include "framework/audio.h"


class Camera;


enum eStages {

	MENU,
	TUTORIAL_STAGE,
	PLAY_STAGE,
	GAME_OVER,
	WIN_STAGE,
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
	virtual void reload() {};

};

//Implementar con el HUD
class MenuStage: public Stage {

	eStages type = MENU;

public:
	MenuStage();


	//--- Audio Part ---
	HCHANNEL background_channel;


	EntityUI* background = nullptr;
	EntityUI* play_button = nullptr;
	EntityUI* exit_button = nullptr;
	

	void render();
	void update(float seconds_elapsed);
	void onEnterStage();
	void onExitStage();
	void onButtonPressed(eButtonId buttonId);
	void reload();

};

class TutorialStage : public Stage {

	eStages type = TUTORIAL_STAGE;

public:
	TutorialStage();


	//--- Audio Part ---
	HCHANNEL background_channel;


	EntityUI* background = nullptr;
	EntityUI* continue_button = nullptr;


	void render();
	void update(float seconds_elapsed);
	void onEnterStage();
	void onExitStage();
	void onButtonPressed(eButtonId buttonId);
	void reload();

};

class PlayStage : public Stage {

	eStages type = PLAY_STAGE;

	EntityUI* square = nullptr;
	EntityUI* controls = nullptr;

	//--- LIFES ---
	EntityUI* life0 = nullptr;
	EntityUI* life1 = nullptr;
	EntityUI* life2 = nullptr;
	EntityUI* life3 = nullptr;

	//--- BOOST ---
	EntityUI* boost = nullptr;

	//--- FIREBALLS ---
	EntityUI* fireball = nullptr;


	//--- COUNTDOWN ---
	EntityUI * countdown_num = nullptr;
	Material number_mat;

	float countdown_timer = 6.0f;
	bool countdown_finished = false;
	bool restart_countdown = false;
	bool initial_rotation = true;


	//--- FINISH ----
	EntityUI* finish = nullptr;
	bool finish_game = false;
	float timer = 3.0f;
	HCHANNEL start_channel;
	bool start_music = true;


	//--- SCORE ---
	EntityUI* score = nullptr;
	Material zero_mat;
	Material one_mat;
	Material two_mat;
	Material three_mat;
	Material four_mat;
	Material five_mat;
	Material six_mat;
	Material seven_mat;
	Material eight_mat;
	Material nine_mat;

	//--- OBJECT OF CUBE SURPRISE ---
	EntityUI* bullet = nullptr;
	EntityUI* thunder = nullptr;
	EntityUI* heart = nullptr;
	EntityUI* fake_cube = nullptr;


	HCHANNEL sound;


public:

	PlayStage();
	void render() override;
	void update(float seconds_elapsed) override;
	void onEnterStage();
	void onExitStage();
	void reload();

};

class WinStage : public Stage {

	eStages type = WIN_STAGE;

public:
	WinStage();

	EntityUI* background = nullptr;
	EntityUI* play_button = nullptr;
	EntityUI* exit_button = nullptr;

	//--- SCORE ---
	EntityUI* score = nullptr;
	Material zero_mat;
	Material one_mat;
	Material two_mat;
	Material three_mat;
	Material four_mat;
	Material five_mat;
	Material six_mat;
	Material seven_mat;
	Material eight_mat;
	Material nine_mat;

	HCHANNEL winBackground;


	void render();
	void update(float seconds_elapsed);
	void onEnterStage();
	void onExitStage();
	void reload();

};

//Implementar con el HUD
class GameOverStage : public Stage {

	eStages type = GAME_OVER;

public:

	HCHANNEL loseBackground;

	EntityUI* background = nullptr;
	EntityUI* play_button = nullptr;
	EntityUI* exit_button = nullptr;

	//--- SCORE ---
	EntityUI* score = nullptr;
	Material zero_mat;
	Material one_mat;
	Material two_mat;
	Material three_mat;
	Material four_mat;
	Material five_mat;
	Material six_mat;
	Material seven_mat;
	Material eight_mat;
	Material nine_mat;

	GameOverStage();
	void render();
	void update(float seconds_elapsed);
	void onEnterStage();
	void onExitStage();
	void reload();
};