#include "world.h"
#include "framework/camera.h"
#include "game/game.h"
#include "graphics/texture.h"
#include <framework/input.h>
#include <fstream>




World::World()
{
	int window_width = Game::instance->window_width;
	int window_height = Game::instance->window_height;

	camera = new Camera();

	camera->lookAt(Vector3(0.f, 100.f, 100.f), Vector3(0.f, 0.f, 0.f), Vector3(0.f, 1.f, 0.f)); //position the camera and point to 0,0,0
	camera->setPerspective(70.f, window_width / (float)window_height, 0.1f, 10000.f); //set the projection, we want to be perspective


	Mesh* spitfire_mesh = Mesh::Get("data/meshes/spitfire.ASE");
	Material spitfire_mat;
	spitfire_mat.diffuse = Texture::Get("data/meshes/spitfire_color_spec.tga");

	EntityMesh* spitfire = new EntityMesh(spitfire_mesh, spitfire_mat);

	spitfire->model.setTranslation(0.f, 10.f, 0.f);

	spitfire->addLOD({ Mesh::Get("data/meshes/spitfire_low.ASE"),10.0f });



	//spitfire->addInstance((5, 0, 0)); // Ejemplo de otra instancia en la posición (5, 0, 0)



	/*int iterations = 25;

	for (int x = -iterations; x < iterations; ++x) {
		for (int y = -iterations; y < iterations; ++y) {
			EntityMesh* spitfire = new EntityMesh(spitfire_mesh, spitfire_mat);
			spitfire->model.setTranslation(x*5,y*5,0);
			root.addChild(spitfire);
		}
	}*/

	root.addChild(spitfire);


	parseScene("data/scene/myscene.scene", &root);

}


void World::render() {

	// Set the clear color (the background color)
	glClearColor(0.0, 0.0, 0.0, 1.0);

	// Clear the window and the depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Set the camera as default
	camera->enable();

	//// Set flags
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	//// Create model matrix for cube
	//Matrix44 m;
	//m.rotate(angle * DEG2RAD, Vector3(0.0f, 1.0f, 0.0f));


	drawGrid();
	root.render(camera);


	// Render the FPS, Draw Calls, etc
	drawText(2, 2, getGPUStats(), Vector3(1, 1, 1), 2);


}


void World::update(float seconds_elapsed) {



	if (free_camera)
	{
		float speed = seconds_elapsed * camera_speed;

		camera_pitch = clamp(camera_yaw);

		root.update(seconds_elapsed);

	}
	else {
		camera_yaw -= Input::mouse_delta.x * 0.001;
		camera_pitch -= Input::mouse_delta.y * 0.001;
		camera_pitch = clamp(camera_pitch, -M_PI * 0.4f, M_PI* 0.4f);
		
		Matrix44 mYaw;

		mYaw.setRotation(camera_yaw, Vector3(0, 1, 0));

		Matrix44 mPitch;
		mPitch.setRotation(camera_yaw, Vector3(-1, 0, 0));

		Vector3 front = (mPitch * mYaw).frontVector().normalize();
		Vector3 eye;
		Vector3 center;

		float orbit_dist = 0.6f;

		/*eye = player->model.getTranslation() - front * orbit_dist;

		center = player->model.getTranslation() + Vector3(0.0f, 0.1f, 0.0f);

		camera->lookAt(eye, center, Vector3(0, 1, 0));
		root.update(seconds_elapsed);*/

	}


	for (auto e : entities_to_destroy) {
		root.removeChild(e);
		delete e;
	}
	entities_to_destroy.clear();

}

bool World::parseScene(const char* filename, Entity* root)
{
	std::cout << " + Scene loading: " << filename << "..." << std::endl;

	std::ifstream file(filename);

	if (!file.good()) {
		std::cerr << "Scene [ERROR]" << " File not found!" << std::endl;
		return false;
	}

	std::map<std::string, sRenderData> meshes_to_load;

	std::string scene_info, mesh_name, model_data;
	file >> scene_info; file >> scene_info;
	int mesh_count = 0;

	// Read file line by line and store mesh path and model info in separated variables
	while (file >> mesh_name >> model_data)
	{
		if (mesh_name[0] == '#')
			continue;

		// Get all 16 matrix floats
		std::vector<std::string> tokens = tokenize(model_data, ",");

		// Fill matrix converting chars to floats
		Matrix44 model;
		for (int t = 0; t < tokens.size(); ++t) {
			model.m[t] = (float)atof(tokens[t].c_str());
		}

		// Add model to mesh list (might be instanced!)
		sRenderData& render_data = meshes_to_load[mesh_name];
		render_data.models.push_back(model);
		mesh_count++;
	}

	// Iterate through meshes loaded and create corresponding entities
	for (auto data : meshes_to_load) {

		mesh_name = "data/" + data.first;
		sRenderData& render_data = data.second;

		// No transforms, nothing to do here
		if (render_data.models.empty())
			continue;


		Material mat = render_data.material;
		EntityMesh* new_entity = nullptr;


		size_t tag = data.first.find("@tag");

		if (tag != std::string::npos) {
			Mesh* mesh = Mesh::Get("...");
			// Create a different type of entity
			// new_entity = new ...
		}
		else {
			Mesh* mesh = Mesh::Get(mesh_name.c_str());
			new_entity = new EntityMesh(mesh, mat);
		}

		if (!new_entity) {
			continue;
		}

		new_entity->name = data.first;

		// Create instanced entity
		if (render_data.models.size() > 1) {
			new_entity->isInstanced = true;
			new_entity->models = render_data.models; // Add all instances
		}
		// Create normal entity
		else {
			new_entity->model = render_data.models[0];
		}

		// Add entity to scene root
		root->addChild(new_entity);
	}

	std::cout << "Scene [OK]" << " Meshes added: " << mesh_count << std::endl;
	return true;
}

void World::addEntity(Entity* entity)
{

}

void World::removeEntity(Entity* entity)
{

}



//ENTITY MESH DEL CUBO Y EL MATERIAL il shader è diverso infatti dobbiammo crearci uno che si chiami cubemap.fs

//non mettorlo nel root  


//glDisable()
//flEnable()




