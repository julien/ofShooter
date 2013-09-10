#include "Entity.h"

Entity::Entity () {}
Entity::~Entity() {}

void Entity::draw() {}

void Entity::update(float dt) {
    position += direction * speed * dt;
    checkBounds();
}

void Entity::rotate(float value) {
    angle += value;
}

bool Entity::checkCollision(Entity *sprite) {

    float dist = ofDist(position.x, position.y, sprite->position.x, sprite->position.y);
    float minDist = sprite->size.x;

    if (dist <= minDist) {
        return true;
    }

    return false;
}

void Entity::checkBounds() {
    if (position.x - size.x > (float) ofGetWidth()) {
        position.x = -size.x;
    } else if (position.x + size.x < 0) {
        position.x = ofGetWidth();
    }
    if (position.y - size.y > (float) ofGetHeight()) {
        position.y = -size.y;
    } else if (position.y + size.y < 0) {
        position.y = ofGetHeight();
    }
}