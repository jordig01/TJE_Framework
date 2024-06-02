#include "stage.h"

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

}


void MenuStage::update(float seconds_elapsed) {
	background->update(seconds_elapsed);
	play_button->update(seconds_elapsed);
	exit_button->update(seconds_elapsed);
}

void MenuStage::render() {
	Camera* camera2D = World::get_instance()->camera2D;

	background->render(camera2D);


	
	if (Input::wasKeyPressed(SDL_SCANCODE_1)) {
		Game::instance->goToStage(PLAY_STAGE);
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


//----- PLAY STAGE -----
PlayStage::PlayStage() {
	int width = Game::instance->window_width;
	int height = Game::instance->window_height;

	Material life0_mat;
	life0_mat.diffuse = Texture::Get("data/hud/lives0.png");
	life0 = new EntityUI(Vector2(width * 0.5, 10), Vector2(100, 75), life0_mat);

	Material life1_mat;
	life1_mat.diffuse = Texture::Get("data/hud/lives1.png");
	life1 = new EntityUI(Vector2(width * 0.5, 10), Vector2(100, 75), life1_mat);

	Material life2_mat;
	life2_mat.diffuse = Texture::Get("data/hud/lives2.png");
	life2 = new EntityUI(Vector2(width * 0.5, 10), Vector2(100, 75), life2_mat);

	Material life3_mat;
	life3_mat.diffuse = Texture::Get("data/hud/lives3.png");
	life3 = new EntityUI(Vector2(width * 0.5, 50), Vector2(175, 50), life3_mat);

	Material boost_mat;
	boost_mat.shader = Shader::Get("data/shaders/basic.vs", "data/shaders/boost.fs");
	boost = new EntityUI(Vector2(760, 450), Vector2(20, 200), boost_mat);
}


void PlayStage::render()	
{

	Camera* camera2D = World::get_instance()->camera2D;
	EntityPlayer* player = World::get_instance()->root_player;

	World::get_instance()->render();
	life3->render(camera2D);
	boost->render(camera2D);

	//if (player->total_lives == 3) life3->render(camera2D);
	//if (player.total_lives == 2) life2->render(camera2D);
	//if (player.total_lives == 1) life1->render(camera2D);
	//if (player.total_lives == 0) life0->render(camera2D);
	//if (player.position.y < 68.0f) Game::instance->goToStage(WIN_STAGE);
}

void PlayStage::update(float seconds_elapsed) {

	World::get_instance()->update(seconds_elapsed);
	life3->update(seconds_elapsed);
	boost->update(seconds_elapsed);
}

//----- WIN STAGE -----
WinStage::WinStage()
{
	int width = Game::instance->window_width;
	int height = Game::instance->window_height;

	Material background_mat;
	background_mat.diffuse = Texture::Get("data/hud/win.png");
	background = new EntityUI(Vector2(width * 0.5, height * 0.5), Vector2(width, height), background_mat);
}

void WinStage::render()
{
	Camera* camera2D = World::get_instance()->camera2D;

	background->render(camera2D);
}

void WinStage::update(float seconds_elapsed) {
	background->update(seconds_elapsed);
}


//----- GAME OVER STAGE -----
GameOverStage::GameOverStage()
{
	int width = Game::instance->window_width;
	int height = Game::instance->window_height;

	Material background_mat;
	background_mat.diffuse = Texture::Get("data/hud/game_over2.png");
	background = new EntityUI(Vector2(width * 0.5, height * 0.5), Vector2(width, height), background_mat);
}

void GameOverStage::render()
{
	Camera* camera2D = World::get_instance()->camera2D;

	background->render(camera2D);
}

void GameOverStage::update(float seconds_elapsed) {
	background->update(seconds_elapsed);
}
