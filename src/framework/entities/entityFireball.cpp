#include "entityFireball.h"
#include "graphics/shader.h"
#include "graphics/texture.h"
#include "game/world.h"
#include <framework/input.h>
#include "framework/camera.h"
#include "entityPlayer.h"
#include "entityHeart.h"


EntityFireball::EntityFireball() {
    this->mesh = Mesh::Get("data/meshes/fireball/fireball.obj");
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

    // Test collision with enemy
    if (testCollisionWithEnemy()) {
        std::cout << "Fireball collided with an enemy" << std::endl;

        // Mark this fireball for destruction
        World::instance->removeEntity(this);
    }

}


bool EntityFireball::testCollisionWithEnemy() {
    Vector3 collision_point, collision_normal;
    for (Entity* e : World::instance->root.children) {
        EntityAI* enemy = dynamic_cast<EntityAI*>(e);
        if (enemy) {
            if (this->mesh->testSphereCollision(enemy->model, this->model.getTranslation(), 20.0f, collision_point, collision_normal)) {
      
                // Add 1500 Points
                World::instance->root_player->total_points += 1500;

               shoot_channel = Audio::Play("data/sounds/goomba.mp3", 1.f, BASS_SAMPLE_OVER_POS);

                // Remove the enemy entity
                World::instance->removeEntity(enemy);

                // Spawn a heart entity
                EntityHeart* heart = new EntityHeart();
                if (heart) std::cout << "LIFE OF GOOMBA" << std::endl;
                heart->model.setTranslation(collision_point);
                World::instance->addEntity(heart);

                return true;
            }
        }
    }
    return false;
}
