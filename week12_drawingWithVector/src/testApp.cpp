#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){	
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	
	ofBackground(255, 255, 255);
	
	mouseDown = false;
}

//--------------------------------------------------------------
void testApp::update(){

	// for particle systems, a common workflow is:
	// - reset forces on particles
	// - add forces (gravity, attraction, repulsion, etc.)
	// - add damping (friction)
	// - update (adjust velocity & position based on forces)
	
	// I do that here, and update the springs in between since they're
	// adding forces to the particles
	
	for (int i = 0; i < particles.size(); i++){
		// If it's the last particle, keep it fixed (don't apply gravity) if
		// the mouse is still down. Otherwise, let it fall
		if (particles[i] == particles.back()) {
			if (mouseDown)
				particles[i]->fixed = true;
			else
				particles[i]->fixed = false;
		} else {
			// And if it's not the last particle, then it's not fixed
			// and should fall according to gravity
			particles[i]->fixed = false;
		}
		particles[i]->resetForce();
	}
	
	// Update springs & add other forces as explained above
	for (int i = 0; i < springs.size(); i++) {
		springs[i].update();
	}
	
	for (int i = 0; i < particles.size(); i++){
		particles[i]->addForce(0, 0.8);
		particles[i]->addDampingForce();
		particles[i]->update();
	}

}

//--------------------------------------------------------------
void testApp::draw(){


	ofSetLineWidth(3);
	
	// Draw all the springs
	// The springs draw themselves based on a color where the mouse was
	// when the particle was created so we get nice gradients across
	// the string
	for (int i = 0; i < springs.size(); i++){
		springs[i].draw();
	}
	
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 
}

//--------------------------------------------------------------
void testApp::keyReleased  (int key){ 
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

	// Store these for later
	
	prevMouseX = x;
	prevMouseY = y;
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

	float dx = x - prevMouseX;
	float dy = y - prevMouseY;

	
	// Only keep 10 particles so our strings are kind of short
	if (particles.size() < 11) {
		
		// Crete a new particle and set it's initial position (x, y)
		// and its initial velocity (dx and dy represenent x & y velocity)
		particle *p = new particle();
		p->setInitialCondition(x,y, dx*0.3,dy*0.3);
		p->fixed = true;

		// If there are more than 1 particles, create a spring between the particle
		// we just created and the previous one
		if (particles.size() > 0) {
			particle *last = particles.back();

			spring s;
			s.distance		= p->pos.distance(last->pos);
			s.springiness	= 0.5f;
			s.particleA = last;
			s.particleB = p;

			
			// Get the midpoint of the spring and convert it to a color
			// The left side of the window will be 0 and the right side will be 255
			float avg = (p->pos.middle(last->pos)).x;
			float hue = ofMap(avg, 0, ofGetWidth(), 0, 255);
			s.color = ofColor::fromHsb(hue, 200, 200);
			
			springs.push_back(s);

		}

		particles.push_back(p);
	} else {
		particle *last = particles.back();
		last->pos.x = x;
		last->pos.y = y;
	}

	
	prevMouseX = x;
	prevMouseY = y;
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	// When we click, clear the particles & springs
	particles.clear();
	springs.clear();
	mouseDown = true;
}

//--------------------------------------------------------------
void testApp::mouseReleased(){
	mouseDown = false;
}
