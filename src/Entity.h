#pragma once

#include "ofMain.h"

class Entity {

public:
    Entity();
    ~Entity();

    ofPoint position;
    ofPoint direction;
    ofPoint size;

    float angle;
    float speed;

    virtual void update(float dt);
    virtual void draw();
    virtual bool checkCollision(Entity *sprite);
    virtual void checkBounds();
    virtual void rotate(float value);

};
