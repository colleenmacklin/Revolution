//
//  CParticleSystem.cpp
//  Revolution
//
//  Created by Colleen Macklin on 1/8/12.
//  Copyright (c) 2012 Parsons School of Design. All rights reserved.
//

#include <iostream>
#include "CParticleSystem.h"

CParticleSystem::CParticleSystem(b2World* _theWorld, ofVec2f _location){
    theWorld=_theWorld;
    origin=_location;
}

void addParticle() {
    //for (int i=0; i<numParticles; i++) {
        
        Particle m;
        m.dead = false;
        
        m.setPhysics(1.0, 0.5, 0.3);
        m.setSensor(true);
        //m.setup(box2d.getWorld(), centerX, centerY, m.radius);
        
        m.setup(&theWorld, centerX, centerY, m.radius);
    
        if (i==0) {
            m.setPosition(centerX+amplitude+5, centerY);
        }
        if (i==1) {
            m.setPosition(centerX, centerY-amplitude/2);
        }
        if (i==2) {
            m.setPosition(centerX-amplitude+5, centerY);
        }
        if (i==3) {
            m.setPosition(centerX+amplitude/2, centerY+amplitude/2+5);
        }
        
        m.setData(new MyData());
        
		MyData * md = (MyData*) m.getData();
        
        int mNum = 200+i; //player id will be from 2.1 to 2.xnum of particles
        printf("adding particles number %i\n\n",mNum);
		md->myID = mNum; //set a unique id
		md->bHit = false;
        md->myName = "particle";
        m.id = mNum;
        
        particles.push_back(m);
        
    //}
}

//    void addParticle() {
//        Particle.add(new Particle(origin));
//    }
//    
//    // A function to apply a force to all Particles
//    void applyForce(PVector f) {
//        for (Particle p: particles) {
//            p.applyForce(f);
//        }
//    }
//    
//    void applyRepeller(Repeller r) {
//        for (Particle p: particles) {
//            PVector repel = r.repel(p);        
//            p.applyForce(repel);
//        }
//    }
//    
//    
//    void run() {
//        Iterator<Particle> it = particles.iterator();
//        while (it.hasNext()) {
//            Particle p = it.next();
//            p.run();
//            if (p.isDead()) {
//                it.remove();
//            }
//        }
//    }
//}
//

