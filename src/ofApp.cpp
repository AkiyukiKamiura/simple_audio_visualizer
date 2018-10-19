#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofToggleFullscreen();
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofBackground(0);
    
    plotHeight = 128;
    bufferSize = 2048;
    fft = ofxFft::create(bufferSize, OF_FFT_WINDOW_HAMMING);
    drawBins.resize(fft->getBinSize());
    middleBins.resize(fft->getBinSize());
    audioBins.resize(fft->getBinSize());
    
    ofSoundStreamSetup(0, 1, this, 44100, bufferSize, 4);
    
    ofColor meanColor = ofColor(200, 0, 0, 125);
    ofColor lineColor = ofColor(0);
    
    gridWidth = int(ofGetHeight()/GRIDHEIGHT);
    for (int i = 0; i < GRIDHEIGHT; i++){
        for (int j = 0; j < GRIDWIDTH; j++){
            int k = int(i*GRIDWIDTH + j);
            ofVec3f gridPos = ofVec3f(gridWidth*(j - GRIDWIDTH/2), gridWidth*(i - GRIDHEIGHT/2), 0);
            colorGrids[k] = ColorGrid(gridWidth, 10, meanColor, lineColor, gridPos);
            colorGrids[k].initRandomizedColor(20, 0, 0);
            colorGrids[k].initColorSine(0, 3);
            colorGrids[k].initDepthSine(20, rand()%2+1);
        }
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    for (int i = 0; i < GRIDHEIGHT; i++){
        for (int j = 0; j < GRIDWIDTH; j++){
            int k = int(i*GRIDWIDTH + j);
            colorGrids[k].updateColor();
            colorGrids[k].updateDepth();
            if (mousePointedPos.x == j and mousePointedPos.y == i) {
                colorGrids[k].addDepth(80);
            }
        }
    }
    
    soundMutex.lock();
    drawBins = middleBins;
    soundMutex.unlock();
    
    int freqGroup = floor(drawBins.size()/GRIDWIDTH);
    for (int j = 0; j < GRIDWIDTH; j++){
        float meanVal = 0.0;
        for (int l = j*freqGroup; l < (j+1)*freqGroup; l++){
            meanVal += drawBins[l];
        }
        meanVal /= float(freqGroup);
        for (int i = GRIDHEIGHT-1; i >= GRIDHEIGHT*(1-meanVal*2); i--){
            int k = int(i*GRIDWIDTH + j);
            colorGrids[k].addDepth(30);
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255);
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    for (int i = 0; i < GRIDHEIGHT; i++){
        for (int j = 0; j < GRIDWIDTH; j++){
            int k = int(i*GRIDWIDTH + j);
            ofDrawBitmapString(ofToString(i) + ", " + ofToString(j), colorGrids[k].getPosition().x-gridWidth/2 + 10, colorGrids[k].getPosition().y);
            colorGrids[k].draw();
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if (key == OF_KEY_RETURN) {
        isPlaying = !isPlaying;
        if (isPlaying) {
            cout << "playing" << endl;
        } else {
            cout << "stopped" << endl;
        }
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    int w = floor((x - ofGetWidth()/2)/float(gridWidth) + GRIDWIDTH/2.0);
    int h = floor((y - ofGetHeight()/2)/float(gridWidth) + GRIDHEIGHT/2.0);
    mousePointedPos.x = (0 <= w and w < GRIDWIDTH) ? w : -1;
    mousePointedPos.y = (0 <= h and h < GRIDHEIGHT) ? h : -1;
//    cout << "mouse position: " << mousePointedPos.y << ", " << mousePointedPos.x << endl;
 }

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

// -------------------------------------------------------------
void ofApp::audioIn(float* input, int bufferSize, int nChannels) {
    float maxValue = 0;
    for(int i = 0; i < bufferSize; i++) {
        if(abs(input[i]) > maxValue) {
            maxValue = abs(input[i]);
        }
    }
    for(int i = 0; i < bufferSize; i++) {
        input[i] /= maxValue; // 正規化
    }
    
    fft->setSignal(input);
    
    float* curFft = fft->getAmplitude();
    memcpy(&audioBins[0], curFft, sizeof(float) * fft->getBinSize());
    
    maxValue = 0;
    for(int i = 0; i < fft->getBinSize(); i++) {
        if(abs(audioBins[i]) > maxValue) {
            maxValue = abs(audioBins[i]);
        }
    }
    for(int i = 0; i < fft->getBinSize(); i++) {
        audioBins[i] /= maxValue;
    }
    
    soundMutex.lock();
    middleBins = audioBins;
    soundMutex.unlock();
}
