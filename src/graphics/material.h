#pragma once

#include "framework/includes.h"
#include "framework/framework.h"

class Shader;
class Texture;

class Material {
public:
	Shader* shader = nullptr;
	Vector4 color = Vector4(1.f);
	Texture* diffuse = nullptr;



	//-- AGGIUNYTO 28/05 --
	Texture* normal = nullptr;

	bool transparent =false;

	int tiling = 0;
};

struct sRenderData {
	Material material;
	std::vector<Matrix44> models;
};