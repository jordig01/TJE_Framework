#pragma once

#include "framework/entities/entityMesh.h"
#include "framework/utils.h"


class EntityPlayer;

class Camera;



class World {



public:
	
	static World* instance;

	static World* get_instance() {
		if (instance != nullptr) 
			return instance;

		instance = new World();
		return instance;
	}

	World();

	Entity root;

	EntityMesh * skybox;

	EntityPlayer* player;

	Camera* camera = nullptr;


	//Para Entity Collider
	float sphere_radius = 50.0f;
	float sphere_ground_radius = 50.0f;
	float player_height = 50.0f;

	float camera_yaw = 0.f;
	float camera_pitch = 0.f;
	float camera_speed = 10.0f;
	float mouse_speed = 0.5f;

	bool free_camera = true;

	void render();
	void update(float seconds_elapsed);

	std::map<std::string, sRenderData> meshes_to_load;

	std::vector<Entity*> entities_to_destroy;

	bool parseScene(const char* filename, Entity* root);
	void addEntity(Entity* entity);
	void removeEntity(Entity* entity);
};