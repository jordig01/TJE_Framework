#include "stage.h"


//----- MENU STAGE -----
MenuStage::MenuStage()
{
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
