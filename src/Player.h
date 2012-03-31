//
//  Player.h
//  emptyExample
//
//  Created by Colleen Macklin on 1/1/12.
//  Copyright (c) 2012 Parsons School of Design. All rights reserved.
//

#ifndef emptyExample_Player_h
#define emptyExample_Player_h
#include "ofMain.h"
#include "ofxBox2d.h"
//#include "Box2D.h"

class Player : public ofxBox2dCircle{
    
public:
	Player();
	string name;
    int id;
    bool isTouching;
    int fingerIndex;

    float density;
    float mass;
    
    b2Body* myBody;
    b2World* theWorld;

	void update();
	void draw();
	bool dead;
    void startContact(int _bodyID, string _bodyName);
    void endContact(int _bodyID, string _bodyName);
    void setColor(int);
    void win();
    bool iWin;

private:
	float x;		// current y position
	float y;		// current x position
    ofPoint position;   //ofpoint

	int radius;
    
    float speedX;
	float speedY;
    ofPoint velocity;   //ofPoint
    int rotation;
    
    ofVec2f force;
    
    int myColor;
    int color;
    int collideColor;
    
    float friction;
    float gravity;
    
    int hits;
    int score;
    int ticks; //for a timer, when grown, shrinks back over time -- or does it shrink when moving?
    
    
    void move();
    void grow();
    void shrink();
    void jump();

};

#endif
