#include "entityMesh.h"


enum eAnimatedState{ //En nuesto caso rotar derecha izquierda  estado Handle
    MOVE
};


/*
* CALLBACK usare per mettere audio
* 
* 
* animator.addCallback [&](float t){
* SoundModule.playSoung("gyusj")
* }, 0.5f); //segundos con f y frame numero entero 
*/

class EntityPlayer : public EntityMesh {

public:


    int walk_speed;
    Vector3 velocity;
    Vector3 position;
    float rotation = -1.0f;
    float cam_rotation = -1.0f;
    bool left = false;
    bool right = false;
    float last_moving = 0.0f;

    int total_lives = 3;
    int total_points = 0;

    eAnimatedState animation;

    Vector3 front;

    ~EntityPlayer();
    EntityPlayer(Mesh* mesh, Material material);
    void update(float seconds_elapsed);

    void render(Camera* camera);
    void handleCollisions(float seconds_elapsed);

    void addPoints(int point);
    void losePoints(int point);

    void addLife(int life);
    void loseLife(int life);
};