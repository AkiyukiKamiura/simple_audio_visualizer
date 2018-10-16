//
//  colorGrid.cpp
//  simpleVisualizer
//
//  Created by Akiyuki Kamiura on 2018/10/16.
//

#include "colorGrid.hpp"

float ran0() {
    return (double)rand()/((double)RAND_MAX+1);
}

void ColorGrid::initRandomizedColor(float hueDeviation, float saturationDeviation, float brightnessDeviation){
    float hue = 0, sat = 0, bri = 0;
    this->mainColor.getHsb(hue, sat, bri);
    float newHue = int(hue+ran0()*hueDeviation)%255;
    float newSat = sat + ran0()*saturationDeviation;
    float newBri = bri + ran0()*brightnessDeviation;
    ofColor newColor = ofColor::fromHsb(newHue, newSat, newBri);
    this->mainColor = newColor;
}

void ColorGrid::initColorSine(float amplitude, float period){
    this->colorAmplitude = amplitude;
    this->colorPeriod = period;
}

void ColorGrid::initDepthSine(float amplitude, float period){
    this->depthAmplitude = amplitude;
    this->depthPeriod = period;
}

void ColorGrid::updateColor(){
    float hue = 0, sat = 0, bri = 0;
    this->mainColor.getHsb(hue, sat, bri);
    this->drawColor = ofColor::fromHsb(hue, sat, bri + this->colorAmplitude*sin(M_PI*2/this->colorPeriod*ofGetElapsedTimef()), 125);
}

void ColorGrid::updateDepth(){
    this->drawDepth = (this->drawDepth*4 + this->mainDepth)/5;
    if (this->drawDepth - this->mainDepth <= 5) {
        this->drawDepth = this->mainDepth;
    }
}

void ColorGrid::mousePointed(float depthAddition) {
    depthChangedTimef = ofGetElapsedTimef();
    this->drawDepth = this->mainDepth + depthAddition;
}

void ColorGrid::draw(){
    ofNoFill();
    ofSetColor(this->lineColor);
    ofSetLineWidth(2);
    ofDrawBox(this->position, this->width, this->width, this->drawDepth);
    
    ofFill();
    ofSetColor(this->drawColor);
    ofDrawBox(this->position, this->width, this->width, this->drawDepth);
}

ofVec3f ColorGrid::getPosition() {
    return this->position;
}

