#include "entityAI.h"
#include "game/world.h"
#include "graphics/shader.h"
#include "entityMesh.h"
#include "entityPlayer.h"
#include "framework/camera.h"

#define RENDER_DEBUG


EntityAI::EntityAI(Mesh* mesh, const Material& material, const std::string& name)
{
	this->mesh = mesh;
	this->material = material;
}

EntityAI::~EntityAI()
{

}

void EntityAI::render(Camera* camera)
{
#ifdef RENDER_DEBUG
	Entity* target = (Entity*)World::get_instance()->root_player;
	bool in_sight = inLineOfSight(target->getGlobalMatrix().getTranslation());

	std::vector<Vector3> vertices;

	Vector3 pos = model.getTranslation();
	Vector3 front = model.frontVector();

	vertices.push_back(pos);
	vertices.push_back(pos + front);

	Matrix44 m;
	m.setRotation(fov * 0.5f * DEG2RAD, Vector3::UP);

	vertices.push_back(pos);
	vertices.push_back(pos + m.rotateVector(front));

	Mesh mesh;
	mesh.vertices = vertices;

	Shader* shader = Shader::Get("data/shaders/basic.vs", "data/shaders/flat.fs");

	shader->enable();
	shader->setUniform("u_color", in_sight ? Vector4(1.f, 0.f, 0.f, 1.f) : Vector4(0.f, 1.f, 0.f, 1.f));
	shader->setUniform("u_viewprojection", camera->viewprojection_matrix);
	shader->setUniform("u_model", Matrix44());

	mesh.render(GL_LINE_STRIP);


#endif RENDER_DEBUG
		EntityMesh::render(camera);
}

void EntityAI::update(float seconds_elapsed)
{
	
	Vector3 player_pos = World::get_instance()->root_player->position;

	if (state == PATROL) {
		followPath(seconds_elapsed);

		bool in_sight = inLineOfSight(player_pos);

		if (in_sight) {
			state = SEARCH_PLAYER;
		}
	}

	EntityCollider::update(seconds_elapsed);
}

bool EntityAI::inLineOfSight(const Vector3& position)
{
	Vector3 offset = Vector3(0.f, 0.1f, 0.f);
	Vector3 origin = model.getTranslation() + offset;
	Vector3 target = position + offset;
	Vector3 to_target = target - origin;


	float max_distance = 10.f;

	float distance = to_target.length();
	to_target.normalize();
	Vector3 front = model.frontVector();
	front.normalize();

	//1st step: Vision Cone
	float angle = model.getYawRotationToAimTo(target);
	float half_fov_radians = fov * 0.5f * DEG2RAD;

	if (fabsf(angle) < half_fov_radians && distance < max_distance)
	{
		// 2nd step: check obstacles
		sCollisionData data = World::get_instance()->ray_cast(origin, to_target, eCollisionFilter::ALL ^ eCollisionFilter::ENEMY, distance);
		return !data.collided;
	}

	return false;
}

void EntityAI::lookAtTarget(const Vector3& position, float seconds_elapsed)
{
	//Rotate model to look at position
	float angle = model.getYawRotationToAimTo(position);
	float rotationSpeed = 4.0f * seconds_elapsed;
	model.rotate(angle * rotationSpeed, Vector3::UP);
}


void EntityAI::followPath(float seconds_elapsed)
{
	//path = World::get_instance()->waypoints;
	if (path.size()) {
		Vector3 origin = model.getTranslation();
		Vector3 target = path[waypoint_index].position;

		lookAtTarget(target, seconds_elapsed);

		model.translate(0.f, 0.f, seconds_elapsed * 5.f);
		
		float distance_to_target = (target - origin).length();
		if (distance_to_target < 0.1f) {
			if (walk_forwards && waypoint_index + 1 == path.size() || !walk_forwards && waypoint_index - 1 < 0) {
				walk_forwards = !walk_forwards;
			}
			waypoint_index += (walk_forwards ? 1 : -1);
		}
	}
}

