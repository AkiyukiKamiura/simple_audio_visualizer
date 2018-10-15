#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofToggleFullscreen();
    ofBackground(0);
    
    ofColor meanColor = ofColor(200, 0, 50, 125);
    
    float hue = 0, sat = 0, bri = 0;
    meanColor.getHsb(hue, sat, bri);
    
    width = int(ofGetHeight()/GRIDHEIGHT);
    for (int i = 0; i < GRIDHEIGHT; i++){
        for (int j = 0; j < GRIDWIDTH; j++){
            int k = int(i*GRIDWIDTH + j);
            grids[k] = ofVec3f(width*(j - GRIDWIDTH/2), width*(i - GRIDHEIGHT/2), 0);
            firstColors[k] = ofColor::fromHsb(hue, sat, bri + rand()%50 - 50, 125);
            depths[k] = sin(M_PI/100*k);
        }
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    for (int i = 0; i < GRIDHEIGHT; i++){
        for (int j = 0; j < GRIDWIDTH; j++){
            int k = int(i*GRIDWIDTH + j);
            float hue = 0, sat = 0, bri = 0;
            firstColors[k].getHsb(hue, sat, bri);
            colors[k] = ofColor::fromHsb(hue, sat, bri + 20*sin(M_PI*2/3*ofGetElapsedTimef()), 125);
            depths[k] = sin(M_PI/100*k + ofGetElapsedTimef()/10000);
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    
    for (int i = 0; i < GRIDHEIGHT; i++){
        for (int j = 0; j < GRIDWIDTH; j++){
            int k = int(i*GRIDWIDTH + j);
            float depth = depths[k];

            ofNoFill();
            ofSetColor(ofColor::white);
            ofSetLineWidth(2);
            ofDrawBox(grids[k], width, width, depth);
            
            ofDrawBitmapString(ofToString(i) + ", " + ofToString(j), grids[k].x-width/2 + 10, grids[k].y);

            ofFill();
            ofSetColor(colors[k]);
            ofDrawBox(grids[k], width, width, depth);
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
