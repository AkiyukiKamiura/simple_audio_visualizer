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
    // mainDepth の処理
    if (this->mainDepth - this->basicDepth > 0) {
        this->returnToBasicDepth();
    }
    
    // TODO: 深さの変動処理
    // とりあえず今は mainDepth = drawDepth
    this->drawDepth = this->mainDepth;
}

void ColorGrid::returnToBasicDepth(){
    this->mainDepth = (this->mainDepth*9 + this->basicDepth)/10;
    if (this->mainDepth - this->basicDepth <= 5) {
        this->mainDepth = this->basicDepth;
    }
}

void ColorGrid::addDepth(float depthAddition) {
    depthChangedTimef = ofGetElapsedTimef();
    this->mainDepth = this->basicDepth + depthAddition;
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

void ColorGrid::propagate(ColorGrid grid){
    grid.addDepth(this->drawDepth/5);
}

float ColorGrid::getDepthDiff(){
    return this->drawDepth - this->basicDepth;
}

ofVec3f ColorGrid::getPosition() {
    return this->position;
}

