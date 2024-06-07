#include "entityHeart.h"
#include "graphics/texture.h"
#include "graphics/shader.h"
#include "game/world.h"

EntityHeart::EntityHeart() {
    this->mesh = Mesh::Get("data/meshes/heart/life.obj");
    this->material.diffuse = Texture::Get("data/meshes/heart/MI_heart_alb.png");
    this->remaining_time = 6.0f; // Heart will be rendered for 6 seconds
    this->rotation_speed = 0.5f;
}

EntityHeart::EntityHeart(Mesh* mesh, Material material) {
    this->mesh = mesh;
    this->material = material;
    this->remaining_time = 4.0f;
    this->rotation_speed = 0.5f;
}

EntityHeart::~EntityHeart() {
}

void EntityHeart::update(float seconds_elapsed) {
    // Reduce remaining time
    remaining_time -= seconds_elapsed;

    // Move up and rotate
    this->model.translate(Vector3(0, seconds_elapsed*10.f, 0));
    this->model.rotate(seconds_elapsed * rotation_speed, Vector3(0, 1, 0));

    // Remove entity when time runs out
    if (remaining_time <= 0) {
        World::instance->removeEntity(this);
    }
}
