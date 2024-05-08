#include "stage.h"




//PlayStage update(float seconds_elapsed)
// World::get_instance->().update(seconds_elapsed);
// 
// //Example
// if(Input::wasKeyPressed()){
// 
// Camera* camera = World::get_instance()->camera;
// 
// //Get ray direction
// Vector2 mouse_pos = Input::mouse_position;
// Vector3 ray_origin = camera->eye;
// 
// Vector3 ray_directoin = camera->getRayDirection(mouse_po.x, mouse_pos.y, Game::instance->window_width, Game::instance->window_height);
// 
// //Fill collision vector
// 
// std::vector<Vector3> collisions;
// 
// //Recorro todas las entidades del mundo
// for(Entity* e : World::get_instance()->root.children()){
// EntityCollider* collider = dynamic_cast<EntityCollider*>(e);
// if(!collider) continue;
// //En extra están todos los métodos de la librería coldet
// 
// //Como testRayCollision devuelve un bool, hay que pasarle los vectores donde guardará la colisión y las normales
// Vector3 col_point;
// Vector3 col_normal;
// 
// if(collider->mesh->testRayCollision(collider->model, ray_origin, ray_direction, col_point, col_normal)){
// collisions.push_back(col_point);
// }
// 
// }
// 
// //Generate entities
// 
// for(auto& col_point: collisions){
// Mesh* mesh = Mesh::Get("data/meshes/...");
// EntityMesh* new_mesh = new EntityMesh(mesh, {});
// new_entity.model.setTranslation(col_point);
// World::get_instance()->addEntity(new_entity);
// //En este punto estoy colocando mesh donte apunto con el ratón
// }
// 
// }
//PlayStage update(float seconds_elapsed)