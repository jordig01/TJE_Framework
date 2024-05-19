//#include "entityPlayer.h"
//#include "graphics/shader.h"
//#include "game/world.h"
//#include <framework/input.h>
//#include "framework/camera.h"
//#include "entityCollider.h"
//
//
//EntityPlayer::EntityPlayer(Mesh* mesh, Material material) {
//	this->mesh = mesh;
//	this->material = material;
//	this->position = Vector3(0,100,0);
//	this->velocity = Vector3(0, 0, 0);
//	this->walk_speed = 100.0f;
//	this->front = Vector3(0, 0, -1);
//	this->rotation = -1.0f;
//}
//
//
//EntityPlayer::~EntityPlayer()
//{
//	if (mesh != nullptr) {
//		delete mesh;
//		mesh = nullptr;
//	}
//
//	models.clear();
//
//	mesh->clear();
//
//}
//
//void EntityPlayer::render(Camera* camera)
//{
//
//	EntityMesh::render(camera);
//
//
//	//Render debug spheres...
//
//	float sphere_radius = World::get_instance()->sphere_radius;
//	float sphere_ground_radius = World::get_instance()->sphere_ground_radius;
//	float player_height = World::get_instance()->player_height;
//
//
//	//TODO: Pensarlo de hacerlo con cubos
//	Shader* shader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");
//	Mesh* mesh = Mesh::Get("data/meshes/sphere.obj");
//	Matrix44 m = model;
//
//	shader->enable();
//
//
//	//First sphere (para el ground)
//	{
//		m.translate(0.0f, 2.0f, 0.0f);
//		m.scale(sphere_ground_radius, sphere_ground_radius, sphere_ground_radius);
//
//		shader->setUniform("u_color", Vector4(1.0f, 0.0f, 0.0f, 1.0f));
//		shader->setUniform("u_viewprojection", camera->viewprojection_matrix);
//		shader->setUniform("u_model", m);
//
//		mesh->render(GL_LINES);
//	}
//
//
//	//Second sphere
//	{
//		m = model;
//		m.translate(0.0f, player_height, 0.0f);
//		m.scale(sphere_radius, sphere_radius, sphere_radius);
//
//		shader->setUniform("u_color", Vector4(0.0f, 1.0f, 0.0f, 1.0f));
//
//		shader->setUniform("u_model", m);
//
//		mesh->render(GL_LINES);
//
//	}
//
//	shader->disable();
//
//
//}
//
//
//
//void EntityPlayer::update(float seconds_elapsed) {
//
//	float camera_yaw = World::get_instance()->camera_yaw;
//
//	Matrix44 mYaw;
//	mYaw.setRotation(camera_yaw, Vector3(0, 1, 0));
//
//	//Vector3 front = Vector3(0, 0, -1);
//	//Vector3 right = Vector3(1, 0, 0);
//	//Vector3 left = Vector3(-1, 0, 0);
//	//Vector3 back = Vector3(0, 0, 1);
//
//	//Cambiar c�mara
//	//Vector3 front_cam = mYaw.frontVector();
//	//Vector3 right_cam = mYaw.rightVector();
//
//	position = model.getTranslation();
//
//	Vector3 move_dir;
//	float moving = 0.0f;
//
//	if (Input::isKeyPressed(SDL_SCANCODE_W) || Input::isKeyPressed(SDL_SCANCODE_UP)) {
//		move_dir += front;
//		moving = 1.0f;
//		last_moving = 1.0f;
//	}
//
//	if (Input::isKeyPressed(SDL_SCANCODE_S) || Input::isKeyPressed(SDL_SCANCODE_DOWN)) {
//		move_dir -= front;
//		moving = -1.0f;
//		last_moving = -1.0f;
//	}
//
//	if ((Input::isKeyPressed(SDL_SCANCODE_A) || Input::isKeyPressed(SDL_SCANCODE_LEFT))) {
//		right = false;
//		left = true;
//		rotation -= 0.004f * moving;
//		cam_rotation -= 0.001f * moving;
//	}
//
//
//	if ((Input::isKeyPressed(SDL_SCANCODE_D) || Input::isKeyPressed(SDL_SCANCODE_RIGHT))) {
//		right = true;
//		left = false;
//		rotation += 0.004f * last_moving;
//		cam_rotation += 0.001f * last_moving;
//	}
//	if (cam_rotation != rotation) {
//		if (left) {
//			cam_rotation -= 0.001f * last_moving;
//		}
//		else if (right) {
//			cam_rotation += 0.001f * last_moving;
//		}
//	}
//	front = Vector3(sin(rotation), 0, -cos(rotation));
//
//
//	float speed_mult = walk_speed;
//	if (Input::isKeyPressed(SDL_SCANCODE_LSHIFT)) speed_mult *= 3.0f;
//
//	move_dir.normalize();
//	move_dir *= speed_mult;
//
//	velocity += move_dir;
//
//	//Check collisions with the world entitites
//	handleCollisions(seconds_elapsed);
//
//	position += velocity * seconds_elapsed;
//
//	//Decrease velocity when not moving
//	velocity.x *= 0.5f;
//	velocity.z *= 0.5f;
//
//
//	model.setTranslation(position);
//	model.rotate(rotation, Vector3(0, 1, 0));
//
//	EntityMesh::update(seconds_elapsed);
//
//
//
//}
//
//
//
//void EntityPlayer::handleCollisions(float seconds_elapsed) {
//	std::vector<sCollisionData> collisions;
//	std::vector<sCollisionData> ground_collisions;
//
//
//	for (auto e : World::get_instance()->root.children) {
//
//		EntityCollider* ec = dynamic_cast<EntityCollider*>(e);
//
//		if (ec != nullptr)
//			ec->getCollisions(position + velocity * seconds_elapsed, collisions, ground_collisions);
//	}
//
//
//	for (const sCollisionData& collision : collisions) {
//		Vector3 newDir = velocity.dot(collision.col_normal) * collision.col_normal;
//		velocity.x -= newDir.x;
//		velocity.y -= newDir.y;
//		velocity.z -= newDir.z;
//	}
//
//
//	bool is_grounded = false;
//
//	for (const sCollisionData& collision : ground_collisions) {
//
//
//		//Si la normal apunta hacia arriba, collision con suelo
//		float up_factor = fabsf(collision.col_normal.dot(Vector3::UP));
//		if (up_factor > 0.8f) {
//			is_grounded = true;
//		}
//
//		if (collision.col_point.y > (position.y + velocity.y * seconds_elapsed)) {
//			position.y = collision.col_point.y;
//		}
//	}
//
//
//	if (!is_grounded) {
//		velocity.y -= 9.8f * seconds_elapsed;
//	}
//	else if (Input::wasKeyPressed(SDL_SCANCODE_SPACE)) {
//		velocity.y = 2.0f;
//	}
//
//
//}