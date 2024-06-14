#include "entityUI.h"
#include "game/game.h"
#include "entityPlayer.h"
#include "framework/audio.h"
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
	material.shader->setUniform("u_boost", World::get_instance()->root_player->turbo);

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

		if (Input::isMousePressed(SDL_BUTTON_LEFT)) {
			Audio::Play("data/sounds/option.wav", 0.7f, BASS_SAMPLE_OVER_POS);
			if (button_id == PlayButton) Game::instance->goToStage(1);
			if (button_id == ContinueButton) Game::instance->goToStage(2);
			if (button_id == ControlsButton) Game::instance->goToStage(1);
			if (button_id == RestartButton) {
				Game::instance->restart();
			}
			if (button_id == ExitButton) exit(0);
		}

	}
	else {
		material.diffuse = original_texture;
	}

	Entity::update(seconds_elapsed);

}



//--- For healtbars --- 
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