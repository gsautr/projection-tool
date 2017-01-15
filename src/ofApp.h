#pragma once

#include "ofMain.h"
#include "ofxDatGui.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void draw();
    int w, h;
    ofFbo fbo;
    ofxDatGui * gui;
    ofxDatGuiTextInput * boxBase;
    ofxDatGuiTextInput * boxAngle;
    ofxDatGuiTextInput * boxWidth;
    ofxDatGuiTextInput * boxLength;
    ofxDatGuiTextInput * ceilingHeight;
    ofxDatGuiTextInput * lensOffset;
    float rotate;
    ofTrueTypeFont font;
    void annotate(float x1, float y1, float x2,float  y2, ofColor color);
    
    ofMesh box;
    ofEasyCam camera;
};
