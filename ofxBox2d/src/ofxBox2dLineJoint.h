#pragma once
#include "ofMain.h"
#include "Box2D.h"
#include "ofxBox2dUtils.h"

class ofxBox2dLineJoint {
	
public:
	
	b2World			*	world;
	b2LineJoint *	ljoint;
	int					ljointType;
	bool				alive;

	
	//----------------------------------------
	ofxBox2dLineJoint();
    
    ofxBox2dLineJoint(b2World* b2world, b2Body* body1, b2Body* body2, b2Vec2 axis, float lowerTranslation=0.0f, float upperTranslation=0.0f, float maxMotorForce=0.0f, float motorSpeed=0.0f, bool enableLimit=false, bool enableMotor=false, bool bCollideConnected=true);
	ofxBox2dLineJoint(b2World* b2world, b2Body* body1, b2Body* body2, b2Vec2 anchor, b2Vec2 axis, float lowerTranslation=0.0f, float upperTranslation=0.0f, float maxMotorForce=0.0f, float motorSpeed=0.0f, bool enableLimit=false, bool enableMotor=false, bool bCollideConnected=true);
	
	//----------------------------------------
	void setWorld(b2World * w);
	void setup(b2World* b2world, b2Body* body1, b2Body* body2, b2Vec2 axis, float lowerTranslation=0.0f, float upperTranslation=0.0f, float maxMotorForce=0.0f, float motorSpeed=0.0f, bool enableLimit=false, bool enableMotor=false, bool bCollideConnected=true);
	void setup(b2World* b2world, b2Body* body1, b2Body* body2, b2Vec2 anchor, b2Vec2 axis, float lowerTranslation=0.0f, float upperTranslation=0.0f, float maxMotorForce=0.0f, float motorSpeed=0.0f, bool enableLimit=false, bool enableMotor=false, bool bCollideConnected=true);
	
	//----------------------------------------
	bool isSetup();
	void draw();
	void destroy();
	
	//----------------------------------------
	// Manipulating the length can lead to non-physical behavior when the frequency is zero.
	//void  setLength(float len);
	//float getLength();
    
	
	//----------------------------------------
	ofVec2f getReactionForce(float inv_dt) const;
	b2Vec2  getReactionForceB2D(float inv_dt) const;
	float   getReactionTorque(float inv_dt) const;
    
    float getJointTranslation() const;

    float   getJointSpeed() const; //in radians per sec
    float   getJointAngle() const; //in radians
    
    bool    isLimitEnabled() const;
    void    enableLimit(bool flag);
    float   getLowerLimit() const;
	float   getUpperLimit() const;
    void    setLimits(float lower, float upper);
    
    bool    isMotorEnabled() const;
	void    enableMotor(bool flag);
	void    setMotorSpeed(float speed);
	float   getMotorSpeed() const;
    
    void    setMaxMotorForce(float torque);
    float   getMaxMotorForce() const;

	float   getMotorForce() const;
    
    bool bCollideConnected() const;
    
};












