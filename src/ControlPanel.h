#pragma once

#include "ofMain.h"

#include "ofxGui.h"
#include "ofxOscParameterSync.h"
#include "ofxOMXVideoGrabber.h"


class ControlPanel
{
public:
	ControlPanel();
	
	void setup(ofxOMXVideoGrabber* omxVideoGrabber_);
	void update();
	void draw();
	ofxOMXVideoGrabber* omxVideoGrabber;
	
private:
	ofParameter<int> sharpness;
	ofParameter<int> contrast;
	ofParameter<int> brightness;
	ofParameter<int> saturation;
	ofParameter<bool> frameStabilizationEnabled;
	ofParameter<bool> colorEnhancementEnabled;
	ofParameter<bool> ledEnabled;
	ofParameter<bool> hideGui;
	
	ofParameterGroup parameters;
	ofxPanel gui;
	
	ofxOscParameterSync sync;
	
	int localPort;
	int remotePort;
	
	bool doHide;
	void onSharpnessChanged(int &sharpness_);
	void onContrastChanged(int &constrast_);
	void onBrightnessChanged(int &brightness_);
	void onSaturationChanged(int &saturation_);
	
	void onFrameStabilizationChanged(bool &doFrameStabilization);
	void onColorEnhancementChanged(bool &doColorEnhancement);
	void onLEDEnabledChanged(bool &doEnableLED);
	void onHideGuiChanged(bool & doHide);
};