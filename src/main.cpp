#include "ofMain.h"
#include "ofGLProgrammableRenderer.h"

//#define USE_TEST_APP
#define USE_REMOTE_APP

#ifdef USE_TEST_APP
#include "testApp.h"
int main()
{
	ofSetLogLevel(OF_LOG_VERBOSE);
	ofSetCurrentRenderer(ofGLProgrammableRenderer::TYPE);
	ofSetupOpenGL(1280, 720, OF_WINDOW);
	ofRunApp( new testApp());
}
#endif


#ifdef USE_REMOTE_APP
#include "remoteApp.h"
int main()
{
	ofSetLogLevel(OF_LOG_VERBOSE);
	ofSetCurrentRenderer(ofGLProgrammableRenderer::TYPE);
	ofSetupOpenGL(1280, 720, OF_WINDOW);
	ofRunApp( new remoteApp());
}
#endif

