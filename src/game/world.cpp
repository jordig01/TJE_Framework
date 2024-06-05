#include "world.h"
#include "framework/camera.h"
#include "game/game.h"
#include "graphics/texture.h"
#include "graphics/shader.h"
#include "framework/entities/entityPlayer.h"
#include "framework/entities/entityCollider.h"
#include "framework/entities/entityFireball.h"
#include <framework/input.h>
#include <fstream>

World* World::instance = nullptr; // Initialization of static member variable


World::World()
{
	int window_width = Game::instance->window_width;
	int window_height = Game::instance->window_height;

	camera = new Camera();

	camera->lookAt(Vector3(0.f, 100.f, 100.f), Vector3(0.f, 0.f, 0.f), Vector3(0.f, 1.f, 0.f)); //position the camera and point to 0,0,0
	camera->setPerspective(70.f, window_width / (float)window_height, 0.1f, 10000.f); //set the projection, we want to be perspective


	camera2D = new Camera();
	//camera2D->view_matrix.setIdentity();
	camera2D->setOrthographic(0, window_width, window_height, 0, -1.f, 1.f);


	Mesh* wheels_mesh = Mesh::Get("data/meshes/player/wheels.obj");
	Material wheels_mat;
	wheels_mat.diffuse = Texture::Get("data/meshes/player/F2_Item_Kart_Yoshi_Tire_S.png");
	root_player = new EntityPlayer(wheels_mesh, wheels_mat);
	

	Mesh* kart_mesh = Mesh::Get("data/meshes/player/kart.obj");
	Material kart_mat;
	kart_mat.diffuse = Texture::Get("data/meshes/player/F2_Item_Kart_Yoshi_Kart_S.png");
	EntityMesh* kart = new EntityMesh(kart_mesh, kart_mat);
	
	Mesh* character_mesh = Mesh::Get("data/meshes/player/character.obj");
	Material character_mat;
	character_mat.diffuse = Texture::Get("data/meshes/player/F2_Item_Kart_Yoshi_Body_S.png");
	EntityMesh* character = new EntityMesh(character_mesh, character_mat);

	root_player->addChild(kart);
	root_player->addChild(character);

	//player->isAnimated = true; //el body tendría que ser


	//root_player.shader

	//root_player->model.setTranslation(2955.f, 2550.f, 4690.f);

	/*EntityAI* enemy = new EntityAI(Mesh::Get("data/meshes/enemy.obj"), {});
	enemy->setLayer(eCollisionFilter::ENEMY);
	root.addChild(enemy);*/

	Material landscape;
	landscape.shader = Shader::Get("data/shaders/basic.vs", "data/shaders/cubemap.fs");
	landscape.diffuse = new Texture();

	landscape.diffuse->loadCubemap("landscape",  {
		"data/textures/skybox2/right.png",
		"data/textures/skybox2/left.png",
		"data/textures/skybox2/bottom.png",
		"data/textures/skybox2/top.png",
		"data/textures/skybox2/front.png",
		"data/textures/skybox2/back.png"
	});

	Mesh* cubemapMesh = Mesh::Get("data/meshes/cubemap.obj");

	skybox = new EntityMesh(cubemapMesh, landscape);

	parseScene("data/circuit_test2/circuitv2.scene", &root);//sample2.scene


	//channel = Audio::Play("data/audio/,  BASS_SAMPLE_LOOP); //riproduce musica in loop

}


void World::render() {


	// Set the camera as default
	camera->enable();

	glDepthMask(GL_FALSE);
	skybox-> model.setTranslation(camera->center);
	skybox->render(camera);
	glDepthMask(GL_TRUE);

	
	drawGrid();


	// Set flags
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	//// Create model matrix for cube
	//Matrix44 m;
	//m.rotate(angle * DEG2RAD, Vector3(0.0f, 1.0f, 0.0f));

	root.render(camera);
	root_player->render(camera);

	//Render the FPS, Draw Calls, etc
	//drawText(2, 2, getGPUStats(), Vector3(1, 1, 1), 2);


	//NOTA: es provisional lo substituiremos con el HUD
	/*std::string lives_info = "LIVES: " + std::to_string(root_player->total_lives); 
	drawText(350, 30, lives_info, Vector3(1, 1, 1), 2); */


	std::string score_info = "SCORE: " + std::to_string(root_player->total_points);
	drawText(5, 570, score_info, Vector3(1, 1, 1), 2);

	/*std::string turbo_info = "TURBO: " + std::to_string(root_player->turbo);
	drawText(660, 570, turbo_info, Vector3(1, 1, 1), 2);*/

	std::string bullet_info = std::to_string(root_player->bullet_count) + "/5";
	drawText(750, 35, bullet_info, Vector3(1, 1, 1), 2);

	/*std::string obj_info = "OBJECT: " + root_player->object_collected;
	drawText(10, 30, obj_info, Vector3(1, 1, 1), 2);*/




}


void World::update(float seconds_elapsed) {


	if (Input::wasKeyPressed(SDL_SCANCODE_C)) free_camera = !free_camera; 
	//printf("%d\n", free_camera);


	//float speed = seconds_elapsed * mouse_speed; //the speed is defined by the seconds_elapsed so it goes constant
	float speed = seconds_elapsed * 30.0f;



	if (free_camera)
	{
		float speed = seconds_elapsed * camera_speed;

		camera_pitch = clamp(camera_yaw);

		root.update(seconds_elapsed);

		// Mouse input to rotate the cam
		if (Input::isMousePressed(SDL_BUTTON_LEFT) || Game::instance->mouse_locked) //is left button pressed?
		{
			camera->rotate(Input::mouse_delta.x * 0.005f, Vector3(0.0f, -1.0f, 0.0f));
			camera->rotate(Input::mouse_delta.y * 0.005f, camera->getLocalVector(Vector3(-1.0f, 0.0f, 0.0f)));
		}

		// Async input to move the camera around
		if (Input::isKeyPressed(SDL_SCANCODE_LSHIFT)) speed *= 10; //move faster with left shift
		if (Input::isKeyPressed(SDL_SCANCODE_W) || Input::isKeyPressed(SDL_SCANCODE_UP)) 	camera->move(Vector3(0.0f, 0.0f, 1.0f) * speed);
		if (Input::isKeyPressed(SDL_SCANCODE_S) || Input::isKeyPressed(SDL_SCANCODE_DOWN))	camera->move(Vector3(0.0f, 0.0f, -1.0f) * speed);
		if (Input::isKeyPressed(SDL_SCANCODE_A) || Input::isKeyPressed(SDL_SCANCODE_LEFT)) 	camera->move(Vector3(1.0f, 0.0f, 0.0f) * speed);
		if (Input::isKeyPressed(SDL_SCANCODE_D) || Input::isKeyPressed(SDL_SCANCODE_RIGHT)) camera->move(Vector3(-1.0f, 0.0f, 0.0f) * speed);

	}
	else {
		camera_yaw -= Input::mouse_delta.x * 0.001;
		//camera_pitch -= Input::mouse_delta.y * 0.001;
		camera_pitch = clamp(camera_pitch, -M_PI * 0.4f, M_PI* 0.4f);
		
		Matrix44 mYaw;

		/*if (num_steps == 100) {
			rot = root_player->rotation;
			num_steps = 0;
		}
		num_steps++;*/

		mYaw.setRotation(root_player->cam_rotation, Vector3(0, 1, 0));

		Matrix44 mPitch;
		mPitch.setRotation(camera_pitch, Vector3(-1, 0, 0));

		Vector3 front = (mPitch * mYaw).frontVector();//;.normalize();
		Vector3 eye;
		Vector3 center;

		float orbit_dist = 35.0f;

		root.update(seconds_elapsed);
		root_player->update(seconds_elapsed);

		eye = root_player->model.getTranslation()  + front * orbit_dist;
		eye.y += 18.0f;

		center = root_player->model.getTranslation() + Vector3(0.0f, 0.1f, 0.0f);

		/*Vector3 dir = eye - center;
		sCollisionData data = World::get_instance()->ray_cast(center, dir.normalize(), eCollisionFilter::ALL, dir.length());

		if (data.collided) {
			eye = data.col_point;
		}*/

		camera->lookAt(eye, center, Vector3(0, 1, 0));


	}

	for (auto e : entities_to_destroy) {
		root.removeChild(e);
		delete e;
	}
	entities_to_destroy.clear();

	//std::cout << root_player->model.getTranslation().x << std::endl;

	
	
	// Sirve para "disparar"
	if (Input::wasKeyPressed(SDL_SCANCODE_T) && !free_camera) { 
		
		shootFireball();
	}

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

		mesh_name = "data/circuit_test2/" + data.first;
		sRenderData& render_data = data.second;

		// No transforms, nothing to do here
		if (render_data.models.empty())
			continue;


		Material mat = render_data.material;
		EntityCollider* new_entity = nullptr;


		size_t tag_pipe = data.first.find("Pipe");
		size_t tag_cube = data.first.find("cube");
		size_t tag_player = data.first.find("Player");
		size_t tag_waypoints = data.first.find("@waypoint");

		if (tag_pipe != std::string::npos) {
			Mesh* mesh = Mesh::Get(mesh_name.c_str());
			new_entity = new PipeCollider(mesh, mat);

			//assert(new_entity);
			//new_entity->model.setTranslation(render_data.models[0].getTranslation());
		}
		else if (tag_cube != std::string::npos) {
			Mesh* mesh = Mesh::Get(mesh_name.c_str());
			new_entity = new CubeCollider(mesh, mat);
			//assert(new_entity);
			//new_entity->model.setTranslation(render_data.models[0].getTranslation());
		}
		else if (tag_player != std::string::npos) { 
			assert(root_player);
			root_player->model.setTranslation(render_data.models[0].getTranslation());
		}
		else if (tag_waypoints != std::string::npos) {
			waypoints.push_back(render_data.models[0].getTranslation());
			continue;
		}
		else {
			Mesh* mesh = Mesh::Get(mesh_name.c_str());
			new_entity = new EntityCollider(mesh, mat);
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
	root.addChild(entity);
}

void World::removeEntity(Entity* entity)
{
	root.removeChild(entity);

}

// --- RAY CAST FUNCTION ---
sCollisionData World::ray_cast(const Vector3& origin, const Vector3& direction, int layer, float max_ray_dist)
{
	sCollisionData data;
	data.distance = max_ray_dist;

	for (auto e : root.children) {
		EntityCollider* ec = dynamic_cast<EntityCollider*>(e);
		if (ec == nullptr || !(ec->getLayer() & layer)) {
			continue;
		}
		
		Vector3 col_point;
		Vector3 col_normal;

		if (!ec->mesh->testRayCollision(ec->model, origin, direction, col_point, col_normal, player_height + 0.01f)){
			continue;
		}

		data.collided = true;

		float new_distance = (col_point - origin).length();
		if (new_distance < data.distance){
			data.col_point = col_point;
			data.col_normal = col_normal;
			data.distance = new_distance;
			data.collider_entity = ec;
		}
	}
	
	return data;
}


//----- FUNCTION TO SHOOT A FIREBALL ----
void World::shootFireball()
{
	if (root_player->bullet_count > 0) {
		Vector3 player_pos = root_player->model.getTranslation();
		Vector3 fireball_dir = root_player->model.frontVector().normalize() * root_player->rotation;
		Vector3 fireball_start_pos = player_pos + fireball_dir * 2.0f;

		// Create a new fireball entity
		EntityFireball* fireball_entity = new EntityFireball();
		fireball_entity->model.setTranslation(fireball_start_pos);
		fireball_entity->direction = fireball_dir; 

		// Add the fireball entity to the world
		addEntity(fireball_entity);

		// Decrease the bullet count
		root_player->bullet_count--;
	}
	else {
		// Output a message indicating that the player is out of bullets
		std::cout << "Cannot shoot fireball." << std::endl;
	}
}








