// #pragma once


#include "ofMain.h"

class ofApp: public ofBaseApp
{
public:

ofPixels pixels;
ofTexture texture;
ofEasyCam camera;
ofVideoGrabber grabber;

void setup() 
{
    ofSetWindowShape(1024, 768);

    ofEnableAlphaBlending();
    ofEnableDepthTest();

    grabber.initGrabber(40,30);
}

void update() 
{
    grabber.update();

    if(grabber.isFrameNew())
    {
        pixels = grabber.getPixelsRef();
    }
}

void draw() 
{
    ofBackground(0);

    camera.begin();

    ofPushMatrix();
    ofScale(1, -1);
    ofTranslate(- (pixels.getWidth() * 10) / 2, - (pixels.getHeight() * 10) / 2);

    for(std::size_t x = 0; x < pixels.getWidth(); ++x)
    {
        for(std::size_t y = 0; y < pixels.getHeight(); ++y)
        {
            ofColor color = pixels.getColor(x, y);

            float z = ofMap(color.getBrightness(), 0, 255, 0, 1024);

            ofVec3f position(x * 10, y * 10, z);

            ofFill();
            ofSetColor(color);
            ofEllipse(position, 10, 10);
        }
    }

    ofPopMatrix();

    camera.end();
}


};

int main()
{
    ofSetupOpenGL(320,240,OF_WINDOW);
    ofRunApp(new ofApp());
}


