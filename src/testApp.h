#pragma once

#include "ofMain.h"
#include "ofxiPhone.h"
#include "ofxiPhoneExtras.h"
#include "ofxBox2d.h"
#include "Player.h"
#include "Particle.h"
#include "POFinger.h"
#include "ofTrueTypeFont.h"
//#include "Box2D.h"

// A simple little Data class. This is were
// you can store anything you want.

//class Data {
//public:
//	ofColor color;
//	string  name;
//	int		id;
//};

class MyData {
public:
	int   myID;
    string myName;
	bool  bHit;
};

class TouchInfo{
public:
    int pNum;
    float pSpeed;
    int pDir;//direction (left or right)
    
};


class testApp : public ofxiPhoneApp {
	
public:
	void setup();
	void update();
	void draw();
	void exit();
	
	void touchDown(ofTouchEventArgs &touch);
	void touchMoved(ofTouchEventArgs &touchd);
	void touchUp(ofTouchEventArgs &touch);
	void touchDoubleTap(ofTouchEventArgs &touch);
	void touchCancelled(ofTouchEventArgs &touch);

	void lostFocus();
	void gotFocus();
	void gotMemoryWarning();
	void deviceOrientationChanged(int newOrientation);
    
    void moving(int x);
    //void gotMessage(ofMessage msg);
    
	void addParticle();
    
    void addPlayer(ofxBox2d _box2d, float _posX, float _posY, float _radius, float _timer);
    
    //contact listeners
	void contactStart(ofxBox2dContactArgs &e);
	void contactEnd(ofxBox2dContactArgs &e);
    
    void addRect();
    //range mapping!
    float rangeMap(float r1min, float r1max, float r2min, float r2max, float r1val);

    int ticks; //a simple timer
    float appIphoneScale;
    
    int     NumPlayers;

    int pTouchX;
    int touchX;
    
    ofPoint pos;
    float radius;
    
    float wavelength;
	float amplitude;
    float touchVel;
    
    bool _isTouching;
    
    int tempDelta;
    int _prevX;
    int _deltaX;
    
    int centerX;
    int centerY;
    
    int angleStep;
    int P1CurrentAngle;
    
    int TWOPI;
    int touchDir;
    
    int j;
    float rem;
    float f;
    
    float length;
    
    b2Body* MyBodyA;
    b2Body* MyBodyB;
    
    float fastestCW;
    float fastestCCW;

    float                           torque;
    float                           speed;
    float                           posx;
    float                           posy;
    
    int                             numParticles;

    ofxBox2d						box2d;			  //	the box2d world    
    ofxBox2dCircle					anchor;			  //	fixed anchor
    ofxBox2dCircle					anchor2;			  //	fixed anchor

	vector		<ofxBox2dJoint>		joints;			  //	joints

    ofVec2f                         force;
    vector <ofxBox2dRevJoint>       rjoints;
	vector <Particle>               particles;
    vector <Player>                 players;
    
    vector<POFinger>                touches;  
    
    //vector <b2PrismaticJoint>       pjoints;
    //b2PrismaticJointDef             pjointDef;
    
    //b2Vec2 worldAxis;
//    b2LineJointDef                  ljointDef;
    vector <ofxBox2dLineJoint>         ljoints;
    b2Vec2  axis;
//    b2LineJoint* ljoint;
    vector<ofVec2f>   randomVals;
    float startTime;
    float lastEventTime;
    
    ofImage bkgd;
    ofImage red_arrowl;
    ofImage red_arrowr;

    ofImage blue_arrowl;
    ofImage blue_arrowr;

    float nTorque;
    float touchEventTime;
    vector <ofRectangle>                rects;
    ofTrueTypeFont                      myFont;
    ofTrueTypeFont                      myFont_small;
    TouchInfo                           t_info;
};


