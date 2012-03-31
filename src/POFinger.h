#pragma once
#include "ofMain.h"

class POFinger: ofTouchEventArgs {
	
public:
	
	POFinger(int id, float x, float y);
	POFinger(ofTouchEventArgs &touch);
	
	void update(ofTouchEventArgs &touch);
	
	int id;
	float x;
	float y;
	float accel;
	float angle;
	float prevX;
	float prevY;
    int direction;
};