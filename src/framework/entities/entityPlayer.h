#include "entityMesh.h"
#include "framework/audio.h"

class CubeCollider;


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

    //--- SOUNDS ---
    HCHANNEL handle_channel;
    HCHANNEL turbo_channel;
    HCHANNEL move_channel;
    HCHANNEL drift_sound_channel;
    bool was_moving; // Flag to track if the player was moving in the previous frame

    
    float collide = 0.0f;
    float collision_time = 0.0f;

    int walk_speed;
    Vector3 velocity;
    Vector3 position;
    float rotation = -1.5f;
    float cam_rotation = -1.5f;
    bool left = false;
    bool right = false;
    float last_moving = 0.0f;

    int total_lives = 3;
    int total_points = 0;
    int bullet_count = 5;
    float turbo;


    std::string object_collected;

    eAnimatedState animation;

    Vector3 front;

    ~EntityPlayer();
    EntityPlayer(Mesh* mesh, Material material);
    void update(float seconds_elapsed);

    void render(Camera* camera);
    void handleCollisions(float seconds_elapsed);

    void checkPipeCollision(float seconds_elapsed, std::vector<sCollisionData> ground_collisions);
    void checkEnemyCollision(float seconds_elapsed, std::vector<sCollisionData> ground_collisions);
    void handleCubePickup(CubeCollider* cube);
   
    //Functions to collect objects
    void addPoints(int point);
    void losePoints(int point);

    void addLife(int life);
    void loseLife(int life);

    void addBullet(int bullet);


};