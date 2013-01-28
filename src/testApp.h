#pragma once

#include "ofMain.h"
#include "ofxDrawnetic.h"
#include "ofxOpenCv.h"

#define _USE_LIVE_VIDEO

class testApp : public ofBaseApp
{
public:
    void setup();
    void update();
    void draw();
    void exit();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    ofxMarking* marking;
    ofxSuperPath* path;
    ofxPaint* paint;
    ofxPerlinBrush* brush;
    
    vector<ofxMarking *>::iterator it;
    vector<ofxMarking *> markings;
    
    ofVideoGrabber 		vidGrabber;
    ofxCvColorImage			colorImg;
};
