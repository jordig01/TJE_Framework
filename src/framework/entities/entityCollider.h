#pragma once

#include "framework//includes.h"
#include "framework/framework.h"
#include "entityMesh.h"



class EntityCollider : public EntityMesh {

	void getCollisionsWithModel(const Matrix44 model, const Vector3& center, std::vector<sCollisionData>& collisions, std::vector<sCollisionData>& ground_collisions, eCollisionFilter filter);
	
	int layer = eCollisionFilter::SCENARIO;

public:
	
		bool is_static = true;

		EntityCollider() {};
		EntityCollider(Mesh* mesh, const Material& material);

		~EntityCollider() {};

		void getCollisions(const Vector3& target_position, std::vector<sCollisionData>& collisions, std::vector<sCollisionData>& ground_collisions, eCollisionFilter filter = ALL);

		int getLayer() { return layer; }
		void setLayer(int new_layer) { layer = new_layer; }


};


class PipeCollider : public EntityCollider {

public:
	PipeCollider(Mesh* mesh, const Material& material) : EntityCollider(mesh, material) {};
};


class CubeCollider : public EntityCollider {

public:	
	bool collected;
	CubeCollider(Mesh* mesh, const Material& material) : EntityCollider(mesh, material) { collected = false; };
	
	void render(Camera* camera) override;
	void update(float seconds_elapsed) override;

};