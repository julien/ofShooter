#include "Game.h"

void Game::setup(){
    ofBackground(0);
    ofSetFrameRate(120);

    deltaTime = 0.0f;
    ship = new Ship();
    addAsteroids(4);
}

void Game::update() {
    float dt = 0.006f;
    ship->update(dt);
    for (unsigned int i = 0; i < asteroids.size(); ++i) {
        asteroids[i]->update(dt);
        asteroids[i]->checkIfBreakable();
    }
    checkCollisions();
}

void Game::draw() {
    ship->draw();
    for (unsigned int i = 0; i < asteroids.size(); ++i) {
        asteroids[i]->draw();
    }
    ofDrawBitmapString("FPS: " + ofToString(ofGetFrameRate()), ofPoint(20,20));
}

void Game::keyPressed(int key){
    handleKey(key, true);
}

void Game::keyReleased(int key){
    handleKey(key, false);
}

void Game::handleKey(int key, bool value) {
    switch (key) {
    case OF_KEY_UP:
        ship->thrust = value;
        break;
    case OF_KEY_LEFT:
        ship->turnLeft = value;
        break;
    case OF_KEY_RIGHT:
        ship->turnRight = value;
        break;
    case 'a':
        ship->isFiring = value;
        if (!value) {
            ship->bulletCount = 0;
        }
        break;
    case OF_KEY_DOWN:
        ship->backthrust = value;
        break;
    
    }
}

void Game::addAsteroids(int num) {
    ofPoint randDirection, randSize, randPos;
    int randSpeed = 0;
    float randRotation = 0.0, randValue = 0.0;

    for (int i = 0; i < num; ++i) {
        randValue = ofRandom(0.0, 1.0);
        if (randValue > 0.8) {
            randSize.x = 120;
            randSize.y = 120;
        } else if (randValue > 0.5) {
            randSize.x = 80;
            randSize.y = 80;
        } else {
            randSize.x = 40;
            randSize.y = 40;
        }

        randDirection.x = ofRandom(-1, 1);
        randDirection.y = ofRandom(-1, 1);
        normalizePoint(randDirection);
        randRotation = ofRandom(-0.5, 0.5);

        randPos.x = ofRandom(0, ofGetWidth());
        randPos.y = ofRandom(0, ofGetHeight());

        randSpeed = ofRandom(200, 400);

        Asteroid *asteroid = new Asteroid();
        asteroid->initialize(randSize, randSpeed, randPos, randDirection);
        asteroid->rotationSpeed = randRotation;
        asteroids.push_back(asteroid);
    }
}

void Game::normalizePoint(ofPoint &point) {
    float length = (float) sqrt(point.x * point.x + point.y * point.y);
    if (length > 0) {
        point.x /= length;
        point.y /= length;
    }
}

void Game::checkCollisions() {
    for (unsigned int i = 0; i < asteroids.size(); ++i) {
        if (ship->checkCollision(asteroids[i])) {
            
            
            ship->reinitialize();
        }
    }

    if (ship->bullets.size() > 0) {
        for (unsigned int i = 0; i < ship->bullets.size(); ++i) {
            for (unsigned int j = 0; j < asteroids.size(); ++j) {
                if (ship->bullets[i]->checkCollision(asteroids[j])) {
                    ship->bullets[i]->lifeTime = 0;
                    splitAsteroid(j);
                }
            }
        }
    }
}

void Game::splitAsteroid(int which) {

    if (asteroids[which]->size.x > 20 && asteroids[which]->size.y > 20) {
        for (unsigned int i = 0; i < (asteroids[which]->size.x / 40) + 1; ++i) {
            Asteroid *asteroid = new Asteroid();
            asteroid->initialize(
                asteroids[which]->size / 2, 
                asteroids[which]->speed, 
                asteroids[which]->position, 
                ofPoint(-(ofRandom(-1, 1)), 
                ofRandom(-1, 1))
            );
			asteroid->rotationSpeed = -asteroids[which]->rotationSpeed;
			asteroids.push_back(asteroid);
        }
    }

    asteroids.erase(asteroids.begin() + which);
    if (asteroids.size() == 0) {
        addAsteroids(ofRandom(4, 6));
    }
}

// void Game::mouseMoved(int x, int y) {}
// void Game::mouseDragged(int x, int y, int button)  {}
// void Game::mousePressed(int x, int y, int button)  {}
// void Game::mouseReleased(int x, int y, int button) {}
// void Game::windowResized(int w, int h) {}
// void Game::gotMessage(ofMessage msg)   {}
// void Game::dragEvent(ofDragInfo dragInfo) {}
