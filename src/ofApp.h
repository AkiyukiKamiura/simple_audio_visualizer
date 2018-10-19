#pragma once

#include "ofMain.h"
#include "colorGrid.hpp"
#include <math.h>
#include "ofxOpenCv.h"
#include "ofxEasyFft.h"

#define GRIDHEIGHT 15 // 奇数
#define GRIDWIDTH 25 // 1.6倍以上, 奇数

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
    void audioIn(float* input, int bufferSize, int nChannels);
    
private:
    bool isPlaying = false;
    float gridWidth; 
    int windowWidth;
    int windowHeight;
    ColorGrid colorGrids[GRIDHEIGHT*GRIDWIDTH];
    ofVec2f mousePointedPos = ofVec2f(-1, -1);
    
    int plotHeight, bufferSize;
    ofxFft* fft;
    ofMutex soundMutex;
    vector<float> drawBins, middleBins, audioBins;
};
