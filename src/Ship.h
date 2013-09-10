#pragma once

#include "Entity.h"
#include "Bullet.h"

class Ship : public Entity {
public:
    Ship();
    ~Ship();

    virtual void update(float dt);
    virtual void draw();
    virtual void checkBounds();
    virtual void rotate(float value);
    virtual void setThrust(float value);
    virtual void reinitialize();

    void drawBullets() const;
    void createBullet();
    void fireBullet(float dt);

    vector<Bullet*> bullets;
    ofPoint bulletDirection;
    int bulletCount;

    bool turnLeft, turnRight, thrust, backthrust, isFiring;
};
