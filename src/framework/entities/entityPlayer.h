#include "entityMesh.h"



class EntityPlayer: public EntityMesh{

public:


    int walk_speed;
    Vector3 velocity;
    Vector3 position;
    float rotation = -1.0f;
    Vector3 front = Vector3(0, 0, -1);
    

    ~EntityPlayer();
    EntityPlayer(Mesh* mesh, Material material);
    void update(float seconds_elapsed);

};