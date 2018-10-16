#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofToggleFullscreen();
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofBackground(0);
    
    ofColor meanColor = ofColor(255, 0, 0, 125);
    ofColor lineColor = ofColor(255);
    
    width = int(ofGetHeight()/GRIDHEIGHT);
    for (int i = 0; i < GRIDHEIGHT; i++){
        for (int j = 0; j < GRIDWIDTH; j++){
            int k = int(i*GRIDWIDTH + j);
            ofVec3f gridPos = ofVec3f(width*(j - GRIDWIDTH/2), width*(i - GRIDHEIGHT/2), 0);
            colorGrids[k] = ColorGrid(width, 10, meanColor, lineColor, gridPos);
            colorGrids[k].initRandomizedColor(0, 0, 0);
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
                colorGrids[k].mousePointed(80);
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    
    for (int i = 0; i < GRIDHEIGHT; i++){
        for (int j = 0; j < GRIDWIDTH; j++){
            int k = int(i*GRIDWIDTH + j);
            ofDrawBitmapString(ofToString(i) + ", " + ofToString(j), colorGrids[k].getPosition().x-width/2 + 10, colorGrids[k].getPosition().y);
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
    int w = floor((x - ofGetWidth()/2)/float(width) + GRIDWIDTH/2.0);
    int h = floor((y - ofGetHeight()/2)/float(width) + GRIDHEIGHT/2.0);
    mousePointedPos.x = (0 <= w and w < GRIDWIDTH) ? w : -1;
    mousePointedPos.y = (0 <= h and h < GRIDHEIGHT) ? h : -1;
    cout << "mouse position: " << mousePointedPos.y << ", " << mousePointedPos.x << endl;
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
