//
//  Player.cpp
//  emptyExample
//
//  Created by Colleen Macklin on 1/1/12.
//  Copyright (c) 2012 Parsons School of Design. All rights reserved.
//

#include <iostream>
#include "Player.h"


Player::Player(){
    name = "Player";
    printf("my name is: %s", name.c_str());
    //id set by main application
	radius = 10;
    
    this->setMassFromShape = true;

    myBody = this->body;

    if(myBody != NULL){
    mass=this->body->GetMass();
        printf("MASS %f", mass);
    }
    
    //starting location
    x=0;
    y=0;
    
    collideColor = 0x333300;
    
    //physics properties
    friction = 100;
    density  = .5;
    gravity = 0;

    hits = 0;
    score = 0;
    
    isTouching = false;
    
    //setPhysics (density, gravity, friction);
    
   // myBody = this->getBody();


}

//--------------------------------------------------------------
void Player::update(){
    //updating me
 if (isTouching) {
  color=collideColor;
     //draw();
//
 }else{
     color=myColor;
    //draw();

}
    
}


//--------------------------------------------------------------
void Player::draw(){
    //draw me
    ofFill();
    ofSetHexColor(color);
	//ofCircle(0, 200, 100);
    ofCircle( getPosition().x, getPosition().y, getRadius() );


}

//--------------------------------------------------------------
void Player::move(){
    //make me move!
}

//--------------------------------------------------------------
void Player::jump(){
    //make me jump!
}

//--------------------------------------------------------------
void Player::grow(){
    //grow when touching a growth particle
    //add some kind of timer, or amount of ticks to grow...for loop
    float myRad = this->getRadius();

    if (myRad > 50){
        return;
    }else{
        
        this->setRadius(myRad+=10);
        this->body->ResetMassData();
        
    }
    
    //set a limit to growth
    draw();
}

void Player::shrink(){
    float myRad = this->getRadius();
    if (myRad <= 5){
        return;
    }

    //shrink back to size
    this->setRadius(myRad-=.5);
    this->body->ResetMassData();
    //set a limit to shrinkage

}

//--------------------------------------------------------------
void Player::startContact(int _bodyID, string _bodyName)
{
    printf("Player hit ID: %i\n",_bodyID);
    //color = (0xFFCC00);
    isTouching = true;
    if(_bodyName=="particle"){
        grow();
        printf("GROWING");
    }
    if (_bodyName=="player") {
        
        shrink();
        
        printf("SHRINKING");

    }
}

void Player::endContact(int _bodyID, string _bodyName)
{
    //printf("PlayerPlayer hit ID: %f\n");
    //color = (0x0000FF);
    isTouching = false;
}

//--------------------------------------------------------------
void Player::win(){
    //I win!!
    iWin=true;
}

void Player::setColor(int _c){
    myColor = _c;
}
