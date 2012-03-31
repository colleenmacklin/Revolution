/*
 *  ofxBox2dRevJoint.cpp
 *  revjointExample
 *
 *  Created by Colleen Macklin on 12/27/11.
 *  Copyright 2011 Colleen Macklin. All rights reserved.
 *
 */

#include "ofxBox2dRevJoint.h"

//----------------------------------------
ofxBox2dRevJoint::ofxBox2dRevJoint() {
	world = NULL;
	alive = false;
}

//----------------------------------------
ofxBox2dRevJoint::ofxBox2dRevJoint(b2World* b2world, b2Body* body1, b2Body* body2, float referenceAngle, float lowerAngle, float upperAngle, float maxMotorTorque, float motorSpeed, bool enableLimit, bool enableMotor, bool bCollideConnected) {
	ofxBox2dRevJoint();
	setup(b2world, body1, body2, referenceAngle, lowerAngle, upperAngle, maxMotorTorque, motorSpeed, enableLimit, enableMotor, bCollideConnected);
}

//----------------------------------------
ofxBox2dRevJoint::ofxBox2dRevJoint(b2World* b2world, b2Body* body1, b2Body* body2, b2Vec2 anchor, float referenceAngle, float lowerAngle, float upperAngle, float maxMotorTorque, float motorSpeed, bool enableLimit, bool enableMotor, bool bCollideConnected) {
	ofxBox2dRevJoint();
	setup(b2world, body1, body2, anchor, referenceAngle, lowerAngle, upperAngle, maxMotorTorque, motorSpeed, enableLimit, enableMotor, bCollideConnected);
}

//----------------------------------------
void ofxBox2dRevJoint::setup(b2World* b2world, b2Body* body1, b2Body* body2, float referenceAngle, float lowerAngle, float upperAngle, float maxMotorTorque, float motorSpeed, bool enableLimit, bool enableMotor, bool bCollideConnected) {
	b2Vec2 a;
	a = body1->GetWorldCenter();
    
	
	setup(b2world, body1, body2, a, referenceAngle, lowerAngle, upperAngle, maxMotorTorque, motorSpeed, enableLimit, enableMotor, bCollideConnected);
}

//----------------------------------------
void ofxBox2dRevJoint::setup(b2World* b2world, b2Body* body1, b2Body* body2, b2Vec2 anchor, float referenceAngle, float lowerAngle, float upperAngle, float maxMotorTorque, float motorSpeed, bool enableLimit, bool enableMotor, bool bCollideConnected) {
	setWorld(b2world);
	b2RevoluteJointDef rjointDef;
	rjointDef.Initialize(body1, body2, anchor);
    rjointDef.referenceAngle    = referenceAngle;
    rjointDef.lowerAngle        = lowerAngle;
    rjointDef.upperAngle        = upperAngle;
    rjointDef.maxMotorTorque    = maxMotorTorque;
    rjointDef.motorSpeed        = motorSpeed;
    rjointDef.enableLimit       = enableLimit;
    rjointDef.enableMotor       = enableMotor;
	rjointDef.collideConnected	= bCollideConnected;
	rjoint						= (b2RevoluteJoint*)world->CreateJoint(&rjointDef);
	
	alive						= true;
}

//----------------------------------------
void ofxBox2dRevJoint::setWorld(b2World* w) {
	if(w == NULL) {
		ofLog(OF_LOG_NOTICE, "ofxBox2dRevJoint :: setWorld : - box2d world needed -");	
		return;
	}
	world = w;
}

//----------------------------------------
bool ofxBox2dRevJoint::isSetup() {
	if (world == NULL) {
		ofLog(OF_LOG_NOTICE, "ofxBox2dRevJoint :: world must be set!");
		return false;
	}
	if (rjoint == NULL) {
		ofLog(OF_LOG_NOTICE, "ofxBox2dRevJoint :: setup function must be called!");
		return false;
	}
	return true;
}


//----------------------------------------
void ofxBox2dRevJoint::draw() {
	if(!alive) return;
	
	b2Vec2 p1 = rjoint->GetAnchorA();
	b2Vec2 p2 = rjoint->GetAnchorB();
	
	p1 *= OFX_BOX2D_SCALE;
	p2 *= OFX_BOX2D_SCALE;
	ofLine(p1.x, p1.y, p2.x, p2.y);
}

//----------------------------------------
void ofxBox2dRevJoint::destroy() {
	if (!isSetup()) return;
	world->DestroyJoint(rjoint);
	rjoint = NULL;
	alive = false;
}


//----------------------------------------
void ofxBox2dRevJoint::enableLimit(bool flag){
    return rjoint->EnableLimit(flag);
}

bool ofxBox2dRevJoint::isLimitEnabled() const{
    return (bool)rjoint->IsLimitEnabled();
}

//void ofxBox2dRevJoint::bCollideConnected()(bool flag){
//    return rjoint->CollideConnected(flag);
//}
//
//bool ofxBox2dRevJoint::bCollideConnected() const{
//    return (bool)rjoint->m_collideConnected();
//}

//----------------------------------------

void ofxBox2dRevJoint::enableMotor(bool flag){
    return rjoint->EnableMotor(flag);
}

bool ofxBox2dRevJoint::isMotorEnabled() const{
    return rjoint->IsMotorEnabled();
}

//----------------------------------------
void ofxBox2dRevJoint::setMotorSpeed(float speed) {
	rjoint->SetMotorSpeed((float32)speed);
}
float ofxBox2dRevJoint::getMotorSpeed() const{
	return (float)rjoint->GetMotorSpeed();
}

//----------------------------------------
void ofxBox2dRevJoint::setMaxMotorTorque(float torque) {
	rjoint->SetMaxMotorTorque((float32)torque);
}
float ofxBox2dRevJoint::getMotorTorque() const{
	return (float)rjoint->GetMotorTorque();
}

//----------------------------------------
ofVec2f ofxBox2dRevJoint::getReactionForce(float inv_dt) const {
	b2Vec2 vec = getReactionForceB2D(inv_dt);
	return ofVec2f(vec.x, vec.y);
}
b2Vec2 ofxBox2dRevJoint::getReactionForceB2D(float inv_dt) const {
	return rjoint->GetReactionForce(inv_dt);
}
float ofxBox2dRevJoint::getReactionTorque(float inv_dt) const {
	return (float)rjoint->GetReactionTorque(inv_dt);
}

float ofxBox2dRevJoint::getJointSpeed() const {
	return (float)rjoint->GetJointSpeed();
}

float ofxBox2dRevJoint::getJointAngle() const {
	return (float)rjoint->GetJointAngle();
}




