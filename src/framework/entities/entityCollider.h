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
		EntityCollider(Mesh* mesh, const Material& material): 
			EntityMesh(mesh, material) {};

		~EntityCollider() {};

		void getCollisions(const Vector3& target_position, std::vector<sCollisionData>& collisions, std::vector<sCollisionData>& ground_collisions, eCollisionFilter filter);

		int getLayer() { return layer; }
		void setLayer(int new_layer) { layer = new_layer; }


};