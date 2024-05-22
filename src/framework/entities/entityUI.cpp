#include "entityUI.h"

EntityUI::EntityUI(Vector2 pos, Vector2 size, const Material& material, eButtonId button_id = UndefinedButton, ) {
	position = pos;
	this->size = size;
	this->button_id = button_id;

	mesh = new Mesh();
	mesh->createQuad(pos.x, pos.y, size.x, size.y, true);

	this->material = material;

	if () {

	}

};

void EntityUI::render() {
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
}

EntityUI::update(seconds_elapsed) {
	//Para cambiar color:
	// Si está dentro del quad: material.color = Vector4::RED //Por ejemplo
	// 
	// Para saber si hemos pulsado tenemos que mirar si está dentro y si se ha pulsado
	// 
	//
}