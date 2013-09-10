#pragma once

#include "ofMain.h"
#include "Ship.h"
#include "Asteroid.h"

class Game : public ofBaseApp {
    float score;
    Ship *ship;
    float deltaTime;

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);

	// void mouseMoved(int x, int y );
	// void mouseDragged(int x, int y, int button);
	// void mousePressed(int x, int y, int button);
	// void mouseReleased(int x, int y, int button);
	// void windowResized(int w, int h);
	// void dragEvent(ofDragInfo dragInfo);
	// void gotMessage(ofMessage msg);


    void handleKey(int key, bool value);
    void addAsteroids(int num);
    void normalizePoint(ofPoint &point);
    void checkCollisions();
    void splitAsteroid(int which);		

    vector<Asteroid*> asteroids;
};
