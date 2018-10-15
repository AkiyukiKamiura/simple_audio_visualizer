//
//  colorGrid.cpp
//  simpleVisualizer
//
//  Created by Akiyuki Kamiura on 2018/10/15.
//

#include "colorGrid.hpp"
#include "ofMain.h"

void ColorGrid::setPosition(ofVec3f position){
    this->position = position;
}

void ColorGrid::setSize(float size){
    this->size = size;
}

void ColorGrid::setDepth(float depth){
    this->depth = depth;
}

void ColorGrid::setColor(ofColor color){
    this->color = color;
}

void ColorGrid::draw(){
    ofSetColor(color);
    cout << this->position << endl;
    ofDrawBox(this->position, this->size, this->size, this->depth);
}
