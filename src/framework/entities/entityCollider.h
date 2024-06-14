#pragma once

#include "framework//includes.h"
#include "framework/framework.h"
#include "graphics/shader.h"
#include "graphics/texture.h"
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


// --- SPECIAL COLLISIONS ---

class PipeCollider : public EntityCollider {

public:
	PipeCollider() {
		Mesh* mesh = Mesh::Get("data/circuit_test2/objects/pipe/pipe.obj");
		Material material;
		material.diffuse = Texture::Get("data/circuit_test2/objects/pipe/pipe.png");
		EntityCollider(mesh, material);
	};
	PipeCollider(Mesh* mesh, const Material& material) : EntityCollider(mesh, material) {};
};


class CubeCollider : public EntityCollider {

public:	
	
	sbool collected;

	CubeCollider() {
		Mesh* mesh = Mesh::Get("data/meshes/cube/box.obj");
		Material cube_mat;
		cube_mat.diffuse = Texture::Get("data/meshes/cube/box_mat.png");
		EntityCollider(mesh, cube_mat);
	};
	CubeCollider(Mesh* mesh, const Material& material) : EntityCollider(mesh, material) { collected = false; };
	
	void render(Camera* camera) override;
	void update(float seconds_elapsed) override;

};