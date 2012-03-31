//
//  BubbleParticle.h
//  emptyExample
//
//  Created by Colleen Macklin on 12/30/11.
//  Copyright (c) 2011 Parsons School of Design. All rights reserved.
//

#ifndef emptyExample_BubbleParticle_h
#define emptyExample_BubbleParticle_h

#import "ofMain.h"

class BubbleParticle {
	
private:
	float x;		// current y position
	float y;		// current x position
    
	int color;	
	int radius;
	int age;		// current age
	int maxAge;		// max age
	float speedX;
	float speedY;
	bool   isTouching;
public:
	BubbleParticle();
	string name;
	void update();
	void draw();
	bool dead;
    void startContact();
    void endContact();

};
#endif
