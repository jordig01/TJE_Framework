#pragma once

#include "entityCollider.h"
#include "framework/extra/pathfinder/PathFinder.h"
#include "framework/extra/pathfinder/Dijkstra.h"

#include "graphics/material.h"


class Camera;

enum eFSMStates {
	PATROL,
	SEARCH_PLAYER,
	ATTACK
};

struct WayPoint : public DijkstraNode
{
	WayPoint() {};
	WayPoint(const Vector3& position) : position(position) {};

	void addLink(WayPoint* waypoint, float distance) {
		addChild(waypoint, distance);
		waypoint->addChild(this, distance);
	}

	Vector3 position;
};

class EntityAI : public EntityCollider {
	
	float fov = 0.0f;

	bool walk_forwards = true;
	int waypoint_index = 0;

	float max_rotation_angle = 0.25f; // Ángulo máximo de oscilación
	float current_rotation_angle = 0.0f; // Ángulo de rotación actual
	float rotation_speed = 0.5f; // Velocidad de rotación en grados por segundo
	bool rotating_forward = true; // Dirección de la rotación

	eFSMStates state = PATROL;


public:

	std::vector<WayPoint> path;

	Vector3 original_position;

	EntityAI() {};
	EntityAI(Mesh* mesh, const Material& material, const std::string& name = "");
	~EntityAI();

	void render(Camera* camera) override;
	void update(float seconds_elapsed) override;

	bool inLineOfSight(const Vector3& position);
	void lookAtTarget(const Vector3& position, float seconds_elapsed);
	void followPath(float seconds_elapsed);


};
