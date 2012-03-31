/*
 *  ofxBox2dPrisJoint.cpp
 *  revjointExample
 *
 *  Created by Colleen Macklin on 12/27/11.
 *  Copyright 2011 Colleen Macklin. All rights reserved.
 *
 */

#include "ofxBox2dPrisJoint.h"

//----------------------------------------
ofxBox2dPrisJoint::ofxBox2dPrisJoint() {
	world = NULL;
	alive = false;
}

//----------------------------------------
ofxBox2dPrisJoint::ofxBox2dPrisJoint(b2World* b2world, b2Body* body1, b2Body* body2, float referenceAngle, bool enableLimit, float lowerTranslation, float upperTranslation, bool enableMotor, float maxMotorForce, float motorSpeed, bool bCollideConnected) {
	ofxBox2dPrisJoint();
	setup(b2world, body1, body2, referenceAngle, enableLimit, lowerTranslation, upperTranslation, enableMotor, maxMotorForce, motorSpeed, bCollideConnected);
}

//----------------------------------------
ofxBox2dPrisJoint::ofxBox2dPrisJoint(b2World* b2world, b2Body* body1, b2Body* body2, b2Vec2 anchor,  b2Vec2 axis, float referenceAngle, bool enableLimit, float lowerTranslation, float upperTranslation, bool enableMotor, float maxMotorForce, float motorSpeed, bool bCollideConnected) {
	ofxBox2dPrisJoint();
	setup(b2world, body1, body2, anchor, axis, referenceAngle, enableLimit, lowerTranslation, upperTranslation, enableMotor, maxMotorForce, motorSpeed, bCollideConnected);
}

//----------------------------------------
void ofxBox2dPrisJoint::setup(b2World* b2world, b2Body* body1, b2Body* body2, float referenceAngle, bool enableLimit, float lowerTranslation, float upperTranslation, bool enableMotor, float maxMotorForce, float motorSpeed, bool bCollideConnected) {
	b2Vec2 a;
	a = body1->GetWorldCenter();
    
    //HERE's WHERE I GOT STUCK
//    b2Vec2 ax;
//    ax = body1->GetLocalVector(axis);
	
//	setup(b2world, body1, body2, a, axis, referenceAngle, enableLimit, lowerTranslation, upperTranslation, enableMotor, maxMotorForce, motorSpeed, bCollideConnected);
}

//----------------------------------------
//void ofxBox2dPrisJoint::setup(b2World* b2world, b2Body* body1, b2Body* body2, b2Vec2 anchor, b2Vec2 axis, float referenceAngle, float lowerAngle, float upperAngle, float maxMotorTorque, float motorSpeed, bool enableLimit, bool enableMotor, bool bCollideConnected) {
//	setWorld(b2world);
//	b2RevoluteJointDef pjointDef;
//	pjointDef.Initialize(body1, body2, anchor, axis);
//    pjointDef.referenceAngle    = referenceAngle;
//    pjointDef.lowerAngle        = lowerAngle;
//    pjointDef.upperAngle        = upperAngle;
//    pjointDef.maxMotorTorque    = maxMotorTorque;
//    pjointDef.motorSpeed        = motorSpeed;
//    pjointDef.enableLimit       = enableLimit;
//    pjointDef.enableMotor       = enableMotor;
//	pjointDef.collideConnected	= bCollideConnected;
//	pjoint						= (b2PrismaticJoint*)world->CreateJoint(&pjointDef);
//	
//	alive						= true;
//}

//----------------------------------------
void ofxBox2dPrisJoint::setWorld(b2World* w) {
	if(w == NULL) {
		ofLog(OF_LOG_NOTICE, "ofxBox2dRevJoint :: setWorld : - box2d world needed -");	
		return;
	}
	world = w;
}

//----------------------------------------
bool ofxBox2dPrisJoint::isSetup() {
	if (world == NULL) {
		ofLog(OF_LOG_NOTICE, "ofxBox2dRevJoint :: world must be set!");
		return false;
	}
	if (pjoint == NULL) {
		ofLog(OF_LOG_NOTICE, "ofxBox2dRevJoint :: setup function must be called!");
		return false;
	}
	return true;
}


//----------------------------------------
void ofxBox2dPrisJoint::draw() {
	if(!alive) return;
	
	b2Vec2 p1 = pjoint->GetAnchorA();
	b2Vec2 p2 = pjoint->GetAnchorB();
	
	p1 *= OFX_BOX2D_SCALE;
	p2 *= OFX_BOX2D_SCALE;
	ofLine(p1.x, p1.y, p2.x, p2.y);
}

//----------------------------------------
void ofxBox2dPrisJoint::destroy() {
	if (!isSetup()) return;
	world->DestroyJoint(pjoint);
	pjoint = NULL;
	alive = false;
}


//----------------------------------------
void ofxBox2dPrisJoint::enableLimit(bool flag){
    return pjoint->EnableLimit(flag);
}

bool ofxBox2dPrisJoint::isLimitEnabled() const{
    return (bool)pjoint->IsLimitEnabled();
}
//----------------------------------------

void ofxBox2dPrisJoint::enableMotor(bool flag){
    return pjoint->EnableMotor(flag);
}

bool ofxBox2dPrisJoint::isMotorEnabled() const{
    return pjoint->IsMotorEnabled();
}

//----------------------------------------
void ofxBox2dPrisJoint::setMotorSpeed(float speed) {
	pjoint->SetMotorSpeed((float32)speed);
}
float ofxBox2dPrisJoint::getMotorSpeed() const{
	return (float)pjoint->GetMotorSpeed();
}

//----------------------------------------
void ofxBox2dPrisJoint::setMaxMotorForce(float force) {
	pjoint->SetMaxMotorForce((float32)force);
}
float ofxBox2dPrisJoint::getMotorForce() const{
	return (float)pjoint->GetMotorForce();
}

//----------------------------------------
ofVec2f ofxBox2dPrisJoint::getReactionForce(float inv_dt) const {
	b2Vec2 vec = getReactionForceB2D(inv_dt);
	return ofVec2f(vec.x, vec.y);
}
b2Vec2 ofxBox2dPrisJoint::getReactionForceB2D(float inv_dt) const {
	return pjoint->GetReactionForce(inv_dt);
}
float ofxBox2dPrisJoint::getReactionTorque(float inv_dt) const {
	return (float)pjoint->GetReactionTorque(inv_dt);
}

float ofxBox2dPrisJoint::getJointSpeed() const {
	return (float)pjoint->GetJointSpeed();
}

//float ofxBox2dPrisJoint::getJointAngle() const {
//	return (float)pjoint->GetJointAngle();
//}




