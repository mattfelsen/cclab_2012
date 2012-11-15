#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	
	// Set some parameters for the sketch
	drawMode = 1;
	ballCount = 300;
	gravity = 0.4;
	
	// Set a basis color somewhere within 360¼ (OF uses 0-255 for 360¼ color wheel)
	// This will be the basis for all the shapes in the sketch
	// Shapes will be offset from this color by some random amount from 0-20 (below)
	// Also, every successive shape gets a triadic color by adding 1/3 of the color wheel
	// each time
	float colorAnchor = 50; // ofRandom(255);
	
	// Turn on all the goods
	// Drawing squares from the center looks better than drawing from their corners when rotating
	ofEnableSmoothing();
	ofEnableAlphaBlending();
	ofSetVerticalSync(true);
	ofRectMode(OF_RECTMODE_CENTER);
	
	// Set background to white
	ofBackground(255);
	
	for (int i = 0; i < ballCount; i++) {
		
		// This is the offset of the current shape from the basis color
		float colorSpread = ofRandom(20);
		
		// Give a random x position and a y position 100px from the top
		xPos.push_back(ofRandom(ofGetWidth()));
		yPos.push_back(100);
		
		// Give a random x speed and then 3x that amount for the y speed
		xSpeed.push_back(ofRandom(-10, 10));
		ySpeed.push_back(xSpeed[i]*3);
		
		// Color for this specific shape. Color is determined by basis color + some
		// amount of randomness (would result in many shades of blue, for example), and then
		// add 1/3 of color wheel (e.g. a basis color of pink would yield pink, then yellow, then
		// light blue)
		// This results in a nice blend of color that is triadic (3 hues), and each hue has a little
		// bit of variation in it
		// Then wrap the whole thing in fmod(COLOR, 255) so that any colors over 255 wrap around the wheel
		colors.push_back(fmod((colorAnchor + colorSpread)+((i%3)*85), 255));
		
		// Annddd finally pick a random size
		sizes.push_back(ofRandom(15, 25));
	}
	
}

//--------------------------------------------------------------
void testApp::update(){
	
	int width = ofGetWidth();
	int height = ofGetHeight();
	
	for (int i = 0; i < ballCount; i++) {
		
		// Increase x by x speed for current shape
		// Then check if it's at the edges and if so, reverse it
		// Also, set the position to the edge so that we don't get stuck on the edge
		xPos[i] += xSpeed[i];
		if (xPos[i] > width - sizes[i]/2) {
			xSpeed[i] *= -1;
			xPos[i] = width - sizes[i]/2;
		}
		if (xPos[i] < sizes[i]/2) {
			xSpeed[i] *= -1;
			xPos[i] = sizes[i]/2;
		}
		
		// Same deal for y...increase y by y speed, and add in gravity
		// HOWEVER do NOT use the same trick of moving to the bottom edge for y because
		// I like the look of the shapes bouncing along the bottom. They look like they're
		// hopping.
		yPos[i] += ySpeed[i];
		ySpeed[i] += gravity;
		
		if (yPos[i] > height-sizes[i]/2) {
			ySpeed[i] *= -0.95;
		}
		
	}
	
}

//--------------------------------------------------------------
void testApp::draw(){
	
	
	for (int i = 0; i < ballCount; i++) {
		
		// Set the current color
		ofSetColor(ofColor::fromHsb(colors[i], 230, 200), 225);
		
		// Calculate the shape's rotation
		// atan2() will return the direction an object should rotate to face
		// the direction it's moving if you supply the x and y speeds
		float theta = atan2(xSpeed[i], ySpeed[i]);
		
		// Grab the size of the current shape and calculate its distance from the mouse
		float size = sizes[i];
		float dist = ofDist(xPos[i], yPos[i], mouseX, mouseY);
		
		// If it's close (200px or closer) then make the shape bigger
		if (dist < 200) {
			size *= ofMap(dist, 200, 0, 1, 5);
		}
		
		ofPushMatrix();
		
		// Translate from (0, 0) to the center of the object & rotate the canvas
		ofTranslate(xPos[i], yPos[i]);
		ofRotateZ(-theta * RAD_TO_DEG);
		
		// Then either draw a square or line based on which mode we're running in
		// Mode 1 is a square which grows near the mouse
		// Mode 2 is a line which grows near the mouse
		// Mode 3 is a line which grows as it gets faster (no mouse interaction)
		if (drawMode == 1)
			ofRect(0, 0, size, size);
		
		if (drawMode == 2)
			ofRect(0, 0, 2, size);
		
		if (drawMode == 3)
			ofRect(0, 0, 2, ySpeed[i]*3);
		
		ofPopMatrix();
	}
	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	
	if (key == '1')
		drawMode = 1;
	if (key == '2')
		drawMode = 2;
	if (key == '3')
		drawMode = 3;
	
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
	
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){
	
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){
	
}