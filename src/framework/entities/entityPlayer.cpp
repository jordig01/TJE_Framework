#include "entityPlayer.h"
#include "graphics/shader.h"
#include "game/world.h"
#include <framework/input.h>
#include "framework/camera.h"
#include "entityCollider.h"



EntityPlayer::EntityPlayer(Mesh* mesh, Material material) {
	this->mesh = mesh;
	this->material = material;
	this->position = Vector3(0,100,0);
	this->velocity = Vector3(0, 0, 0);
	this->walk_speed = 100.0f;
	this->front = Vector3(0, 0, -1);
	this->rotation = -1.0f;
	this->turbo = 1000.0f;
	//animator.playAnimation();

	//To reset the random each time in this way when we start a new game 
	//we have different seed each time
	std::srand(time(0));
}


EntityPlayer::~EntityPlayer()
{
	if (mesh != nullptr) {
		delete mesh;
		mesh = nullptr;
	}

	models.clear();

	mesh->clear();

}

void EntityPlayer::render(Camera* camera)
{

	EntityMesh::render(camera);


	//Render debug spheres...

	float sphere_radius = World::get_instance()->sphere_radius;
	float sphere_ground_radius = World::get_instance()->sphere_ground_radius;
	float player_height = World::get_instance()->player_height;


	//TODO: Pensarlo de hacerlo con cubos
	Shader* shader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");
	Mesh* mesh = Mesh::Get("data/meshes/sphere.obj");
	Matrix44 m = model;

	shader->enable();


	//First sphere (para el ground)
	{
		m.translate(0.0f, 2.0f, 0.0f);
		m.scale(sphere_ground_radius, sphere_ground_radius, sphere_ground_radius);

		shader->setUniform("u_color", Vector4(1.0f, 0.0f, 0.0f, 1.0f));
		shader->setUniform("u_viewprojection", camera->viewprojection_matrix);
		shader->setUniform("u_model", m);

		mesh->render(GL_LINES);
	}


	//Second sphere
	{
		m = model;
		m.translate(0.0f, player_height, 0.0f);
		m.scale(sphere_radius, sphere_radius, sphere_radius);

		shader->setUniform("u_color", Vector4(0.0f, 1.0f, 0.0f, 1.0f));

		shader->setUniform("u_model", m);

		mesh->render(GL_LINES);

	}

	shader->disable();


}



void EntityPlayer::update(float seconds_elapsed) {

	float camera_yaw = World::get_instance()->camera_yaw;

	Matrix44 mYaw;
	mYaw.setRotation(camera_yaw, Vector3(0, 1, 0));

	//Vector3 front = Vector3(0, 0, -1);
	//Vector3 right = Vector3(1, 0, 0);
	//Vector3 left = Vector3(-1, 0, 0);
	//Vector3 back = Vector3(0, 0, 1);

	//Cambiar cámara
	//Vector3 front_cam = mYaw.frontVector();
	//Vector3 right_cam = mYaw.rightVector();

	position = model.getTranslation();

	Vector3 move_dir;
	float moving = 0.0f;
	bool turning = false;
	float drift = 1.0f;

	if (Input::isKeyPressed(SDL_SCANCODE_W) || Input::isKeyPressed(SDL_SCANCODE_UP)) {
		move_dir += front;
		moving = 1.0f;
		last_moving = 1.0f;
	}

	if (Input::isKeyPressed(SDL_SCANCODE_S) || Input::isKeyPressed(SDL_SCANCODE_DOWN)) {
		move_dir -= front;
		moving = -1.0f;
		last_moving = -1.0f;
	}

	if ((Input::isKeyPressed(SDL_SCANCODE_A) || Input::isKeyPressed(SDL_SCANCODE_LEFT)) && moving != 0) {
		if (Input::isKeyPressed(SDL_SCANCODE_V)) drift = 2.0f;
		right = false;
		left = true;
		turning = true;
		rotation -= 0.004f * moving * drift;
		cam_rotation -= 0.001f * moving * drift;
		if (cam_rotation < rotation) cam_rotation += 0.003f * drift;
		cam_rotation = clamp(cam_rotation, rotation - 0.5f * drift, rotation + 0.5f * drift);
	}


	if ((Input::isKeyPressed(SDL_SCANCODE_D) || Input::isKeyPressed(SDL_SCANCODE_RIGHT)) && moving != 0) {
		if (Input::isKeyPressed(SDL_SCANCODE_V)) drift = 2.0f;
		right = true;
		left = false;
		turning = true;
		rotation += 0.004f * moving * drift;
		cam_rotation += 0.001f * moving * drift;
		if (cam_rotation > rotation)cam_rotation -= 0.003f * drift;
		cam_rotation = clamp(cam_rotation, rotation - 0.5f * drift, rotation + 0.5f * drift);
	}
	if (cam_rotation != rotation && !turning) {
		if (left) {
			cam_rotation -= 0.004f * last_moving * drift;
			cam_rotation = clamp(cam_rotation, rotation, rotation + 0.5f * drift);
		}
		else if (right) {
			cam_rotation += 0.004f * last_moving * drift;
			cam_rotation = clamp(cam_rotation, rotation - 0.5f * drift, rotation);
		}
	}
	front = Vector3(sin(rotation), 0, -cos(rotation));


	float speed_mult = walk_speed;
	//if (Input::isKeyPressed(SDL_SCANCODE_LSHIFT)) speed_mult *= 3.0f;

	// ---- TURBO LOGIC ----
	if (Input::isKeyPressed(SDL_SCANCODE_X) && turbo > 0) {
		speed_mult *= 1.5f;
		turbo -= seconds_elapsed * 50.0f;  // Decrease turbo over time
		if (turbo < 0) turbo = 0;
	}

	move_dir.normalize();
	move_dir *= speed_mult;

	velocity += move_dir;

	//Check collisions with the world entitites
	handleCollisions(seconds_elapsed);

	/*if (animation == eAnimatedState::HANDLE && velocity.length() > 1.f) {
		animator.playAnimation("data/animations/yoshi_movement.skanim");
	}

	*/


	position += velocity * seconds_elapsed;

	//Decrease velocity when not moving
	velocity.x *= 0.5f;
	velocity.z *= 0.5f;


	model.setTranslation(position);
	model.rotate(rotation, Vector3(0, 1, 0));




	EntityMesh::update(seconds_elapsed);



}


//--- FUNCTION TO HANDLE COLLISIONS ---
void EntityPlayer::handleCollisions(float seconds_elapsed) {
	std::vector<sCollisionData> collisions;
	std::vector<sCollisionData> ground_collisions;


	for (auto e : World::get_instance()->root.children) {
		EntityCollider* ec = dynamic_cast<EntityCollider*>(e);

		if (ec != nullptr) {
			ec->getCollisions(position + velocity * seconds_elapsed, collisions, ground_collisions);
		}

		// Check for CubeCollider 
		CubeCollider* cube = dynamic_cast<CubeCollider*>(e);
		if (cube != nullptr && !cube->collected) {
			std::vector<sCollisionData> cube_collisions;
			cube->getCollisions(position + velocity * seconds_elapsed, cube_collisions, ground_collisions);
			if (!cube_collisions.empty()) {
				handleCubePickup(cube);
				std::cout << "CUBE SURPRISE COLLIDED"<< cube->collected << std::endl;
			}
		}

		checkPipeCollision(seconds_elapsed, ground_collisions);
		checkEnemyCollision(seconds_elapsed, ground_collisions);

	}

	for (const sCollisionData& collision : collisions) {
		Vector3 newDir = velocity.dot(collision.col_normal) * collision.col_normal;
		velocity.x -= newDir.x;
		velocity.y -= newDir.y;
		velocity.z -= newDir.z;
	}

	bool is_grounded = false;
	for (const sCollisionData& collision : ground_collisions) {
		float up_factor = fabsf(collision.col_normal.dot(Vector3::UP));
		if (up_factor > 0.8f) {
			is_grounded = true;
		}

		if (collision.col_point.y > (position.y + velocity.y * seconds_elapsed)) {
			position.y = collision.col_point.y;
		}
	}

	if (!is_grounded) {
		velocity.y -= 40.0f * seconds_elapsed;
	}
	else if (Input::wasKeyPressed(SDL_SCANCODE_SPACE)) {
		velocity.y = 2.0f;
	}
}


//---- COLLISION CON PIPE -----
void EntityPlayer::checkPipeCollision(float seconds_elapsed, std::vector<sCollisionData> ground_collisions) {
	for (auto e : World::get_instance()->root.children) {
		PipeCollider* pipe = dynamic_cast<PipeCollider*>(e);
		if (pipe != nullptr) {
			std::vector<sCollisionData> pipe_collisions;
			pipe->getCollisions(position + velocity * seconds_elapsed, pipe_collisions, ground_collisions);

			// Check collision with pipe and velocity condition
			if (!pipe_collisions.empty() && velocity.length() > 250.0f) {
				loseLife(1);
				losePoints(500);
				std::cout << "PIPE COLLIDED: Life lost, points deducted." << std::endl;
				break;
			}
		}
	}
}



// ---- COLLISION CON SURPRISE CUBE -----
void EntityPlayer::handleCubePickup(CubeCollider* cube) {
	// Generate a random number to determine if it's an obstacle (20%) or a collectible (80%)
	int random_value = std::rand() % 100 + 1; // Generate a random number between 1 and 100

	if (random_value <= 20) {
		// 20% chance of being an obstacle
		loseLife(1);
		losePoints(500);
		std::cout << "SURPRISE CUBE COLLIDED: Life lost, points deducted." << std::endl;
	}
	else {
		// 80% chance of being a collectible
		int collectible_value = std::rand() % 3; // Generate a random number between 0 and 2

		if (collectible_value == 0) {
			// 33% chance of the cube containing a heart (recovers a life)
			addLife(1);
			object_collected = "life";
		}
		else if (collectible_value == 1) {
			// 33% chance of the cube containing a thunder (increases turbo bar)
			turbo += turbo * (std::rand() % 11 + 10) / 100.0f; // Increase turbo bar by 10-20%
			if (turbo > 1000.0f) {
				total_points += 200; // If turbo bar is full, add 200 points to score
			}
			object_collected = "turbo";
		}
		else {
			// 33% chance of the cube containing bullets (increase bullet counter)
			addBullet(1);
			object_collected = "bullet";
		}

		// Mark the cube as collected and remove it from the scene and from the root's list
		cube->collected = true;
		World::get_instance()->removeEntity(cube);
	}
}


//--- COLLISION CON ENEMIGO ----
void EntityPlayer::checkEnemyCollision(float seconds_elapsed, std::vector<sCollisionData> ground_collisions) {
	for (auto e : World::get_instance()->root.children) {
		// Verifica si la entidad es un EntityAI
		EntityAI* enemy = dynamic_cast<EntityAI*>(e);
		if (enemy != nullptr) {
			std::vector<sCollisionData> enemy_collisions;
			enemy->getCollisions(position + velocity * seconds_elapsed, enemy_collisions, ground_collisions);

			// Verifica si hubo una colisión con el enemigo
			if (!enemy_collisions.empty()) {
				loseLife(1);
				losePoints(500);
				std::cout << "ENEMY COLLIDED: Life lost, points deducted." << std::endl;
				break; // Sal del ciclo una vez que se encuentre una colisión con un enemigo
			}
		}
	}
}






//--- SCORE, LIFES, BULLET MECHANICS ---
void EntityPlayer::addPoints(int point)
{
	total_points += point;
}

void EntityPlayer::losePoints(int point)
{
	total_points -= point;
}

void EntityPlayer::addLife(int life) {
	total_lives += life;
	if (total_lives > 3) {
		total_points += 200; 
		total_lives = 3;
	}

}

void EntityPlayer::loseLife(int life) {

	if (total_lives > 0) {
		total_lives -= life;
	}
	else {
		std::cout << "GAME OVER" << std::endl;
	}
}

void EntityPlayer::addBullet(int bullet) {
	bullet_count += bullet;

	if (bullet_count > 5) {
		total_points += 200;
		bullet_count = 5;
	}
}
