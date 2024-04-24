#include "world.h"
#include "camera.h"
#include "game/game.h"



//IMPLEMENTAR GO TO STAGES

World::World()
{
	int window_width = Game::instance->window_width;
	int window_height = Game::instance->window_height;

	camera = new Camera();

	camera->lookAt(Vector3(0.f, 100.f, 100.f), Vector3(0.f, 0.f, 0.f), Vector3(0.f, 1.f, 0.f)); //position the camera and point to 0,0,0
	camera->setPerspective(70.f, window_width / (float)window_height, 0.1f, 10000.f); //set the projection, we want to be perspective


	Mesh* spitfire_mesh = Mesh::Get("data/meshes");
	Material spitfire_material;
	//mat.diffuse = Texture::Get("ok");

	/*


	int iterations = 25;

	for (int x = -iterations; x < iterations; ++x) {
		for (int y = -iterations; y < iterations; ++y) {
			EntityMesh* spitfire = new EntityMesh(spitfire_mesh, spitfire_material);
			spitfire->model.setTranslation(x*5,y*5,0);
			root.addChild(spitfire);
		}
	}*/



}


void World::render() {

	camera->enable();




	// Render all scene tree
	root.render(camera);


}


void World::update(float seconds_elapsed) {



	if (free_camera) //de les fotos 
	{
		float speed = seconds_elapsed * camera_speed;

		camera_pitch = clamp(camera_yaw);

		root.update(seconds_elapsed);

		//player update etc
	}


	for (auto e : entities_to_destroy) {
		root.removeChild(e);
		delete e;
	}
	entities_to_destroy.clear();

}

