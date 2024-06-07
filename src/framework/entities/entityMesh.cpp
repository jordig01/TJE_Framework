#include "entityMesh.h"
#include "graphics/shader.h"
#include "framework/camera.h"
#include "game/game.h"
#include <algorithm>



EntityMesh::EntityMesh(Mesh* mesh, Material material) {
	this->mesh = mesh;
	this->material = material;
}


EntityMesh::~EntityMesh() {
	if (mesh != nullptr) {
		delete mesh;
		mesh = nullptr;
	}

	models.clear();

	for (auto& lod : mesh_lods) {
		if (lod.mesh_lod != nullptr) {
			delete lod.mesh_lod;
			lod.mesh_lod = nullptr;
		}
	}
	mesh_lods.clear();
}



void EntityMesh::render(Camera* camera) {

	//// Get the last camera that was activated 
	//Camera* camera = Camera::current;

	if (!mesh) return;

	std::vector<Matrix44>* final_models = &models;
	std::vector<Matrix44> models_instanced;


	
	if (isInstanced) {
		for (int i = 0; i < models.size(); ++i) {
			Vector3 center_world = models[i] * mesh->box.center;
			float aabb_radius = mesh->box.halfsize.length();

			if (camera->testSphereInFrustum(center_world, aabb_radius)) {
				models_instanced.push_back(models[i]);
			}

			final_models = &models_instanced;
		}
	}
	else {
		Vector3 center_world = model * mesh->box.center;
		float aabb_radius = mesh->box.halfsize.length();

		if (!camera->testSphereInFrustum(center_world, aabb_radius)) {
			return;
		}
	}


	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);

	if (!material.shader) {
		material.shader = Shader::Get("data/shaders/basic.vs", "data/shaders/phong.fs");
	}
	

	// Enable shader and pass uniforms 
	material.shader->enable();


	Vector2 maps = { 0.0f, 0.0f };


	material.shader->setUniform("u_color", material.color);
	material.shader->setUniform("u_viewprojection", camera->viewprojection_matrix);

	//Para el cubemap
	material.shader->setUniform("u_camera_position", camera->eye);

	if (material.diffuse) {
		maps.x = 1.0f;
		material.shader->setUniform("u_texture", material.diffuse, 0);
		//material.shader->setTexture("u_texture", material.diffuse, 0);
	}


	if (material.normal) {
		maps.y = 1.0f;
		material.shader->setUniform("u_normal_texture", material.normal, 1);
	}

	//Other Uniform
	material.shader->setUniform("u_background_color", Vector3(1.0f, 0.0f, 0.0f));
	material.shader->setUniform("u_time", Game::instance->time);



	//Light Part
	material.shader->setUniform("u_Ka", Vector3(0.1f));
	material.shader->setUniform("u_Kd", Vector3(0.0f));
	material.shader->setUniform("u_Ks", Vector3(0.0f));
	material.shader->setUniform("u_light_position", Vector3(0.0f, 10.0f, 0.0f));
	material.shader->setUniform("u_light_color", Vector3(1.0f));
	//material.shader->setUniform("u_fog_factor", Vector3(0.1f));



	material.shader->setUniform("u_maps", maps);


	//si no estoy instanciando le envio mi model
	if (!isInstanced) {
		material.shader->setUniform("u_model", getGlobalMatrix());
	}

	//si instanciado renderInstance
	if (isInstanced)
		mesh->renderInstanced(GL_TRIANGLES, final_models->data(), final_models->size());
	else {
		if (isAnimated) {
			mesh->renderAnimated(GL_TRIANGLES, &animator.getCurrentSkeleton());
		}
		else {
			mesh->render(GL_TRIANGLES);
		}

	}


	// Disable shader after finishing rendering
	material.shader->disable();

	Entity::render(camera);
}


void EntityMesh::update(float seconds_elapsed) {


	if (isAnimated) {
		animator.update(seconds_elapsed);
	}

	Entity::update(seconds_elapsed);

}


void EntityMesh::addInstance(const Matrix44& model)
{
	models.push_back(model);
}

void EntityMesh::addLOD(sMeshLOD mesh_lod) {
	mesh_lods.push_back(mesh_lod);

	std::sort(mesh_lods.begin(), mesh_lods.end(), [](sMeshLOD a, sMeshLOD b) {
		return a.distance < b.distance;
		});
}

