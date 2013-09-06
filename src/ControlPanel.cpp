#include "ControlPanel.h"


ControlPanel::ControlPanel()
{
	localPort = 6666;
	remotePort = 6667;
	rpiCameraVideoGrabber = NULL;
	doHide = false;
}

void ControlPanel::setup(ofxRPiCameraVideoGrabber* rpiCameraVideoGrabber_)
{
	rpiCameraVideoGrabber = rpiCameraVideoGrabber_;
	parameters.setName("parameters");
    
    sharpness.set("sharpness", rpiCameraVideoGrabber->sharpness, -100, 100);
    contrast.set("contrast", rpiCameraVideoGrabber->contrast, -100, 100);
    brightness.set("brightness", rpiCameraVideoGrabber->brightness, 0, 100);
    saturation.set("saturation", rpiCameraVideoGrabber->saturation, -100, 100);
    frameStabilizationEnabled.set("FrameStabilization", false);
    colorEnhancementEnabled.set("ColorEnhancement", false);
    ledEnabled.set("LED", false);
    hideGui.set("hideGui", false);
	
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
	
	parameters.add(hideGui);
	hideGui.addListener(this, &ControlPanel::onHideGuiChanged);
	
	gui.setup(parameters);
	// by now needs to pass the gui parameter groups since the panel internally creates it's own group
	sync.setup((ofParameterGroup&)gui.getParameter(), localPort, "localhost", remotePort);
	gui.setPosition(ofPoint(ofGetWidth()-gui.getWidth()-100, 50));
	
}

void ControlPanel::update()
{
	sync.update();
}


void ControlPanel::draw()
{
	if (doHide) 
	{
		return;
	}
	gui.draw();
}

void ControlPanel::onHideGuiChanged(bool & doHide)
{
	this->doHide = doHide;
}

void ControlPanel::onSharpnessChanged(int & sharpness_)
{
	ofLogVerbose(__func__) << sharpness_;
	rpiCameraVideoGrabber->setSharpness(sharpness_);
}

void ControlPanel::onContrastChanged(int & contrast_)
{
	ofLogVerbose(__func__) << contrast_;
	rpiCameraVideoGrabber->setContrast(contrast_);
}

void ControlPanel::onBrightnessChanged(int & brightness_)
{
	ofLogVerbose(__func__) << brightness_;
	rpiCameraVideoGrabber->setBrightness(brightness_);
}

void ControlPanel::onSaturationChanged(int & saturation_)
{
	ofLogVerbose(__func__) << saturation_;
	rpiCameraVideoGrabber->setSaturation(saturation_);
}
void ControlPanel::onFrameStabilizationChanged(bool & doFrameStabilization)
{
	rpiCameraVideoGrabber->setFrameStabilization(doFrameStabilization);
}

void ControlPanel::onColorEnhancementChanged(bool & doColorEnhancement)
{
	rpiCameraVideoGrabber->setColorEnhancement(doColorEnhancement);
}

void ControlPanel::onLEDEnabledChanged(bool & doEnableLED)
{
	rpiCameraVideoGrabber->setLEDStatus(doEnableLED);
}

