#pragma once

#include "Entity.h"

class Asteroid : public Entity {
public:
    Asteroid();
    ~Asteroid();

    virtual void initialize(ofPoint size, float speed, ofPoint position, ofPoint direction);
    virtual void draw() const;
    virtual void update(float dt);
    void checkIfBreakable();
    bool isBreakable;
    float rotationSpeed;
    vector<ofPoint> vertices;
};


