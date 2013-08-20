#include "ControlPanel.h"


ControlPanel::ControlPanel()
{
	localPort = 6666;
	remotePort = 6667;
	omxVideoGrabber = NULL;
}

void ControlPanel::setup(ofxOMXVideoGrabber* omxVideoGrabber_)
{
	omxVideoGrabber = omxVideoGrabber_;
	parameters.setName("parameters");
    
    sharpness.set("sharpness", omxVideoGrabber->sharpness, -100, 100);
    contrast.set("contrast", omxVideoGrabber->contrast, -100, 100);
    brightness.set("brightness", omxVideoGrabber->brightness, 0, 100);
    saturation.set("saturation", omxVideoGrabber->saturation, -100, 100);
    frameStabilizationEnabled.set("FrameStabilization", false);
    colorEnhancementEnabled.set("ColorEnhancement", false);
    ledEnabled.set("LED", false);
    
	parameters.add(sharpness);
	sharpness.addListener(this, &ControlPanel::onSharpnessChanged);
	
	parameters.add(contrast);
	contrast.addListener(this, &ControlPanel::onContrastChanged);
	
    parameters.add(brightness);
	brightness.addListener(this, &ControlPanel::onBrightnessChanged);
	
    parameters.add(saturation);
    saturation.addListener(this, &ControlPanel::onSaturationChanged);
	
    parameters.add(frameStabilizationEnabled);
	frameStabilizationEnabled.addListener(this, &ControlPanel::onFrameStabilizationChanged);
	
    parameters.add(colorEnhancementEnabled);
	colorEnhancementEnabled.addListener(this, &ControlPanel::onColorEnhancementChanged);
	
    parameters.add(ledEnabled);
	ledEnabled.addListener(this, &ControlPanel::onLEDEnabledChanged);
	
	
	
	gui.setup(parameters);
	// by now needs to pass the gui parameter groups since the panel internally creates it's own group
	sync.setup((ofParameterGroup&)gui.getParameter(), localPort, "localhost", remotePort);
	gui.setPosition(ofPoint(ofGetWidth()-gui.getWidth(), 50));
	
}

void ControlPanel::update()
{
	sync.update();
}


void ControlPanel::draw()
{
	
	gui.draw();
}

void ControlPanel::onSharpnessChanged(int & sharpness_)
{
	ofLogVerbose(__func__) << sharpness_;
	omxVideoGrabber->setSharpness(sharpness_);
}

void ControlPanel::onContrastChanged(int & contrast_)
{
	ofLogVerbose(__func__) << contrast_;
	omxVideoGrabber->setContrast(contrast_);
}

void ControlPanel::onBrightnessChanged(int & brightness_)
{
	ofLogVerbose(__func__) << brightness_;
	omxVideoGrabber->setBrightness(brightness_);
}

void ControlPanel::onSaturationChanged(int & saturation_)
{
	ofLogVerbose(__func__) << saturation_;
	omxVideoGrabber->setSaturation(saturation_);
}
void ControlPanel::onFrameStabilizationChanged(bool & doFrameStabilization)
{
	omxVideoGrabber->setFrameStabilization(doFrameStabilization);
}

void ControlPanel::onColorEnhancementChanged(bool & doColorEnhancement)
{
	omxVideoGrabber->setColorEnhancement(doColorEnhancement);
}

void ControlPanel::onLEDEnabledChanged(bool & doEnableLED)
{
	omxVideoGrabber->setLEDStatus(doEnableLED);
}

