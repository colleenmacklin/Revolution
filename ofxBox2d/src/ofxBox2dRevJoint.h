#pragma once
#include "ofMain.h"
#include "Box2D.h"
#include "ofxBox2dUtils.h"

class ofxBox2dRevJoint {
	
public:
	
	b2World			*	world;
	b2RevoluteJoint *	rjoint;
	int					rjointType;
	bool				alive;
	
	//----------------------------------------
	ofxBox2dRevJoint();
    
    ofxBox2dRevJoint(b2World* b2world, b2Body* body1, b2Body* body2, float referenceAngle=0.0f, float lowerAngle=0.0f, float upperAngle=0.0f, float maxMotorTorque=0.0f, float motorSpeed=0.0f, bool enableLimit=false, bool enableMotor=false, bool bCollideConnected=true);
	ofxBox2dRevJoint(b2World* b2world, b2Body* body1, b2Body* body2, b2Vec2 anchor, float referenceAngle=0.0f, float lowerAngle=0.0f, float upperAngle=0.0f, float maxMotorTorque=0.0f, float motorSpeed=0.0f, bool enableLimit=false, bool enableMotor=false, bool bCollideConnected=true);

	
	//----------------------------------------
	void setWorld(b2World * w);
	void setup(b2World* b2world, b2Body* body1, b2Body* body2, float referenceAngle=0.0f, float lowerAngle=0.0f, float upperAngle=0.0f, float maxMotorTorque=0.0f, float motorSpeed=0.0f, bool enableLimit=false, bool enableMotor=false, bool bCollideConnected=true);
	void setup(b2World* b2world, b2Body* body1, b2Body* body2, b2Vec2 anchor, float referenceAngle=0.0f, float lowerAngle=0.0f, float upperAngle=0.0f, float maxMotorTorque=0.0f, float motorSpeed=0.0f, bool enableLimit=false, bool enableMotor=false, bool bCollideConnected=true);
	
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
    
    void    setMaxMotorTorque(float torque);
	float   getMotorTorque() const;
    
    bool bCollideConnected() const;

};












