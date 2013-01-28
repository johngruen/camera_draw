#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{
    ofSetVerticalSync(true);
    ofEnableSmoothing();
    path = new ofxSuperPath();
    path->reset();
    ofBackgroundGradient(200, 0);
    ofBackground(255);
    vidGrabber.setVerbose(true);
    vidGrabber.initGrabber(1280,720);

    colorImg.allocate(1280,720);
    marking = NULL;
    brush = NULL;
    paint = NULL;
    
}
//--------------------------------------------------------------
void testApp::update()
{
    bool bNewFrame = false;
    vidGrabber.update();
    bNewFrame = vidGrabber.isFrameNew();
    if (bNewFrame){
    colorImg.setFromPixels(vidGrabber.getPixels(), 1280,720);
    }
    
    bool killSome = false;
    if(ofGetFrameRate() < 50)
    {
        killSome = true;
    }
    
    if(marking != NULL)
    {
        marking->update();
    }
    
    for ( it=markings.begin() ; it < markings.end(); it++ )
    {
        
        ofxMarking *marking = *it;
        if(killSome)
        {
            marking->killLastParticle();
            if(marking->isDead)
            {
                delete marking;
                markings.erase(it);
            }
        }
        else
        {
            marking->update();
        }
    }
}
//--------------------------------------------------------------
void testApp::draw()
{
    ofDisableAlphaBlending();
    ofSetColor(100,0,255);
    colorImg.draw(0,0);
    //colorImg.draw(20,20);
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    
    if(marking != NULL)
    {
        marking->draw();
    }
    
    for(int i = 0; i < markings.size(); i++)
    {
        markings[i]->draw();
    }
}
//--------------------------------------------------------------
void testApp::exit()
{
    for(int i = 0; i < markings.size(); i++)
    {
        delete markings[i];
    }
    markings.clear();
    
    if(marking != NULL)
    {
        delete marking;
    }
}
//--------------------------------------------------------------
void testApp::keyPressed(int key)
{
    
}

//--------------------------------------------------------------
void testApp::keyReleased(int key)
{
    
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y)
{
    
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button)
{
    path->lineTo(x,y,0, ofFloatColor(0), ofGetFrameNum(), 0);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button)
{
    path = new ofxSuperPath();
    paint = new ofxPaint(path, ofColor(255,ofRandom(255),ofRandom(255)), 100);
    brush = new ofxPerlinBrush(path, paint);
    brush->setDynamic(true);
    brush->setSpeed(6);
    brush->setNoiseScale(ofRandom(.001));
    
    
    marking = new ofxMarking(path, paint, brush);
    path->reset();
    path->lineStart(x,y,0, ofFloatColor(0), ofGetFrameNum(), 0);
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button)
{
    path->lineEnd(x,y,0, ofGetFrameNum(), -1, 0);
    marking->pathFinished();
    markings.push_back(marking);
    marking = NULL;
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h)
{
    
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg)
{
    
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo)
{
    
}