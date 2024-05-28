#include "stage.h"

//----- MENU STAGE -----
MenuStage::MenuStage()
{
	int width = Game::instance->window_width;
	int height = Game::instance->window_height;

	Material background_mat;
	background_mat.diffuse = Texture::Get("data");
	background = new EntityUI(Vector2(width * 0.5, height * 0.5), Vector2(width, height), background_mat);

	Material play_mat;
	play_mat.diffuse = Texture::Get("data");
	play_button = new EntityUI(Vector2(width * 0.5, 400), Vector2(240,60), play_mat, eButtonId::PlayButton);


	Material exit_mat;
	exit_mat.diffuse = Texture::Get("data");
	exit_button = new EntityUI(Vector2(width * 0.5, 400), Vector2(240, 60), exit_mat, eButtonId::ExitButton);

	background->addChild(play_button);
	background->addChild(exit_button);

}


void MenuStage::update(float seconds_elapsed) {
	background->update(seconds_elapsed);
}

void MenuStage::render() {
	Camera* camera2D = World::get_instance()->camera2D;
	background->render(camera2D);
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

}


void PlayStage::render()
{
	World::get_instance()->render();
}

void PlayStage::update(float seconds_elapsed) {

	World::get_instance()->update(seconds_elapsed);
}




//----- GAME OVER STAGE -----
GameOverStage::GameOverStage()
{
}
