/*
 *  ofxBox2dLineJoint.cpp
 *  revjointExample
 *
 *  Created by Colleen Macklin on 12/27/11.
 *  Copyright 2011 Colleen Macklin. All rights reserved.
 *
 */

#include "ofxBox2dLineJoint.h"

//----------------------------------------
ofxBox2dLineJoint::ofxBox2dLineJoint() {
	world = NULL;
	alive = false;
}

//----------------------------------------
ofxBox2dLineJoint::ofxBox2dLineJoint(b2World* b2world, b2Body* body1, b2Body* body2, b2Vec2 axis, float lowerTranslation, float upperTranslation, float maxMotorForce, float motorSpeed, bool enableLimit, bool enableMotor, bool bCollideConnected) {
	ofxBox2dLineJoint();
	setup(b2world, body1, body2, axis, lowerTranslation, upperTranslation, maxMotorForce, motorSpeed, enableLimit, enableMotor, bCollideConnected);
}

//----------------------------------------
ofxBox2dLineJoint::ofxBox2dLineJoint(b2World* b2world, b2Body* body1, b2Body* body2, b2Vec2 anchor, b2Vec2 axis, float lowerTranslation, float upperTranslation, float maxMotorForce, float motorSpeed, bool enableLimit, bool enableMotor, bool bCollideConnected) {
	ofxBox2dLineJoint();
	setup(b2world, body1, body2, anchor, axis, lowerTranslation, upperTranslation, maxMotorForce, motorSpeed, enableLimit, enableMotor, bCollideConnected);
}

//----------------------------------------
void ofxBox2dLineJoint::setup(b2World* b2world, b2Body* body1, b2Body* body2, b2Vec2 axis, float lowerTranslation, float upperTranslation, float maxMotorForce, float motorSpeed, bool enableLimit, bool enableMotor, bool bCollideConnected) {
	b2Vec2 a;
	a = body1->GetWorldCenter();
    
	
	setup(b2world, body1, body2, a, axis, lowerTranslation, upperTranslation, maxMotorForce, motorSpeed, enableLimit, enableMotor, bCollideConnected);
}

//----------------------------------------
void ofxBox2dLineJoint::setup(b2World* b2world, b2Body* body1, b2Body* body2, b2Vec2 anchor, b2Vec2 axis, float lowerTranslation, float upperTranslation, float maxMotorForce, float motorSpeed, bool enableLimit, bool enableMotor, bool bCollideConnected) {
	setWorld(b2world);
	b2LineJointDef ljointDef;
	ljointDef.Initialize(body1, body2, anchor, axis);
    ljointDef.lowerTranslation        = lowerTranslation;
    ljointDef.upperTranslation        = upperTranslation;
    ljointDef.maxMotorForce    = maxMotorForce;
    ljointDef.motorSpeed        = motorSpeed;
    ljointDef.enableLimit       = enableLimit;
    ljointDef.enableMotor       = enableMotor;
	ljointDef.collideConnected	= bCollideConnected;
	ljoint						= (b2LineJoint*)world->CreateJoint(&ljointDef);
	
	alive						= true;
}

//----------------------------------------
void ofxBox2dLineJoint::setWorld(b2World* w) {
	if(w == NULL) {
		ofLog(OF_LOG_NOTICE, "ofxBox2dLineJoint :: setWorld : - box2d world needed -");	
		return;
	}
	world = w;
}

//----------------------------------------
bool ofxBox2dLineJoint::isSetup() {
	if (world == NULL) {
		ofLog(OF_LOG_NOTICE, "ofxBox2dLineJoint :: world must be set!");
		return false;
	}
	if (ljoint == NULL) {
		ofLog(OF_LOG_NOTICE, "ofxBox2dLineJoint :: setup function must be called!");
		return false;
	}
	return true;
}


//----------------------------------------
void ofxBox2dLineJoint::draw() {
	if(!alive) return;
	
	b2Vec2 p1 = ljoint->GetAnchorA();
	b2Vec2 p2 = ljoint->GetAnchorB();
	
	p1 *= OFX_BOX2D_SCALE;
	p2 *= OFX_BOX2D_SCALE;
	ofLine(p1.x, p1.y, p2.x, p2.y);
}

//----------------------------------------
void ofxBox2dLineJoint::destroy() {
	if (!isSetup()) return;
	world->DestroyJoint(ljoint);
	ljoint = NULL;
	alive = false;
}


//----------------------------------------
void ofxBox2dLineJoint::enableLimit(bool flag){
    return ljoint->EnableLimit(flag);
}

bool ofxBox2dLineJoint::isLimitEnabled() const{
    return (bool)ljoint->IsLimitEnabled();
}

//void ofxBox2dLineJoint::bCollideConnected()(bool flag){
//    return ljoint->CollideConnected(flag);
//}
//
//bool ofxBox2dLineJoint::bCollideConnected() const{
//    return (bool)ljoint->m_collideConnected();
//}

//----------------------------------------

void ofxBox2dLineJoint::enableMotor(bool flag){
    return ljoint->EnableMotor(flag);
}

bool ofxBox2dLineJoint::isMotorEnabled() const{
    return ljoint->IsMotorEnabled();
}

//----------------------------------------
void ofxBox2dLineJoint::setMotorSpeed(float speed) {
	ljoint->SetMotorSpeed((float32)speed);
}
float ofxBox2dLineJoint::getMotorSpeed() const{
	return (float)ljoint->GetMotorSpeed();
}

//----------------------------------------
void ofxBox2dLineJoint::setMaxMotorForce(float force) {
	ljoint->SetMaxMotorForce((float32)force);
}
float ofxBox2dLineJoint::getMotorForce() const{
	return (float)ljoint->GetMotorForce();
}

//----------------------------------------
ofVec2f ofxBox2dLineJoint::getReactionForce(float inv_dt) const {
	b2Vec2 vec = getReactionForceB2D(inv_dt);
	return ofVec2f(vec.x, vec.y);
}
b2Vec2 ofxBox2dLineJoint::getReactionForceB2D(float inv_dt) const {
	return ljoint->GetReactionForce(inv_dt);
}
float ofxBox2dLineJoint::getReactionTorque(float inv_dt) const {
	return (float)ljoint->GetReactionTorque(inv_dt);
}

float ofxBox2dLineJoint::getJointSpeed() const {
	return (float)ljoint->GetJointSpeed();
}