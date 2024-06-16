#include "entityMesh.h"
#include "framework/audio.h"

class CubeCollider;


enum eAnimatedState{ 
    MOVE
};


/* 
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

    int end_score = 100000;
    float score_timer = 0.0f;

    bool countdown_finished = false;
    float countdown_timer = 6.0f;
    bool initial_rotation = true;
    bool start_music = true;

    int total_lives = 3;
    int total_points = 0;
    int bullet_count = 10;
    float turbo;

    bool is_moving;

    bool is_dripping;



    std::string object_collected;

    eAnimatedState animation;

    Vector3 front;

    ~EntityPlayer();
    EntityPlayer(Mesh* mesh, Material material);
    void update(float seconds_elapsed);

    void render(Camera* camera);

    // --- Functions to handle collisions ---
    void handleCollisions(float seconds_elapsed);
    void handleCubePickup(CubeCollider* cube);
    void checkPipeCollision(float seconds_elapsed, std::vector<sCollisionData> ground_collisions);
    void checkEnemyCollision(float seconds_elapsed, std::vector<sCollisionData> ground_collisions);
   
    void addPoints(int point);
    void losePoints(int point);

    void addLife(int life);
    void loseLife(int life);

    void addBullet(int bullet);


};




// --- WHEELS ENTITY IS CONNECTED TO THE PLAYER ---

enum eTypeWheels {
    FRONT_LEFT,
    FRONT_RIGHT,
    BACK_WHEEL
};


class EntityWheels : public EntityMesh {

    public:

        eTypeWheels type_wheels;

        float rotation = -1.5f;

        bool wheels_front;

        Vector3 original_position;
        EntityWheels(Mesh* mesh, const Material& material, eTypeWheels type_wheels = BACK_WHEEL);

        void update(float seconds_elapsed);
};