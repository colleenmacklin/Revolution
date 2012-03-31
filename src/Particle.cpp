//
//  Particle.cpp
//  emptyExample
//
//  Created by Colleen Macklin on 1/2/12.
//  Copyright (c) 2012 Parsons School of Design. All rights reserved.
//

#include <iostream>
#include "Particle.h"


Particle::Particle(){
    name = "Particle";
    //id set by main application
	color = 0xFFCC22;	
	radius = 5;
    
    //think about this:
    //radius = ofRandom(0,3);

    dead = false;
    
    //starting location
    x=0;
    y=0;
    
    speedX = ofRandom(0,4);
	speedY = ofRandom(0,4);

    //physics properties
    mass = 10;
    friction = 100;
    density  = .5;
    gravity = 0;
        
    isTouching = false;
    centerX = ofGetWidth()/2.0;
    centerY = ofGetHeight()/2.0;
    

    //setPhysics (density, gravity, friction);
//    this->setPosition(centerX, centerY);

    
}

//--------------------------------------------------------------
void Particle::update(){
    float myRad = this->getRadius();

    this->setRadius(myRad+=.02);
    
   // updating me
    /**
    if (this->getPosition().x > 300 || this->getPosition().x<0 ||this->getPosition().y>700 || this->getPosition().y < 0) {
        this->dead=true;
    }
    
    if (!dead) {
        move();
        if (isTouching) {
            color=0xFF0000;
            //draw();
        
        }else{
            color=0x000033;
            //draw();
        }
    }
    if(dead){
        //setPosition(-10000, -10000);
        myTimeOfDeath = ofGetElapsedTimef();
    }
    **/
//    ofPoint myPosition = this->getPosition();
//    ofPoint graveYard;
//    graveYard.set(-10000, -10000);
//    
//    if (myPosition==graveYard) {
//        float timer=ofGetElapsedTimef();
//        if (timer-myTimeOfDeath>100) {
//            this->setPosition(centerX, centerY);
//            dead=false;
//
//        }
//    }
}

//--------------------------------------------------------------
void Particle::draw(){
    //draw me
    ofFill();
    ofSetHexColor(color);
	//ofCircle(0, 200, 100);
    ofCircle( getPosition().x, getPosition().y, getRadius() );
    
}

//--------------------------------------------------------------
void Particle::move(){
    //make me move!
    int myX = getPosition().x;
    int myY = getPosition().y;
    float myRot = getRotation();
    
    myX += (myX>0 && myX<700) ? speedX : speedX*-1;
	myY += (myY>0 && myY <1024) ? speedY : speedY*-1;
    this->setPosition(myX, myY);
    this->rotation=myRot;
//    x += (x>0) ? speedX : speedX*-1;
//	y += (y>0) ? speedY : speedY*-1;
    //int myX = getPosition().x;
    //int myY = getPosition().y;
}


//--------------------------------------------------------------
void Particle::startContact(int _bodyID, string _bodyName)
{
    if (_bodyName=="particle") {
        return;
    }
    printf("%i Player was collided with \n",id);
    //color = (0xFFCC00);
    isTouching = true;

}

void Particle::endContact(int _bodyID, string _bodyName)
{
    if (_bodyName=="particle") {
        return;
    }

    printf("%i Particle collision ENDED\n", id);
    //color = (0x000000);
    isTouching = false;
    //setPosition(-10000, -10000);
    //dead=true;
    die();

}

//--------------------------------------------------------------
void Particle::die(){
    
    dead=true;
    
    //I'm dead!!
    //remove(this);
    //this->erase(this);
   // int iter=this.begin();
    
//    box2d.world->DestroyBody(_i->body);
//    iter = customParticles.erase(iter);
                //box2d.getWorld()->DestroyBody(this->body);
    			//this.erase( this );

}
  
    //one way to do this
//    vector <CustomParticle>::iterator iter = customParticles.begin();
//	while (iter != customParticles.end()) {
//		iter->draw();
//		if (iter->isDead) {
//			box2d.world->DestroyBody(iter->body);
//			iter = customParticles.erase(iter);
//		}
//		else ++iter;
//}
