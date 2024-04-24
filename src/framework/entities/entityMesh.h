//#pragma once
//
//#include "framework/entities/entity.h"
//#include "graphics/mesh.h"
//
//
//class Material;
//
//
//class EntityMesh : public Entity {
//
//
//public:
//
//	// Attributes of the derived class  
//	Mesh* mesh = nullptr;
//	/*Texture* texture = nullptr;
//	Shader* shader = nullptr;
//	Vector4 color;*/ //YA LO HACE MATERIAL
//
//	Material material;
//
//	EntityMesh(); 
//	EntityMesh(Mesh* mesh, Material material);
//
//	//bool instanced = false;
//	//std::vector<Matrix44> models;
//	//void addInstance(const Matrix44& model); models.push_back(model)
//
//	// Methods overwritten from base class
//	void render();
//	void update(float elapsed_time);
//
//};