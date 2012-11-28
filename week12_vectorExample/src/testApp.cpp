#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

	ofSetVerticalSync(true);
	ofSetColor(0);
	ofBackground(255);
	ofNoFill();
	
}

//--------------------------------------------------------------
void testApp::update(){

	for (int i = 0; i < points.size(); i++) {
		points[i].z += 2;
	}
	
}

//--------------------------------------------------------------
void testApp::draw(){

	ofBeginShape();

	for (int i = 0; i < points.size(); i++) {
		ofVertex(points[i].x, points[i].y, points[i].z);
	}
	
	ofEndShape();
	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

	ofPoint p;

	p.x = x;
	p.y = y;
	p.z = 0;
	
	points.push_back(p);
	
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