#include "entityUI.h"
#include "game/game.h"
#include <framework/input.h>

EntityUI::EntityUI(Vector2 size, const Material& material)
{

}

EntityUI::EntityUI(Vector2 pos, Vector2 size, const Material& material, eButtonId button_id)
{
	position = pos;
	this->size = size;
	this->button_id = button_id;

	mesh = new Mesh();
	mesh->createQuad(pos.x, pos.y, size.x, size.y, true);

	this->material = material;
	
	this->original_texture = material.diffuse;

	if (!this->material.shader) {
		if (material.diffuse) {
			std::cout << "Loading texture shader." << std::endl;
			this->material.shader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");
		}
		else {
			std::cout << "Loading flat shader." << std::endl;
			this->material.shader = Shader::Get("data/shaders/basic.vs", "data/shaders/flat.fs");
		}

		if (this->material.shader == nullptr) {
			std::cerr << "Error: Shader not found or failed to load." << std::endl;
		}
	}
}



void EntityUI::render(Camera* camera2d) {
	//shader
	//enviar unifrom ...
	//Igual que EntityMesh, pero cambiando cámara y:
	// glDisable(GL_DEPTH_TEST)
	// glDisable(GL_CULL_FACE)
	// glEnable(GL_BLEND)
	// glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// 
	// material.shader->enable();
	// 
	// World* world = World::get_instance();
	// Matrix44 viewProj = camera2d->voew`rpkectopm_matrix
	// 
	// material.shader->setUniform("u_model", model);
	// material.shader->setUniform("u_viewprojection", viewProj);
	// material.shader->setUniform("u_color", material.color);
	// material.shader->setUniform("u_mask", mask);
	// 
	// 
	// 
	// Dejamos todo como estaba antes
	// glEnable(GL_DEPTH_TEST)
	// glEnable(GL_CULL_FACE)
	// glDisable(GL_BLEND)
	// glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// 
	//MenuStage
	// 
	// EntityUI* background = nullptr;
	// EntityUI* play_button = nullptr;
	// EntityUI* exit_button = nullptr;
	// 
	// en el cpp:
	// Material backgorun_mat;
	// background_mat.diffuse = Texture::Get();
	// background = new EntityUI();
	// 
	// play_button = new EntityUI(Vector2(), ..., eButtonId::PlayButton)
	// 
	// //Podemos hacer que background sea un root y guardar todo ahí
	// background->addChild(play_button);
	// background->addChild(exit_button);
	// 
	// 
	//MenuStage

	if (!visible) return;

	if (!is3D) {
		glDisable(GL_DEPTH_TEST);
	}

	glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	if (material.shader == nullptr) printf("NO SHADER");

	material.shader->enable();

	World* world = World::get_instance();
	Matrix44 viewProj = camera2d->viewprojection_matrix;

	material.shader->setUniform("u_model", model);
	material.shader->setUniform("u_viewprojection", viewProj);
	material.shader->setUniform("u_color", material.color);
	material.shader->setUniform("u_mask", mask);

	if (material.diffuse) {
		material.shader->setUniform("u_texture", material.diffuse, 0);
	}

	if (is3D) {
		Vector2 _size = size;
		float max_dist = 5.0f;
		float dist = clamp(world->camera->eye.distance(pos3d), 0.01f, max_dist);
		_size *= 1.f - dist / max_dist;
		mesh->createQuad(position.x, position.y, _size.x, _size.y, true);
		mesh->render(GL_TRIANGLES);
	}
	else {
		mesh->render(GL_TRIANGLES);
	}


	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glDisable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Entity::render(camera2d);
	


}

void EntityUI::update(double seconds_elapsed) {
	
	Vector2 mousepos = Input::mouse_position;
	if (button_id != UndefinedButton &&
		mousepos.x > (position.x - size.x * 0.5f) &&
		mousepos.x < (position.x + size.x * 0.5f) &&
		mousepos.y > (position.y - size.y * 0.5f) &&
		mousepos.y < (position.y + size.y * 0.5f)) {
		
		material.diffuse = hover_texture;

		printf("MOUSE OVER");

		if (Input::isMousePressed(SDL_BUTTON_LEFT)) {
			//Aggiungere logica del cambiare stato
		}

	}
	else {
		material.diffuse = original_texture;
	}

	Entity::update(seconds_elapsed);
	
	
	//--- APUNTES ---
	// Para cambiar color:
	// Si está dentro del quad: material.color = Vector4::RED //Por ejemplo
	// Para saber si hemos pulsado tenemos que mirar si está dentro y si se ha pulsado
}



//--- Para healtbars??? --- 
void EntityUI::update3D(Vector3 position3d) {
	pos3d = position3d;

	int width = Game::instance->window_width;
	int height = Game::instance->window_height;
	World* world = World::get_instance();

	visible = true;

	Vector3 pos = world->camera->project(position3d, width, height);
	if (pos.z < 0.0f || pos.z > 1.f) {
		visible = false;
	}
	else {
		pos.y = height - pos.y;
		position = Vector2(pos.x, pos.y);
	}
}