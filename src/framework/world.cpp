#include "world.h"
#include "camera.h"
#include "game/game.h"

World::World()
{
	int window_width = Game::instance->window_width;
	int window_height = Game::instance->window_height;

	camera = new Camera();

	camera->lookAt(Vector3(0.f, 100.f, 100.f), Vector3(0.f, 0.f, 0.f), Vector3(0.f, 1.f, 0.f)); //position the camera and point to 0,0,0
	camera->setPerspective(70.f, window_width / (float)window_height, 0.1f, 10000.f); //set the projection, we want to be perspective




}


void World::render() {

	camera->enable();

}

