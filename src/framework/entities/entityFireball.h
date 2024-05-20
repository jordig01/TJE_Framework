#include "entityMesh.h"

class EntityFireball : public EntityMesh {


public:

	EntityFireball();
	EntityFireball(Mesh* mesh, Material material);
	~EntityFireball();

	void update(float seconds_elapsed);



};