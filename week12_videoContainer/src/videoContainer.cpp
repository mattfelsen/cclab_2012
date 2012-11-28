//
//  videoContainer.cpp
//  week12_videoContainer
//
//  Created by Matt on 11/16/12.
//
//

#include "videoContainer.h"

void videoContainer::setup() {
	
	player.loadMovie("kyle.mov");
	player.play();
	
}

void videoContainer::update() {
	
	player.update();
	
}

void videoContainer::draw(float x, float y) {
	
	player.draw(x, y);
	
}