#pragma once

#include "ofMain.h"
#include "colorGrid.hpp"
#include <math.h>

#define GRIDHEIGHT 15 // 奇数
#define GRIDWIDTH 25  // 1.6倍以上, 奇数

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
		
    
private:
    bool isPlaying = false;
    int width;
    ofVec3f grids[GRIDHEIGHT*GRIDWIDTH];
    ofColor colors[GRIDHEIGHT*GRIDWIDTH];
    float depths[GRIDHEIGHT*GRIDWIDTH];
    ofColor firstColors[GRIDHEIGHT*GRIDWIDTH];
    int colorDev = 80;
    
    ColorGrid colorGrids[GRIDHEIGHT*GRIDWIDTH];
    
    ofVec2f mousePointedPos = ofVec2f(-1, -1);
};
