#include "entityPlayer.h"
#include "graphics/shader.h"
#include "game/world.h"
#include <framework/input.h>
#include "framework/camera.h"


EntityPlayer::EntityPlayer(Mesh* mesh, Material material) {
	this->mesh = mesh;
	this->material = material;
	this->position = Vector3(0,100,0);
	this->velocity = Vector3(0, 0, 0);
	this->walk_speed = 100.0f;
	this->front = Vector3(0, 0, -1);
	this->rotation = -1.0f;
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

//void EntityPlayer::render(Camera* camera)
// 
// //REnder mesh
// EntityMesh::render(camera);
// 
// //Debug spheres...
// 
// Shader* shader = Shader::Get
// Mesh* mesh = Mesh::Get
// Matrix44 m = model;
// 
// m.model;
// m.translate(0.0f, player_height, 0.0f);
// m.scale(sphere_radius)
// 
// 
// //Check collisions with world entities
// for(auto e: World::get_instance()->root.childern()
// 
// 
// //Ground collisions
// bool is_grounded = false;
// 
// for(const sCollisionDAta& collision : ground_collisions){
// 
// float up_factor = fabs(collision.com_normal.dot(Vector3::UP));
// if(up_factor>0.8){
// is_grounded = true;
// }
// if(collision.col_point.y>(position.y + veloxity.y * seconds_elapsed)){
// position.y = collision.col_point.y
// }
// 
// if(!is_grounded){
// veloscity.y -= //Añadir gravedad
// }else if(){
// 
// }
// 
// 
//void EntityPlayer::render(Camera* camera)

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
	bool moving = false;

	if (Input::isKeyPressed(SDL_SCANCODE_W) || Input::isKeyPressed(SDL_SCANCODE_UP)) {
		move_dir += front;
		moving = true;
	}

	if (Input::isKeyPressed(SDL_SCANCODE_S) || Input::isKeyPressed(SDL_SCANCODE_DOWN)) {
		move_dir -= front;
		moving = true;
	}

	if ((Input::isKeyPressed(SDL_SCANCODE_A) || Input::isKeyPressed(SDL_SCANCODE_LEFT)) && moving) {
		rotation -= 0.005f;
	}


	if ((Input::isKeyPressed(SDL_SCANCODE_D) || Input::isKeyPressed(SDL_SCANCODE_RIGHT)) && moving) {
		rotation += 0.005f;
	}
	front = Vector3(sin(rotation), 0, -cos(rotation));


	float speed_mult = walk_speed;
	if (Input::isKeyPressed(SDL_SCANCODE_LSHIFT)) speed_mult *= 3.0f;

	move_dir.normalize();
	move_dir *= speed_mult;

	velocity += move_dir;

	position += velocity * seconds_elapsed;


	//Decrease velocity when not moving
	velocity.x *= 0.5f;
	velocity.z *= 0.5f;

	model.setTranslation(position);
	model.rotate(rotation, Vector3(0, 1, 0));

	EntityMesh::update(seconds_elapsed);


}

void EntityPlayer::render(Camera* camera)
{

	EntityMesh::render(camera);


	//Render debug spheres...

	float sphere_radius = World::get_instance()->sphere_radius;
	float sphere_ground_radius = World::get_instance()->sphere_ground_radius;
	float player_height = World::get_instance()->player_height;

	Shader* shader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");
	Mesh* mesh = Mesh::Get("data/meshes/sphere.obj");
	Matrix44 m = model;

	shader->enable();


	//First sphere
	{
		m.translate(0.0f, sphere_ground_radius, 0.0f);
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


