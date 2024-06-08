#pragma once

#include "framework/entities/entityMesh.h"
#include "framework/utils.h"
#include "framework/entities/entityAI.h"


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

	EntityPlayer* root_player;

	EntityMesh * skybox;

	EntityPlayer* player;
	EntityAI* enemy;

	Camera* camera = nullptr;
	Camera* camera2D = nullptr;

	Vector3 old_position_player;

	//List of Waypoints to renderize some objects
	std::vector<WayPoint> enemy_waypoints;
	
	std::vector<WayPoint> waypoints;

	std::vector<WayPoint> pipewaypoints;

	std::vector <WayPoint> cubewaypoints;

	//Prueba giro
	int num_steps = 0;
	float rot = -1.0f;

	
	//Para Entity Collider
	float sphere_radius = 4.f;
	float sphere_ground_radius = 2.5f;
	float player_height = 5.0f;

	float camera_yaw = 0.f;
	float camera_pitch = 0.f;
	float camera_speed = 10.0f;
	float mouse_speed = 0.5f;

	bool free_camera = false;

	void render();
	void update(float seconds_elapsed);

	std::map<std::string, sRenderData> meshes_to_load;

	std::vector<Entity*> entities_to_destroy;

	bool parseScene(const char* filename, Entity* root);
	void addEntity(Entity* entity);
	void removeEntity(Entity* entity);
	
	void shootFireball();

	void renderCubeWaypoint();
	void renderPipeWaypoint();
	void instantiateEnemies();

	
	sCollisionData ray_cast(const Vector3& origin, const Vector3& direction, int layer, float max_ray_dist);

	bool reset = false;

};