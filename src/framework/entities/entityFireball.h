#include "entityMesh.h"
#include "framework/audio.h"

class EntityFireball : public EntityMesh {


public:

	HCHANNEL shoot_channel;

	EntityFireball();
	EntityFireball(Mesh* mesh, Material material);
	~EntityFireball();

	Vector3 direction; 

	void update(float seconds_elapsed);

	bool testCollisionWithEnemy();

};