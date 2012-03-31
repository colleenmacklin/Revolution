//
//  ParticleSystem.h
//  Revolution
//
//  Created by Colleen Macklin on 1/8/12.
//  Copyright (c) 2012 Parsons School of Design. All rights reserved.
//

#pragma once

#include "ofMain.h"
#include "Particle.h"
#include "ofxBox2d.h"

class CParticleSystem : public ofxBox2dCircle{
public:
    
    CParticleSystem(b2World* _theWorld, ofVec2f _location);
    ofVec2f origin;
    b2World* theWorld;

    void update();
    void draw();
    //void addParticle(ofxBox2d _box2d, float _posX, float _posY, float _radius);
    vector <Particle> particles;
    

};