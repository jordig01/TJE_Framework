//#include "entityMesh.h"
//#include "framework/camera.h"
//#include "graphics/material.h"
//
//
//
//EntityMesh::EntityMesh(Mesh* mesh, Material material)
//{
//	this->mesh = mesh;
//	this->material = material;
//
//}
//
//void EntityMesh::render() {
//
//	// Get the last camera that was activated 
//	Camera* camera = Camera::current;
//	
//
//
//	// Enable shader and pass uniforms 
//	material.shader->enable();
//	material.shader->setUniform("u_color", material.color);
//	material.shader->setUniform("u_viewproj", camera->viewprojection_matrix);
//
//	if (material.diffuse) {
//		material.shader->setTexture("u_texture", material.diffuse, 0);
//	}
//
//
//	//si no estoy instanciando le envio mi model
//	material.shader->setUniform("u_model", getGlobalMatrix());
//
//	//si instanciado renderInstance
//
//
//	// Render the mesh using the shader
//	mesh->render(GL_TRIANGLES);
//
//	// Disable shader after finishing rendering
//	material.shader->disable();
//
//	//render(camera) pero podria hacer mi Entity::render(camera);
//};
//
//
//void EntityMesh::update(float seconds_elapsed) {
//
//	//for i  i< children.size(); ++i
//	//children[i]->update(seconds_elapsed)
//	//otra opción Entity::render(camera)
//};
