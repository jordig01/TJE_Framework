#include "entityMesh.h"

class EntityFireball : public EntityMesh {


public:

	EntityFireball();
	EntityFireball(Mesh* mesh, Material material);
	~EntityFireball();

	Vector3 direction; 

	void update(float seconds_elapsed);



};