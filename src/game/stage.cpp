#include "stage.h"
#include "framework/entities/entityPlayer.h"

//----- MENU STAGE -----
MenuStage::MenuStage()
{
	int width = Game::instance->window_width;
	int height = Game::instance->window_height;

	Material background_mat;
	background_mat.diffuse = Texture::Get("data/Icons/background.png");
	background = new EntityUI(Vector2(width * 0.5, height * 0.5), Vector2(width, height), background_mat);

	Material play_mat;
	play_mat.diffuse = Texture::Get("data/hud/start_button2.png");
	play_button = new EntityUI(Vector2(width * 0.5, 350), Vector2(200,75), play_mat, eButtonId::PlayButton);
	play_button->hover_texture = Texture::Get("data/hud/start_button.png");


	Material exit_mat;
	exit_mat.diffuse = Texture::Get("data/hud/exit_button2.png");
	exit_button = new EntityUI(Vector2(width * 0.5, 450), Vector2(200, 75), exit_mat, eButtonId::ExitButton);
	exit_button->hover_texture = Texture::Get("data/hud/exit_button.png");


	//Material exit_mat;
	//exit_mat.diffuse = Texture::Get("data");
	//exit_button = new EntityUI(Vector2(width * 0.5, 400), Vector2(240, 60), exit_mat, eButtonId::ExitButton);

	background->addChild(play_button);
	background->addChild(exit_button);

	background_channel = Audio::Play("data/sounds/intro_audio.wav", 0.2f, BASS_SAMPLE_LOOP);
}


void MenuStage::update(float seconds_elapsed) {
	background->update(seconds_elapsed);
	play_button->update(seconds_elapsed);
	exit_button->update(seconds_elapsed);
}

void MenuStage::onEnterStage()
{
	
}

void MenuStage::render() {
	Camera* camera2D = World::get_instance()->camera2D;

	background->render(camera2D);
	play_button->render(camera2D);
	exit_button->render(camera2D);


	
	if (Input::wasKeyPressed(SDL_SCANCODE_1)) {
		Game::instance->goToStage(WIN_STAGE);
	}
	if (Input::wasKeyPressed(SDL_SCANCODE_2)) {
		Game::instance->goToStage(GAME_OVER);

	}
}

void MenuStage::onButtonPressed(eButtonId buttonId)
{
	switch (buttonId) {
	case PlayButton:
		Game::instance->goToStage(PLAY_STAGE);
		break;
	case ExitButton:
		exit(0);
		break;
	}
}

void MenuStage::onExitStage()
{
	Audio::Stop(background_channel);
}


//----- PLAY STAGE -----
PlayStage::PlayStage() {
	int width = Game::instance->window_width;
	int height = Game::instance->window_height;


	// ---- Square and Surprise Objects ----
	Material square_material;
	square_material.diffuse = Texture::Get("data/hud/cuadrado.png");
	square = new EntityUI(Vector2(50, 45), Vector2(75, 75), square_material);

	Material thunder_material;
	thunder_material.diffuse = Texture::Get("data/Icons/thunder.png");
	thunder = new EntityUI(Vector2(50, 45), Vector2(50, 50), thunder_material);

	Material bullet_material;
	bullet_material.diffuse = Texture::Get("data/Icons/fireball.png");
	bullet = new EntityUI(Vector2(50, 45), Vector2(50, 50), bullet_material);

	Material heart_material;
	heart_material.diffuse = Texture::Get("data/Icons/fullheart.png");
	heart = new EntityUI(Vector2(50, 45), Vector2(50, 50), heart_material);

	Material cube_mat;
	cube_mat.diffuse = Texture::Get("data/Icons/fake_cube.png");
	fake_cube = new EntityUI(Vector2(50, 45), Vector2(50, 50), cube_mat);


	// ---- Lifes, Turbo and Fireballs ----
	Material life0_mat;
	life0_mat.diffuse = Texture::Get("data/hud/lives0.png");
	life0 = new EntityUI(Vector2(width * 0.5, 50), Vector2(175, 50), life0_mat);

	Material life1_mat;
	life1_mat.diffuse = Texture::Get("data/hud/lives1.png");
	life1 = new EntityUI(Vector2(width * 0.5, 50), Vector2(175, 50), life1_mat);

	Material life2_mat;
	life2_mat.diffuse = Texture::Get("data/hud/lives2.png");
	life2 = new EntityUI(Vector2(width * 0.5, 50), Vector2(175, 50), life2_mat);

	Material life3_mat;
	life3_mat.diffuse = Texture::Get("data/hud/lives3.png");
	life3 = new EntityUI(Vector2(width * 0.5, 50), Vector2(175, 50), life3_mat);

	Material boost_mat;
	boost_mat.shader = Shader::Get("data/shaders/basic.vs", "data/shaders/boost.fs");
	boost = new EntityUI(Vector2(760, 470), Vector2(20, 200), boost_mat);

	Material fireball_mat;
	fireball_mat.diffuse = Texture::Get("data/Icons/fireball.png");
	fireball = new EntityUI(Vector2(700, 40), Vector2(75, 75), fireball_mat);


}


void PlayStage::render()	
{

	Camera* camera2D = World::get_instance()->camera2D;
	EntityPlayer* player = World::get_instance()->root_player;

	World::get_instance()->render();


	switch (player->total_lives) {
		case 3:
			life3->render(camera2D);
			break;
		case 2:
			life2->render(camera2D);
			break;
		case 1:
			life1->render(camera2D);
			break;
		case 0:
			life0->render(camera2D);
			break;
	}

	boost->render(camera2D);

	fireball->render(camera2D);



	// --- Suprise Objects render ---
	square->render(camera2D);

	if (player->object_collected == "turbo") {
		thunder->render(camera2D);
	}
	else if (player->object_collected == "life") {
		heart->render(camera2D);

	}
	else if (player->object_collected == "bullet") {
		bullet->render(camera2D);

	}
	else if (player->object_collected == "obstacle") {
		fake_cube->render(camera2D);
	}




	if (player->position.y < 68.0f) Game::instance->goToStage(WIN_STAGE);

}

void PlayStage::update(float seconds_elapsed) {

	World::instance->update(seconds_elapsed);
	life3->update(seconds_elapsed);
	boost->update(seconds_elapsed);
	square->update(seconds_elapsed);
}

void PlayStage::onEnterStage() {
	sound = Audio::Play("data/sounds/mainScene.mp3", 0.1f, BASS_MUSIC_LOOP | BASS_MUSIC_MONO);
	//World::instance->root_player->handle_channel = Audio::Play("data/sounds/handle.wav", 1.f, BASS_MUSIC_LOOP);
}



void PlayStage::onExitStage() {
	Audio::Stop(sound);

	EntityPlayer* player = World::instance->root_player;

	Audio::Stop(player->turbo_channel);
	Audio::Stop(player->handle_channel);
	Audio::Stop(player->move_channel);


}

//----- WIN STAGE -----
WinStage::WinStage()
{
	int width = Game::instance->window_width;
	int height = Game::instance->window_height;

	Material background_mat;
	background_mat.diffuse = Texture::Get("data/hud/win.png");
	background = new EntityUI(Vector2(width * 0.5, height * 0.5), Vector2(width, height), background_mat);

	Material play_mat;
	play_mat.diffuse = Texture::Get("data/hud/restart_button2.png");
	play_button = new EntityUI(Vector2(280, 350), Vector2(200, 75), play_mat, eButtonId::RestartButton);
	play_button->hover_texture = Texture::Get("data/hud/restart_button.png");


	Material exit_mat;
	exit_mat.diffuse = Texture::Get("data/hud/exit_button2.png");
	exit_button = new EntityUI(Vector2(280, 450), Vector2(200, 75), exit_mat, eButtonId::ExitButton);
	exit_button->hover_texture = Texture::Get("data/hud/exit_button.png");

	background->addChild(play_button);
	background->addChild(exit_button);



}

void WinStage::render()
{
	Camera* camera2D = World::get_instance()->camera2D;

	background->render(camera2D);
}

void WinStage::update(float seconds_elapsed) {
	background->update(seconds_elapsed);
	play_button->update(seconds_elapsed);
	exit_button->update(seconds_elapsed);
}

void WinStage::onEnterStage()
{
	winBackground = Audio::Play("data/sounds/WinStage.wav", 0.3f, BASS_MUSIC_LOOP);
}

void WinStage::onExitStage() {
	Audio::Stop(winBackground);
}



//----- GAME OVER STAGE -----
GameOverStage::GameOverStage()
{
	int width = Game::instance->window_width;
	int height = Game::instance->window_height;

	Material background_mat;
	background_mat.diffuse = Texture::Get("data/hud/game_over2.png");
	background = new EntityUI(Vector2(width * 0.5, height * 0.5), Vector2(width, height), background_mat);
	
	Material play_mat;
	play_mat.diffuse = Texture::Get("data/hud/restart_button2.png");
	play_button = new EntityUI(Vector2(200, 350), Vector2(200, 75), play_mat, eButtonId::RestartButton);
	play_button->hover_texture = Texture::Get("data/hud/restart_button.png");


	Material exit_mat;
	exit_mat.diffuse = Texture::Get("data/hud/exit_button2.png");
	exit_button = new EntityUI(Vector2(200, 450), Vector2(200, 75), exit_mat, eButtonId::ExitButton);
	exit_button->hover_texture = Texture::Get("data/hud/exit_button.png");

	background->addChild(play_button);
	background->addChild(exit_button);
}

void GameOverStage::render()
{
	Camera* camera2D = World::get_instance()->camera2D;

	background->render(camera2D);

}

void GameOverStage::update(float seconds_elapsed) {
	background->update(seconds_elapsed);
	play_button->update(seconds_elapsed);
	exit_button->update(seconds_elapsed);

}


void GameOverStage::onEnterStage() {
	loseBackground = Audio::Play("data/sounds/GameOver.mp3", 0.2f, BASS_MUSIC_MONO);
}

void GameOverStage::onExitStage() {
	Audio::Stop(loseBackground);
}
