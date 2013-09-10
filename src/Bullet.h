#pragma once

#include "Entity.h"

class Bullet : public Entity {
public:
    Bullet(ofPoint size);
    ~Bullet();

    virtual void update(float dt);
    virtual void draw();
    virtual void checkBounds();

    void initialize(ofPoint origin, ofPoint dir);
    bool maxDistanceReached();
    float getDistance();
    float fireDist;
    float lifeTime;
    ofPoint tmpOrigin;
};
