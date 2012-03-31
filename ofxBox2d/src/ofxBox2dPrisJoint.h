//
//  ofxBox2dPrisJoint.h
//  emptyExample
//
//  Created by Colleen Macklin on 1/3/12.
//  Copyright (c) 2012 Parsons School of Design. All rights reserved.
//

#pragma once
#include "ofMain.h"
#include "Box2D.h"
#include "ofxBox2dUtils.h"

class ofxBox2dPrisJoint {
	
public:
	
	b2World			*	world;
	b2PrismaticJoint *	pjoint;
	int					pjointType;
	bool				alive;
	
	//----------------------------------------
	ofxBox2dPrisJoint();
    
    ofxBox2dPrisJoint(b2World* b2world, b2Body* body1, b2Body* body2, float referenceAngle=0.0f, bool enableLimit=false, float lowerTranslation=0.0, float upperTranslation=0.0, bool enableMotor=false, float maxMotorForce=0.0f, float motorSpeed=0.0f, bool bCollideConnected=true);
	ofxBox2dPrisJoint(b2World* b2world, b2Body* body1, b2Body* body2, b2Vec2 anchor,  b2Vec2 axis, float referenceAngle=0.0f, bool enableLimit=false, float lowerTranslation=0.0, float upperTranslation=0.0, bool enableMotor=false, float maxMotorForce=0.0f, float motorSpeed=0.0f, bool bCollideConnected=true);
    
	
	//----------------------------------------
	void setWorld(b2World * w);
	void setup(b2World* b2world, b2Body* body1, b2Body* body2, float referenceAngle=0.0f, bool enableLimit=false, float lowerTranslation=0.0, float upperTranslation=0.0, bool enableMotor=false, float maxMotorForce=0.0f, float motorSpeed=0.0f, bool bCollideConnected=true);
	void setup(b2World* b2world, b2Body* body1, b2Body* body2, b2Vec2 anchor,  b2Vec2 axis, float referenceAngle=0.0f, bool enableLimit=false, float lowerTranslation=0.0, float upperTranslation=0.0, bool enableMotor=false, float maxMotorForce=0.0f, float motorSpeed=0.0f, bool bCollideConnected=true);
	
	//----------------------------------------
	bool isSetup();
	void draw();
	void destroy();
	
	
	//----------------------------------------
	ofVec2f getReactionForce(float inv_dt) const;
	b2Vec2  getReactionForceB2D(float inv_dt) const;
	float   getReactionTorque(float inv_dt) const;
    /// Get the current joint translation, usually in meters.
    float   GetJointTranslation() const;
    /// Get the current joint translation speed, usually in meters per second.
    float   getJointSpeed() const; 
    
    bool    isLimitEnabled() const;
    void    enableLimit(bool flag);
    float   getLowerLimit() const;
	float   getUpperLimit() const;
    void    setLimits(float lower, float upper);
    
    bool    isMotorEnabled() const;
	void    enableMotor(bool flag);
	void    setMotorSpeed(float speed);
	float   getMotorSpeed() const;
    
    void    setMaxMotorForce(float force);
	float   getMotorForce() const;
    
};