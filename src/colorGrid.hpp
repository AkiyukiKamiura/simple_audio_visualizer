//
//  colorGrid.hpp
//  simpleVisualizer
//
//  Created by Akiyuki Kamiura on 2018/10/15.
//

#ifndef colorGrid_hpp
#define colorGrid_hpp

#include <stdio.h>
#include "ofMain.h"

class ColorGrid {
private:
    float size;
    float depth;
    ofColor color = ofColor(255);
    ofVec3f position = ofVec3f(0, 0, 0);
    
public:
    ColorGrid(){};
    void setPosition(ofVec3f posVec);
    void setSize(float size);
    void setDepth(float depth);
    void setColor(ofColor color);
    void draw();
};

#endif /* colorGrid_hpp */
