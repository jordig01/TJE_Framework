#include "entityFireball.h"
#include "graphics/shader.h"
#include "graphics/texture.h"
#include "game/world.h"
#include <framework/input.h>
#include "framework/camera.h"


EntityFireball::EntityFireball() {
	this->mesh = Mesh::Get("data/meshes/fireball.obj");
	this->material.diffuse = Texture::Get("data/textures/PlayerFireBall_alb.png");
}

EntityFireball::EntityFireball(Mesh* mesh, Material material) {
	this->mesh = mesh;
	this->material = material;
}

EntityFireball::~EntityFireball()
{
}


void EntityFireball::update(float seconds_elapsed) {
	
	this->model.translate(direction * seconds_elapsed * 200.0f); // Move forward by 200 units per seconds
}
