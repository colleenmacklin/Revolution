#include "POFinger.h"

POFinger::POFinger(int _id, float _x, float _y){
	id = _id;
	x = _x;
	y = _y;
	
	prevX = x;
	prevY = y;
	accel = 0;
	angle = 0;
    direction=0;

}

POFinger::POFinger(ofTouchEventArgs &touch){
	id = touch.id;
	x = touch.x;
	y = touch.y;
	
	prevX = x;
	prevY = y;
	accel = 0;
	angle = 0;
    direction=0;
}

void POFinger::update(ofTouchEventArgs &touch){
	x = touch.x;
	y = touch.y;
    
	accel = ofDist(prevX, prevY, x, y);			// acceleration is the distance between the previous point and this point
    

	angle = atan2(prevY - y, prevX - x) + PI;	// atan2 calculates num of radians
    
    if(x - prevX < 0){
    direction = (-1);
    }
    
    if(x - prevX > 0){
        direction = 1;
    }
    
	prevX = x;
	prevY = y;
}