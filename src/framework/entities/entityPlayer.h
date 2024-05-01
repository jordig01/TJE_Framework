#include "entityMesh.h"



class EntityPlayer: public EntityMesh{

public:


    int walk_speed;
    Vector3 velocity;
    Vector3 position;
    

    ~EntityPlayer();
    EntityPlayer(Mesh* mesh, Material material);
    void update(float seconds_elapsed);

};