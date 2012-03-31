//
//  Particle.h
//  emptyExample
//
//  Created by Colleen Macklin on 1/2/12.
//  Copyright (c) 2012 Parsons School of Design. All rights reserved.
//

#ifndef emptyExample_Particle_h
#define emptyExample_Particle_h

#include "ofMain.h"
#include "ofxBox2d.h"

class Particle : public ofxBox2dCircle{
    
public:
	Particle();
	string name;
    int id;
    int timer;
    
    int radius;

    bool isTouching;
    
	void update();
	void draw();
	bool dead;
    void startContact(int _bodyID, string _bodyName);
    void endContact(int _bodyID, string _bodyName);
    float myTimeOfDeath;

private:
    
    int centerX;
    int centerY;

	float x;		// current y position
	float y;		// current x position
    ofPoint position;   //ofpoint
    
	int color;	
    
    float speedX;
	float speedY;
    ofPoint velocity;   //ofPoint
    int rotation;
    
    ofVec2f force;
    
    int mass;
    float friction;
    float density;
    float gravity;
    
    int ticks; //for a timer, when grown, shrinks back over time -- or does it shrink when moving?
    
    void die();
    void move();

    
};

#endif
