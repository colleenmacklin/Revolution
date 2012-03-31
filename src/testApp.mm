#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){
	// register touch events
	ofxRegisterMultitouch(this);
	
	// initialize the accelerometer
	ofxAccelerometer.setup();
	
	//iPhoneAlerts will be sent to this.
	ofxiPhoneAlerts.addListener(this);
	
	//If you want a landscape oreintation 
	//ofxiPhoneSetOrientation(OFXIPHONE_ORIENTATION_LANDSCAPE_RIGHT);
    
    appIphoneScale = 1.0;
    
	//ofSetFrameRate(60);
	ofBackground(255, 255, 255);
	ofEnableSmoothing();
    //hint(ENABLE_OPENGL_4X_SMOOTH);
    
    box2d.init();
	box2d.setGravity(0, 0);
	box2d.setFPS(30.0);
    //box2d.registerGrabbing();
        
	radius = 15;
    
    pTouchX = 0;
    
    NumPlayers = 2;
    numParticles = 4;
    
    centerX = ofGetWidth()/2.0;
    centerY = ofGetHeight()/2.0;
    
	pos.x = centerX;
	pos.y = centerY;
    
    fastestCW = 2.0;
    fastestCCW = -2.0;

    
    wavelength = 0.0; //how fast we go
	amplitude = 300.0; //the radius of the rotation
    touchVel = 0;
    
    _isTouching = false;
    
    //motor values
    speed = 5;
    //torque = 200;
    torque = 400;
    //change torque depending on player mass
    
    TWOPI = 2*PI;
    
	
	anchor.setup(box2d.getWorld(), centerX, centerY, 4);
    
    
    // register the listener so that we get the events
	ofAddListener(box2d.contactStartEvents, this, &testApp::contactStart);
	ofAddListener(box2d.contactEndEvents, this, &testApp::contactEnd);
    
    //initializing the players
    for (int i=0; i<NumPlayers; i++) {
        
        Player p;
        //p.setPhysics(.5, 0.53, 0.1); //may want to call this in the actuall class
        //p.setPhysics(2, 0.53, 0.1); //may want to call this in the actuall class
        p.setPhysics(5, .2, 0.01); //may want to call this in the actuall class


        //p.setPhysics(.5, 0.53, 100); //may want to call this in the actuall class
        p.setMassFromShape = true;
        p.enableGravity(false);
        //circle.setPhysics(0.1, 0.1, 0.1);
        
        //place player 1

        if (i==0) {
            p.setup(box2d.getWorld(), centerX, centerY+amplitude, radius);
            p.setColor(0x0000FF);	

        }
        //place player 2
        if (i==1) {
            p.setup(box2d.getWorld(), centerX, centerY-amplitude, radius);
            p.setColor(0xFF0000);

        }

        p.setData(new MyData());
		MyData * pd = (MyData*)p.getData();
        int pNum = 100+i; //player id will be either 1.1 or 1.2
        printf("adding players number %i\n\n",pNum);
		pd->myID = pNum; //set a unique id
		pd->bHit	= false;
        pd->myName = "player";
        p.id=pNum;
        //p.alive = true;
        
        players.push_back(p);
    
    }
    


    
    anchor2.setPhysics(5, 0.5, 0.1); //may want to call this in the actual class
    anchor2.enableGravity(false);
    anchor2.setup(box2d.getWorld(), centerX, centerY+300, 4);

//    //connecting the players to a revolute joint
 for (int i=0; i<NumPlayers; i++) {
		ofxBox2dRevJoint rjoint;
        		// if this is the first point connect to the top anchor.
        rjoint.setup(box2d.getWorld(), anchor.body, players[i].body, true);
		rjoint.enableMotor(true);
        rjoint.setMaxMotorTorque(torque);
        rjoints.push_back(rjoint);
}
    
    startTime = ofGetElapsedTimef();
    lastEventTime = startTime;
    
    bkgd.loadImage("bkgd.png");
    red_arrowr.loadImage("Red_arrow_R.png");
    red_arrowl.loadImage("Red_arrow_L.png");

    blue_arrowr.loadImage("Blue_arrow_R.png");
    blue_arrowl.loadImage("Blue_arrow_L.png");
    
    myFont.loadFont("JeanLuc-Bold.otf", 80);
    myFont_small.loadFont("JeanLuc-Bold.otf", 24);
    
    TouchInfo* t_info = new TouchInfo();
//    TouchInfo * ti = (TouchInfo*ti.getData();
//    int pNum = 100+i; //player id will be either 1.1 or 1.2
//    printf("adding players number %i\n\n",pNum);
//    pd->myID = pNum; //set a unique id
//    pd->bHit	= false;
//    pd->myName = "player";
//    p.id=pNum;
//

}


//--------------------------------------------------------------
//checking for collisions, making stuff happen
void testApp::contactStart(ofxBox2dContactArgs &e) {
	
    if(e.a != NULL && e.b != NULL) {
        MyData * aData = (MyData*)e.a->GetBody()->GetUserData();
        MyData * bData = (MyData*)e.b->GetBody()->GetUserData();
        
        if (aData&&bData) {
            printf("adata ID: %i\nbdata ID: %i\n", aData->myID, bData->myID);
            aData->bHit = true;
            
            bData->bHit = true;

            //PLayer hit PLayer
            if (aData->myName=="player") {
                
                for (int i=0; i<players.size(); i++) {
                    int n = 100+i;
                    if (aData->myID==n) {
                        players[i].isTouching = true;
                        players[i].startContact(bData->myID, bData->myName);
                    }
                }
            }
            if (bData->myName=="player") {
                for (int i=0; i<players.size(); i++) {
                    int n = 100+i;

                    if(bData->myID==n){
                        players[i].isTouching = true;
                        players[i].startContact(aData->myID, aData->myName);
                        
                    }
                }
            }
            
            if (aData->myName=="particle") {
                
                for (int i=0; i<particles.size(); i++) {
                    int n = 200+i;
                    if (aData->myID==n) {
                        particles[i].isTouching = true;
                        particles[i].startContact(bData->myID, bData->myName);
                    }
                }
            }
            if (bData->myName=="particle") {
                for (int i=0; i<particles.size(); i++) {
                    int n = 200+i;
                    
                    if(bData->myID==n){
                        particles[i].isTouching = true;
                        particles[i].startContact(aData->myID, aData->myName);
                        
                    }
                }
            }
 
                        
        }//if (aData&&bData)

        }//end if !Null
    }//end Contact Start

void testApp::contactEnd(ofxBox2dContactArgs &e) {
	
    if(e.a != NULL && e.b != NULL) {
        MyData * aData = (MyData*)e.a->GetBody()->GetUserData();
        MyData * bData = (MyData*)e.b->GetBody()->GetUserData();
        
        if (aData&&bData) {
            printf("adata ID: %i\nbdata ID: %i\n", aData->myID, bData->myID);
            aData->bHit = false;
            
            bData->bHit = false;
            
            //PLayer hit PLayer
            if (aData->myName=="player") {
                
                for (int i=0; i<players.size(); i++) {
                    int n = 100+i;
                    if (aData->myID==n) {
                        players[i].isTouching = false;
                        players[i].endContact(bData->myID, bData->myName);
                    }
                }
            }
            if (bData->myName=="player") {
                for (int i=0; i<players.size(); i++) {
                    int n = 100+i;
                    
                    if(bData->myID==n){
                        players[i].isTouching = false;
                        players[i].endContact(aData->myID, aData->myName);
                        
                    }
                }
            }
            
            if (aData->myName=="particle") {
                
                for (int i=0; i<particles.size(); i++) {
                    int n = 200+i;
                    if (aData->myID==n) {
                        particles[i].isTouching = false;
                        particles[i].endContact(bData->myID, bData->myName);
                    }
                }
            }
            if (bData->myName=="particle") {
                for (int i=0; i<particles.size(); i++) {
                    int n = 200+i;
                    
                    if(bData->myID==n){
                        particles[i].isTouching = false;
                        particles[i].endContact(aData->myID, aData->myName);
                        
                    }
                }
            }
            
            
        }//if (aData&&bData)
        
    }//end if !Null
}

//--------------------------------------------------------------
void testApp::update(){
    box2d.update();	
    for (int i=0; i<NumPlayers; i++) {
        players[i].update();
        float _mass = players[i].body->GetMass();
        if (_mass>5) {
//            printf("PLAYER %i Mass = %f", i, _mass);
            nTorque = 30*_mass;
            //a value of 40*_mass keeps the torque consistent, but we want it to be harder...
            rjoints[i].setMaxMotorTorque(nTorque);
//            printf("PLAYER %i Torque = %f", i, nTorque);

        }
        float _radius = players[i].getRadius();
        if (_radius >= 50) {
            players[i].win();
            
        }
    }
    if(ofGetElapsedTimef() - lastEventTime >= 3.0f){  
        lastEventTime = ofGetElapsedTimef();    
        addParticle();
    }


    vector <Particle>::iterator iter = particles.begin();
    while (iter != particles.end()) {
        iter->update();
        ofVec2f center_w = ofVec2f(centerX, centerY);
        if(iter->getPosition().x>740 || iter->getPosition().x<0 || iter->getPosition().y>1024 || iter->getPosition().y<0) {
            iter->dead=true;
        }
        if(iter->dead) {
            printf("\n\nDEAD\n\n");
            iter->destroy();
            particles.erase(iter);
        }

		else ++iter;
    }
    

    posx = (players[0].getPosition().x);
    posy = (players[0].getPosition().y);
    
}

//--------------------------------------------------------------
void testApp::draw(){
    ofFill();
    ofSetHexColor(0xFFFFFFF);
    bkgd.draw(0, 212);
    
    ofFill();
    ofEnableAlphaBlending(); 
    //ofSetColor(255,255,255,0);

 if (_isTouching) {
     ofSetColor(255, 255, 255, t_info.pSpeed); 
     
     if (t_info.pNum==1) {
         if(t_info.pDir==-1){
             red_arrowl.draw(100, 67.5);
         }else{
         red_arrowr.draw(467, 67.5);
     }
     }
     if (t_info.pNum==0) {
         if(t_info.pDir==1){
             blue_arrowl.draw(100, 891.5);
         }else{
             blue_arrowr.draw(467, 891.5);

         }
     }
 }
     ofDisableAlphaBlending();

//        int newalpha;
//        if (newalpha > 255) {newalpha = 255;}
//        ofSetColor(255,255,255,newalpha);
//    }
//    else { ofSetColor(255,255,255,0);}
        
//    red_arrowl.draw(100, 67.5);
//    red_arrowr.draw(467, 67.5);
//    blue_arrowl.draw(100, 891.5);
//    blue_arrowr.draw(467, 891.5);
    

    // ofStroke();
//    ofSetHexColor(0x000000);
//	ofCircle(centerX, centerY, 300);
    
    ofFill();

    ofSetHexColor(0x0000FF);
	ofCircle(708, 752, players[0].getRadius());

    ofSetHexColor(0xFF0000);
	ofCircle(60, 272, players[1].getRadius());

    std::vector<Particle>::iterator p ; 
        for ( p = particles.begin() ; p != particles.end() ; p++ ) 
        {
    		p->draw();
        }
    

    for(int i=0; i<NumPlayers; i++) {
		players[i].draw();
        if (players[i].iWin==true){
            //type it out
            if (i==0) {
                ofSetHexColor(0x0000FF);

                myFont.drawString("Blue Player \nWon!", 127,460);
                myFont_small.drawString("Thanks for playtesting!\nTo play again, quit and reopen", 127, 605);

            }
            if (i==1) {
                ofSetHexColor(0xFF0000);
                
                myFont.drawString("Red Player \nWon!", 127,460);
                myFont_small.drawString("Thanks for playtesting!\nTo play again, quit and reopen", 127, 605);
            }

        }
        
	}
    

     //ofLine(mouseX, 20, pTouchX, 80); 
/**
	string info = "";
	info += "FPS: "+ofToString(ofGetFrameRate(), 1)+"\n";
    info += "circlepos: "+ofToString(players[0].getPosition())+"\n";
    //info += "joint angle: "+ofToString(rjoints[0].getJointAngle())+"\n";
    info += "circle angle: "+ofToString(players[0].getRotation())+"\n";
    info += "circle1 mass: "+ofToString(players[0].body->GetMass())+"\n";
    info += "circle2 mass: "+ofToString(players[1].body->GetMass())+"\n";
    info += "motor Torque1: "+ofToString(rjoints[0].getMotorTorque())+"\n";
    info += "motor Torque2: "+ofToString(rjoints[1].getMotorTorque())+"\n";
    info += "motor Speed1: "+ofToString(rjoints[0].getMotorSpeed()
)+"\n";
    info += "motor Speed2: "+ofToString(rjoints[1].getMotorSpeed()
)+"\n";


    //info += "time: "+ofToString(ofGetElapsedTimef())+"\n";



    //info += "motor velocity: "+ofToString(rjoints[0].getJointSpeed())+"\n";
    
    
	ofSetHexColor(0x444342);
	ofDrawBitmapString(info, 30, 30);
    
    //feedback elements
    **/

}

//--------------------------------------------------------------
//Methods to add player and particle
void testApp::addParticle() {    //initializing the particle
    
    //for (int i=0; i<numParticles; i++) {
        
        Particle m;
        m.dead = false;
        
        m.setPhysics(10.0, 0.5, 0.3);
        m.setSensor(true);
        m.setup(box2d.getWorld(), centerX, centerY, m.radius);
    
        
        m.setData(new MyData());
        
		MyData * md = (MyData*) m.getData();
        
        int mNum = 200; //player id will be from 2.1 to 2.xnum of particles
        printf("adding particles number %i\n\n",mNum);
		md->myID = mNum; //set a unique id
		md->bHit = false;
        md->myName = "particle";
        m.id = mNum;
        
    int rand = ofRandom(0, 100);
    
    for (int i=0; i<101; i++) {
        //float rValX = ofRandom(379, 389);
        //float rValY = ofRandom(507, 517);
        float rValX = ofRandom(0, 740);
        float rValY = ofRandom(0, 1024);

        
        //we don't want (0,0)
        if (rValX==centerX || rValY==centerY){
            randomVals.pop_back(); //remove from end
        }
        ofVec2f myV(rValX, rValY);
        randomVals.push_back(myV);
        //printf("%f ",rVal);
    }
    //m.setPosition(randomVals[rand]);
    
    m.setPosition(centerX, centerY);
    m.addRepulsionForce(randomVals[rand], 1.5);
    

    particles.push_back(m);
    printf("Particle size %lu", particles.size());
        
    //}
    

}

void testApp::addPlayer(ofxBox2d _box2d, float _posX, float _posY, float _radius, float _timer) {
    //could be added later...
}


//--------------------------------------------------------------
void testApp::exit(){
}

//--------------------------------------------------------------
void testApp::touchDown(ofTouchEventArgs &touch)
{
    if(touches.size() < 5) touches.push_back(POFinger(touch));  
    _isTouching = true;
    for(int i = 0; i < players.size(); i++){  
        
        //player 2 touchZone

        if(touch.y>0 && touch.y<212){  
            
            //THIS WILL BE FOR THE BRAKES
            /**
            touchEventTime = ofGetElapsedTimef();
            printf("TOUCH TIME: %f",touchEventTime);
            **/
            
            players[1].fingerIndex = touches.size() - 1;
            _prevX = touch.x;
            //ljoints[1].enableMotor(true);

            rjoints[1].enableMotor(true);
            touchX = touch.x;
            touchVel = touchX;
            float fWidth = ofGetWidth();
            
            wavelength = rangeMap(0, fWidth, fastestCCW, fastestCW, touchVel);
            
            //rjoints[1].setMotorSpeed(wavelength); //this seems to work
            //TURNING OFF FOR THE TIME BEING
            //THIS WILL BE FOR THE BRAKES
            /**

            if(ofGetElapsedTimef() - touchEventTime >= 1.5f){  
            touchEventTime = ofGetElapsedTimef();    
                printf("Brakes!");

            //put on the brakes!

            rjoints[1].setMotorSpeed(0);
            rjoints[1].setMaxMotorTorque(nTorque);//makes no difference
            rjoints[1].enableMotor(true);

            }
             **/
        }
        //player 1 touchZone
        if (touch.y>812 && touch.y<1024) {
            players[0].fingerIndex = touches.size() - 1;  

            _isTouching = true;
            _prevX = touch.x;
            rjoints[0].enableMotor(true);
            //ljoints[0].enableMotor(true);

            touchX = touch.x;
            touchVel = touchX;
            float fWidth = ofGetWidth();
            
            wavelength = rangeMap(0, fWidth, fastestCCW, fastestCW, touchVel);
            
            //rjoints[0].setMotorSpeed(wavelength); //this seems to work

        }
    }

}

//--------------------------------------------------------------
void testApp::touchMoved(ofTouchEventArgs &touch){
    //player 2 touchZone
	int indexOfMovedTouch = -1;
	for(int i = 0; i < touches.size(); i++){	// find touch in vector of touches by id
		if(touches[i].id == touch.id) indexOfMovedTouch = i;
	}	
    
	if(indexOfMovedTouch != -1){
        
        //player 2 touchZone

        if (touch.y>0 && touch.y<200) {
            
            touchX = touch.x;
            touchVel = touchX;
            
            float mySpeed = touches[indexOfMovedTouch].accel;
            
            
            float _currSpeed = rjoints[0].getMotorSpeed();
            if(_currSpeed<0){
                _currSpeed*=-1;
            }
            //direction is either 0, 1 or -1
            rjoints[1].setMotorSpeed((_currSpeed+mySpeed)*(touches[indexOfMovedTouch].direction));
//            rjoints[1].setMotorSpeed(mySpeed*touches[indexOfMovedTouch].direction); //this seems to work

            t_info.pSpeed = rangeMap(0, 50, 0, 255, mySpeed);
            t_info.pNum = 1;
            t_info.pDir = touches[indexOfMovedTouch].direction;

        }
        
        //player 1 touchZone
        
        if (touch.y>824 && touch.y<1024) {
            touchX = touch.x;
            touchVel = touchX;
            
            float mySpeed = touches[indexOfMovedTouch].accel;
            
            float _currSpeed = rjoints[0].getMotorSpeed();
            printf("\n----------CurrSpeed: %f\n", _currSpeed);
            if(_currSpeed<0){
                _currSpeed*=-1;
            }
            //direction is either 0, 1 or -1
            rjoints[0].setMotorSpeed((_currSpeed+mySpeed)*(touches[indexOfMovedTouch].direction*-1)); //this seems to work

            t_info.pSpeed = rangeMap(0, 50, 0, 255, mySpeed);
            t_info.pNum = 0;
            t_info.pDir = touches[indexOfMovedTouch].direction*-1;

        }

	 	touches[indexOfMovedTouch].update(touch); // update the touch
	}

    
}


//--------------------------------------------------------------
void testApp::touchUp(ofTouchEventArgs &touch){
    int indexOfReleasedTouch = -1;  
    for(int i = 0; i < touches.size(); i++){  
        if(touches[i].id == touch.id) indexOfReleasedTouch = i;  
    }  
    for(int i=0; i<NumPlayers; i++){
        if (players[i].fingerIndex==indexOfReleasedTouch) {
            //printf("Player number %i released touch", i);        
        }
        _isTouching = false;
        ticks = 0;//zero out the timer
        wavelength=0;
        
        //put on the brakes!
//TURNING OFF FOR THE TIME BEING
        //rjoints[i].setMotorSpeed(0);
        //rjoints[i].setMaxMotorTorque(200);//makes no difference
        //rjoints[i].enableMotor(true);
        rjoints[i].enableMotor(false);

    }
    
    if(indexOfReleasedTouch != -1) touches.erase(touches.begin() + indexOfReleasedTouch);       // erase the touch  
                
}

//--------------------------------------------------------------
void testApp::touchDoubleTap(ofTouchEventArgs &touch){
    
}

//--------------------------------------------------------------
void testApp::lostFocus(){
    
}

//--------------------------------------------------------------
void testApp::gotFocus(){
    
}

//--------------------------------------------------------------
void testApp::gotMemoryWarning(){
    
}

//--------------------------------------------------------------
void testApp::deviceOrientationChanged(int newOrientation){
    
}


//--------------------------------------------------------------
void testApp::touchCancelled(ofTouchEventArgs& args){
    
}

float testApp::rangeMap(float r1min, float r1max, float r2min, float r2max, float r1val) {
     /**
         *                     r1val
         *    |- - - - -|--------x----|
         *    0       r1min       \  r1max
         *                         \
         *    |- - - - - -|---------x-------|
         *    0         r2min      return  r2max
         */
    
    return (r1val - r1min) * ((r2max - r2min)/(r1max - r1min)) + r2min;
}

void addRect(){
    //add the rectangles to display the touch velocity meter
   // ofRectangle r;
    
}