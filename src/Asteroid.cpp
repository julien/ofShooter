#include "Asteroid.h"

Asteroid::Asteroid()  { 
    angle = PI / 2;
    checkIfBreakable();
    
    int shape = floor(ofRandom(3));

    if (shape == 0) {
        vertices.push_back(ofPoint(20, 0));
        vertices.push_back(ofPoint(80, 0));
        vertices.push_back(ofPoint(100, 20));
        vertices.push_back(ofPoint(100, 50));
        vertices.push_back(ofPoint(60, 100));
        vertices.push_back(ofPoint(40, 100));
        vertices.push_back(ofPoint(50, 70));
        vertices.push_back(ofPoint(25, 90));
        vertices.push_back(ofPoint(0, 70));
        vertices.push_back(ofPoint(20, 40));
        vertices.push_back(ofPoint(0, 20));
        vertices.push_back(ofPoint(20, 0));
    } else if (shape == 1) {
        vertices.push_back(ofPoint(20,0));
        vertices.push_back(ofPoint(50,0));
        vertices.push_back(ofPoint(100,20));
        vertices.push_back(ofPoint(100,30));
        vertices.push_back(ofPoint(50,50));
        vertices.push_back(ofPoint(100,60));
        vertices.push_back(ofPoint(75,100));
        vertices.push_back(ofPoint(50,80));
        vertices.push_back(ofPoint(20,100));
        vertices.push_back(ofPoint(0,60));
        vertices.push_back(ofPoint(0,30));
        vertices.push_back(ofPoint(20,0));
    } else if (shape == 2) {
        vertices.push_back(ofPoint(25,0));
        vertices.push_back(ofPoint(50,10));
        vertices.push_back(ofPoint(75,0));
        vertices.push_back(ofPoint(100,20));
        vertices.push_back(ofPoint(70,45));
        vertices.push_back(ofPoint(100,60));
        vertices.push_back(ofPoint(65,100));
        vertices.push_back(ofPoint(30,90));
        vertices.push_back(ofPoint(20,100));
        vertices.push_back(ofPoint(0,75));
        vertices.push_back(ofPoint(10,50));
        vertices.push_back(ofPoint(0,20));
        vertices.push_back(ofPoint(25,0));
    } else if (shape == 3) {
        vertices.push_back(ofPoint(30,0));
        vertices.push_back(ofPoint(50,20));
        vertices.push_back(ofPoint(75,0));
        vertices.push_back(ofPoint(100,20));
        vertices.push_back(ofPoint(80,50));
        vertices.push_back(ofPoint(100,70));
        vertices.push_back(ofPoint(75,100));
        vertices.push_back(ofPoint(30,100));
        vertices.push_back(ofPoint(0,70));
        vertices.push_back(ofPoint(0,20));
        vertices.push_back(ofPoint(30,0));
    }

    for (int i = 0; i < vertices.size(); ++i) {
        ofVec2f(vertices[i].x, vertices[i].y);
    }
}

Asteroid::~Asteroid() { }

void Asteroid::initialize(ofPoint size, float speed, ofPoint position, ofPoint direction) {
    this->size = size;
    this->speed = speed;
    this->position = position;
    this->direction = direction;
}

void Asteroid::update(float dt) {
    rotate(rotationSpeed / 100);
    position += direction * speed * dt;
    checkBounds();
}

void Asteroid::draw() const {
    ofPolyline p;
    p.addVertexes(vertices);

    ofPushMatrix();
    glTranslatef(position.x, position.y, 0);
    glRotatef(angle / PI * 180, 0, 0, 1);

    ofScale(size.x / 60, size.y / 60, 0);
    glTranslatef(-50, -50, 0);

    p.draw();

    ofPopMatrix();
}

void Asteroid::checkIfBreakable() {
    isBreakable = (size.x > 20 && size.y > 20);
}
