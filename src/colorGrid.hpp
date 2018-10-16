//
//  colorGrid.hpp
//  simpleVisualizer
//
//  Created by Akiyuki Kamiura on 2018/10/16.
//

#ifndef colorGrid_hpp
#define colorGrid_hpp

#include <stdio.h>
#include "ofMain.h"

class ColorGrid {
private:
    float width;
    float mainDepth;
    float drawDepth;
    float depthChangedTimef;
    ofColor lineColor;
    ofColor mainColor;
    ofColor drawColor;
    ofVec3f position;
    float colorPeriod;
    float colorAmplitude;
    float depthPeriod;
    float depthAmplitude;
public:
    ColorGrid(){};
    ColorGrid(float width, float depth, ofColor mainColor, ofColor lineColor, ofVec3f position) {
        this->width = width;
        this->mainDepth = depth;
        this->drawDepth = depth;
        this->mainColor = mainColor;
        this->lineColor = lineColor;
        this->position = position;
    }
    void initRandomizedColor(float hueDeviation, float saturationDeviation, float brightnessDeviation);
    void initColorSine(float amplitude, float period);
    void initDepthSine(float amplitude, float period);
    void updateDepth();
    void updateColor();
    void draw();
    void mousePointed(float depthAddition);
    ofVec3f getPosition();
};

#endif /* colorGrid_hpp */
