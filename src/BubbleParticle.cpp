//
//  BubbleParticle.cpp
//  emptyExample
//
//  Created by Colleen Macklin on 12/30/11.
//  Copyright (c) 2011 Parsons School of Design. All rights reserved.
//

#include <iostream>
#include "BubbleParticle.h"

BubbleParticle::BubbleParticle()
{
	x = ofRandomf();
	y = ofRandomf();
	speedX = ofRandom(0,4);
	speedY = ofRandom(0,4);
	radius = ofRandom(0,3);
	color = 0xff0000;	
	
	age = 0;
	dead = false;
	maxAge = ofRandom(0, 50)+250;
    name = "bubble";
    isTouching = false;
    
  //  body->SetUserData(this);
}

void BubbleParticle::startContact()
{
    printf("Bubble!!!!!!!!\n");
    color = (0xFFCC00);
    isTouching = true;
}

void BubbleParticle::endContact()
{
    printf("Bubble!!!!!!!!ENDED\n");
    color = (0x000000);
    isTouching = false;
}


void BubbleParticle::update()
{
	age++;
	x += (x>0) ? speedX : speedX*-1;
	y += (y>0) ? speedY : speedY*-1;
	if (age >= maxAge) dead = true;
    if (isTouching) {
        color=0xFFCC00;
        draw();
    }
}


void BubbleParticle::draw()
{
    ofFill();
    ofSetHexColor(0x01b1f2);
	ofCircle(100, 100, 100);
}
