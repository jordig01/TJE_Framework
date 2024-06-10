#include "game.h"
#include "framework/utils.h"
#include "graphics/mesh.h"
#include "graphics/texture.h"
#include "graphics/fbo.h"
#include "graphics/shader.h"
#include "framework/input.h"
#include "framework/entities/entityPlayer.h"

#include <cmath>

#include "stage.h"

//some globals
Mesh* mesh = NULL;
Texture* texture = NULL;
Shader* shader = NULL;
float angle = 0;
float mouse_speed = 100.0f;

Game* Game::instance = NULL;

Stage* current_stage;
Stage* stages[STAGES_SIZE];


Game::Game(int window_width, int window_height, SDL_Window* window)
{
	this->window_width = window_width;
	this->window_height = window_height;
	this->window = window;
	instance = this;
	must_exit = false;

	fps = 0;
	frame = 0;
	time = 0.0f;
	elapsed_time = 0.0f;
	mouse_locked = false;

	// OpenGL flags
	glEnable( GL_CULL_FACE ); //render both sides of every triangle
	glEnable( GL_DEPTH_TEST ); //check the occlusions using the Z buffer
	

	//// Hide the cursor
	SDL_ShowCursor(!mouse_locked); //hide or show the mouse

	//world = new World();

	stages[MENU] = new MenuStage();
	stages[TUTORIAL_STAGE] = new TutorialStage();
	stages[PLAY_STAGE] = new PlayStage();
	stages[WIN_STAGE] = new WinStage();
	stages[GAME_OVER] = new GameOverStage();

	current_stage = stages[MENU];

}



// ---- TO MANAGE THE CHANGE OF STAGES ----
void Game::goToStage(int new_stage) {

	if (current_stage) {
		current_stage->onExitStage();
	}

	current_stage = stages[new_stage];
	current_stage->onEnterStage();


}

void Game::restart()
{

	World* world = World::get_instance();
	EntityPlayer * player = World::instance->root_player;
	player->total_lives = 3;
	player->total_points = 0;
	player->bullet_count = 5;
	player->turbo = 1000.f;
	player->object_collected = "";
	player->total_points = 0;

	//World::instance->renderCubeWaypoint();
	//World::instance->instantiateEnemies();
	player->model.setTranslation((World::instance->old_position_player));

	goToStage(PLAY_STAGE);
}



//what to do when the image has to be draw
void Game::render(void)
{


	// Set the clear color (the background color)
	glClearColor(0.0, 0.0, 0.0, 1.0);


	// Clear the window and the depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	
	//render of the world

	current_stage->render();

	//StageManager::get_instance()->render();

	// Swap between front buffer and back buffer 
	SDL_GL_SwapWindow(this->window);
}

void Game::update(double seconds_elapsed)
{

	//world->update(seconds_elapsed);
	current_stage->update(seconds_elapsed);
}

//Keyboard event handler (sync input)
void Game::onKeyDown( SDL_KeyboardEvent event )
{
	switch(event.keysym.sym)
	{
		case SDLK_ESCAPE: must_exit = true; break; //ESC key, kill the app
		case SDLK_F1: Shader::ReloadAll(); break; 
	}
}

void Game::onKeyUp(SDL_KeyboardEvent event)
{

}

void Game::onMouseButtonDown( SDL_MouseButtonEvent event )
{
	if (event.button == SDL_BUTTON_MIDDLE) //middle mouse
	{
		mouse_locked = !mouse_locked;
		SDL_ShowCursor(!mouse_locked);
		SDL_SetRelativeMouseMode((SDL_bool)(mouse_locked));
	}
}

void Game::onMouseButtonUp(SDL_MouseButtonEvent event)
{

}

void Game::onMouseWheel(SDL_MouseWheelEvent event)
{
	mouse_speed *= event.y > 0 ? 1.1f : 0.9f;
}

void Game::onGamepadButtonDown(SDL_JoyButtonEvent event)
{

}

void Game::onGamepadButtonUp(SDL_JoyButtonEvent event)
{

}

void Game::onResize(int width, int height)
{
    std::cout << "window resized: " << width << "," << height << std::endl;
	glViewport( 0,0, width, height );
	window_width = width;
	window_height = height;

	World::get_instance()->camera->aspect = width / (float)height;
	World::get_instance()->camera->setPerspective(70.f, window_width / (float)window_height, 0.1f, 10000.f);
	World::get_instance()->camera2D->setOrthographic(0, window_width, window_height, 0, -1.f, 1.f);
	//for (Stage* s : stages) s->reload();
}


