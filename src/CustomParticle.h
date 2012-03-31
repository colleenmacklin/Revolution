//
//  CustomParticle.h
//  emptyExample
//
//  Created by Colleen Macklin on 12/31/11.
//  Copyright (c) 2011 Parsons School of Design. All rights reserved.
//

#ifndef emptyExample_CustomParticle_h
#define emptyExample_CustomParticle_h
// A simple little Data class. This is were
// you can store anything you want.

class Data {
public:
	ofColor color;
	string  name;
	int		id;
};

// A Custom Particle extedning the box2d circle
class CustomParticle : public ofxBox2dCircle {
    
	string myName;

public:
    float radius;
	float timer;

	void setupTheCustomData() {
		
		static int colors[] = {0xcae72b, 0xe63b8f, 0x2bb0e7};
		static string abc   = "abcdefghijklmnopqrstuvwxyz";
		
		// we are using a Data pointer because 
		// box2d needs to have a pointer not 
		// a referance
		setData(new Data());
		Data * theData = (Data*)getData();
		
		theData->id = ofRandom(0, 100);
		theData->name += abc[(int)ofRandom(0, abc.size())];
		theData->color.setHex(colors[(int)ofRandom(0, 3)]);
        
        myName = theData->name;
		printf("setting the custom data!\n");
        printf("name is: %s \n",myName.c_str());

	}
    
//    string getMyName(){
//        return myName;
//    }
	
	//void draw() {
//		//Data* theData = (Data*)getData();
//		//if(theData) {
////			
////			// Evan though we know the data object lets just 
////			// see how we can get the data out from box2d
////			// you would use this when using a contact listener
////			// or tapping into box2d's solver.
////			
////			float radius = getRadius();
////			ofPushMatrix();
////			ofTranslate(getPosition());
////			ofRotateZ(getRotation());
////			ofSetColor(theData->color);
////			ofFill();
////			ofCircle(0, 0, radius);	
////			
////			ofSetColor(255);
////			ofDrawBitmapString(theData->name, -5, 5);
////			ofPopMatrix();
////		}
//        float radius = 10;
//		ofFill();
//		ofSetHexColor(0x01b1f2);
//        ofCircle(0, 0, radius);	
//        
            //ofCircle(0, 0, 20);	
   // }
    
};


#endif
