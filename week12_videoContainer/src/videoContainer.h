//
//  videoContainer.h
//  week12_videoContainer
//
//  Created by Matt on 11/16/12.
//
//

#ifndef week12_videoContainer_videoContainer_h
#define week12_videoContainer_videoContainer_h

#include "ofMain.h"

class videoContainer {
	
public:
	
	void setup();
	void update();
	void draw(float x, float y);
	
	ofVideoPlayer player;
	
};

#endif
