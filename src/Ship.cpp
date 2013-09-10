#include "Ship.h"

Ship::Ship() {
    size.x = 15;
    size.y = 10;

    reinitialize();
}

Ship::~Ship() {
    
}

void Ship::reinitialize() {
    position.x = (ofGetWidth()  - size.x) / 2;
    position.y = (ofGetHeight() - size.y) / 2;
    angle = PI / 2;
    speed = 0;
    bulletCount = 0;
    turnLeft = turnRight = thrust = backthrust = isFiring = false;
}

void Ship::update(float dt) {
    
    if (turnLeft) {
        rotate(-0.03);
    } 
    
    if (turnRight) {
        rotate(0.03);
    }
    
    if (thrust) {
        setThrust(5);
        direction.x = cos(angle);
        direction.y = sin(angle);
    
    } else {
        setThrust(-2);
    }

    if (backthrust) {
        setThrust(-1.5);
    }


    bulletDirection.x = cos(angle);
    bulletDirection.y = sin(angle);

    if (isFiring) {
        createBullet();
    }

    fireBullet(dt);
    position += -(direction) * speed * dt;

    checkBounds();
}


void Ship::draw() {
    ofPushStyle();
    ofPushMatrix();

    ofSetColor(255, 0, 0);
    ofTranslate(position.x, position.y, 0);
    ofRotate((angle - PI / 2) / PI * 180, 0, 0, 1);
    ofRotate(-90);
    ofTranslate(-size.x / 2, -size.y / 2);
    ofLine(0, 0, size.x, size.y / 2);
    ofLine(size.x, size.y / 2, 0, size.y);
    ofLine(size.x * 0.1, size.y * 0.1, size.x * 0.1, size.y - size.y * 0.1);

    if (thrust || backthrust) {
        ofLine(size.x * 0.1, size.y * 0.1 + 2, size.x * 0.1 - size.x * 0.2, (size.y - size.y * 0.1) / 2);
        ofLine(size.x * 0.1 - size.x * 0.2, (size.y - size.y * 0.1) / 2, size.x * 0.1, size.y - size.y * 0.1 - 2);
    }

    ofPopMatrix();
    ofPopStyle();

    drawBullets();
}

void Ship::rotate(float value) {
    angle += value;
}

// TODO: why is this impl so fucking weird?
void Ship::setThrust(float value) {
    speed += value;

    if (speed > 600) {
        speed = 600;
    } else if (speed < 0.0 && !backthrust) {
        speed = 0.0;
    }

    if (backthrust) {
        speed += thrust;

        if (speed < 0) {
            speed = 0;
        }
    }
}

void Ship::checkBounds() {
    if (position.x > (float) ofGetWidth()) {
        position.x = -size.x;
    } else if (position.x + size.x < 0) {
        position.x = ofGetWidth();
    }

    if (position.y > (float) ofGetHeight()) {
        position.y = -size.y;
    } else if (position.y + size.y < 0) {
        position.y = ofGetHeight();
    }
}

void Ship::drawBullets() const {
    if (bullets.size() > 0) {
        for (unsigned int i = 0; i < bullets.size(); ++i) {
            bullets[i]->draw();
        }
    }
}

void Ship::createBullet() {
    if (bulletCount < 1) {
        Bullet *bullet = new Bullet(ofPoint(2, 2));
        bullet->initialize(this->position, this->bulletDirection);
        bullet->speed = 1200;
        bullet->lifeTime = 255;
        bullets.push_back(bullet);
        ++bulletCount;
    }
}

void Ship::fireBullet(float dt) {
    if (bullets.size() > 0) {
        for (unsigned int i = 0; i < bullets.size(); ++i) {
            bullets[i]->update(dt);
            if (bullets[i]->maxDistanceReached()) {
                bullets.erase(bullets.begin()  + i);
            }
        }
    }
}

