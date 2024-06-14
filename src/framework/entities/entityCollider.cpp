#include "entityCollider.h"
#include "game/world.h"




void EntityCollider::getCollisionsWithModel(const Matrix44 model, const Vector3& center, std::vector<sCollisionData>& collisions, std::vector<sCollisionData>& ground_collisions, eCollisionFilter filter) {

	Vector3 collision_point;
	Vector3 collision_normal;

	float sphere_radius = World::get_instance()->sphere_radius;
	float sphere_ground_radius = World::get_instance()->sphere_ground_radius;
	float player_height = World::get_instance()->player_height;

	Vector3 floor_sphere_center = center + Vector3(0.f, sphere_ground_radius, 0.f);
	if (mesh->testSphereCollision(model, floor_sphere_center, sphere_radius, collision_point, collision_normal)) {
		collisions.push_back({ collision_point, collision_normal.normalize(), floor_sphere_center.distance(collision_point)});
	}

	Vector3 character_center = center + Vector3(0.f, player_height, 0.f);
	if (mesh->testSphereCollision(model, character_center, sphere_radius,collision_point, collision_normal)) {
		collisions.push_back({ collision_point, collision_normal.normalize(), character_center.distance(collision_point) });
	}


	//Check if grounded
	if (mesh->testRayCollision(model, character_center, Vector3(0, -1, 0), collision_point, collision_normal, player_height + 0.01f)) {
		ground_collisions.push_back({ collision_point, collision_normal.normalize(), character_center.distance(collision_point) });
	}

}

EntityCollider::EntityCollider(Mesh* mesh, const Material& material): EntityMesh(mesh, material)
{
	
}

void EntityCollider::getCollisions(const Vector3& target_position, std::vector<sCollisionData>& collisions, std::vector<sCollisionData>& ground_collisions, eCollisionFilter filter){
	if (!(layer & filter)) return;
	
	if (!isInstanced) {
		getCollisionsWithModel(model, target_position, collisions, ground_collisions, filter);
	}
	 else{
		 for(int i = 0; i<models.size();++i){
			 getCollisionsWithModel(models[i], target_position, collisions, ground_collisions, filter);
		 }
	 }

}

void CubeCollider::render(Camera* camera)
{
	if (collected) World::instance->removeEntity(this);

	EntityMesh::render(camera);
}


void CubeCollider::update(float seconds_elapsed)
{
	float rotation_speed = 0.5f;
	model.rotate(seconds_elapsed * rotation_speed, Vector3(0,1,0));

	EntityMesh::update(seconds_elapsed);
}