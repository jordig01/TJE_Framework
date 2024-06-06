#ifndef ENTITY_HEART_H
#define ENTITY_HEART_H

#include "entityMesh.h"

class EntityHeart : public EntityMesh {
public:
    EntityHeart();
    EntityHeart(Mesh* mesh, Material material);
    virtual ~EntityHeart();

    virtual void update(float seconds_elapsed) override;

protected:
    float remaining_time;
    float rotation_speed;
};

#endif // ENTITY_HEART_H
