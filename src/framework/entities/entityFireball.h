//#include "entityMesh.h"
//
//
//
//class EntityPlayer : public EntityMesh {
//
//public:
//
//
//    int walk_speed;
//    Vector3 velocity;
//    Vector3 position;
//    float rotation = -1.0f;
//    float cam_rotation = -1.0f;
//    bool left = false;
//    bool right = false;
//    float last_moving = 0.0f;
//    Vector3 front;
//
//    ~EntityPlayer();
//    EntityPlayer(Mesh* mesh, Material material);
//    void update(float seconds_elapsed);
//
//    void render(Camera* camera);
//    void handleCollisions(float seconds_elapsed);
//};