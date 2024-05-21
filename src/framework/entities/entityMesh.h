#pragma once

#include "entity.h"
#include "graphics/mesh.h"
#include "graphics/material.h"
#include "framework/includes.h"
#include "framework/animation.h"

class Shader;
class Camera;

struct sMeshLOD {
	Mesh* mesh_lod = nullptr;
	float distance = 0.0f;
};

class EntityMesh : public Entity {


	std::vector<sMeshLOD> mesh_lods;

public:

	EntityMesh() {};
	EntityMesh(Mesh* mesh, Material material);
	~EntityMesh(); //Destructor


	// Attributes of the derived class  
	Mesh* mesh = nullptr;
	Material material;

	Animator animator;

	bool isAnimated = false;

	//Instancing
	bool isInstanced = false;
	std::vector<Matrix44> models;

	
	// Methods overwritten from base class
	void render(Camera* camera);
	void update(float elapsed_time);


	void addInstance(const Matrix44& model);
	void addLOD(sMeshLOD mesh_lod);

};