#include "entityPlayer.h"
#include "game/world.h"
#include <framework/input.h>


EntityPlayer::EntityPlayer(Mesh* mesh, Material material) {
	this->mesh = mesh;
	this->material = material;
	this->position = Vector3(0,100,0);
	this->velocity = Vector3(0, 0, 0);
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

void EntityPlayer::update(float seconds_elapsed) {

	float camera_yaw = World::get_instance()->camera_yaw;

	Matrix44 mYaw;
	mYaw.setRotation(camera_yaw, Vector3(0, 1, 0));

	Vector3 front = Vector3(0, 0, -1);
	Vector3 right = Vector3(1, 0, 0);

	position = model.getTranslation();

	Vector3 move_dir;

	if (Input::isKeyPressed(SDL_SCANCODE_W) || Input::isKeyPressed(SDL_SCANCODE_UP)) {
		move_dir += front;
	}

	if (Input::isKeyPressed(SDL_SCANCODE_S) || Input::isKeyPressed(SDL_SCANCODE_DOWN)) {
		move_dir -= front;
	}

	if (Input::isKeyPressed(SDL_SCANCODE_A) || Input::isKeyPressed(SDL_SCANCODE_LEFT)) {
		move_dir += right;
	}

	if (Input::isKeyPressed(SDL_SCANCODE_D) || Input::isKeyPressed(SDL_SCANCODE_RIGHT)) {
		move_dir -= right;
	}


	float speed_mult = walk_speed;
	if (Input::isKeyPressed(SDL_SCANCODE_LSHIFT)) {
		speed_mult *= 3.0f;



		move_dir.normalize();
		move_dir *= speed_mult;

		velocity += move_dir;

		position += velocity * seconds_elapsed;

		velocity.x *= 0.5f;
		velocity.z *= 0.5f;

		model.setTranslation(position);
		model.rotate(camera_yaw, Vector3(0, 1, 0));

		EntityMesh::update(seconds_elapsed);

	}
}


