
#include "gaTimeline.h"


//--------------------------------------------------------------
gaTimeline::gaTimeline(int screenW, int screenH){
    // STORE resource files inside bundle
    CFURLRef appUrl = CFBundleCopyBundleURL(CFBundleGetMainBundle());
    CFStringRef appPath = CFURLCopyFileSystemPath(appUrl, kCFURLPOSIXPathStyle);
    const char *appPathChars = [(NSString *) appPath UTF8String];
    string appPathStr = string(appPathChars); // the path to the .app dir
    CFRelease(appUrl);
    CFRelease(appPath);
    
    CFURLRef resourceUrl = CFBundleCopyResourcesDirectoryURL(CFBundleGetMainBundle());
    CFStringRef resourcePath = CFURLCopyFileSystemPath(resourceUrl, kCFURLPOSIXPathStyle);
    const char *resourcePathChars = [(NSString *) resourcePath UTF8String];
    string resourcePathStr = string(resourcePathChars); // the path from the .app dir to the resources folder
    CFRelease(resourcePath);
    CFRelease(resourceUrl);
    
    string newPath = appPathStr + "/" + resourcePathStr + "/"; // the absolute path to the resources folder
    
    ofSetDataPathRoot(newPath); // tell OF to look for resources here
    
    scrW = screenW;
    scrH = screenH;
    
}

//--------------------------------------------------------------
gaTimeline::~gaTimeline(){
    
}

//--------------------------------------------------------------
void gaTimeline::setup(){
    
    timeline.setup(scrW,scrH);
    timeline.setDurationInSeconds(10);
    
    timeline.addCurves("curves", ofRange(0, 255));
	timeline.addBangs("bangs");
	timeline.addFlags("flags");
    timeline.addColors("colors");
	timeline.addLFO("lfo");
	timeline.addSwitches("switches");
    
    timeline.setPageName("Page 1");
    timeline.addPage("Page 2");
	timeline.setCurrentPage(0);
    
	timeline.enableSnapToOtherKeyframes(false);
	timeline.setLoopType(OF_LOOP_NORMAL);
	
	ofAddListener(timeline.events().bangFired, this, &gaTimeline::bangFired);
}

//--------------------------------------------------------------
void gaTimeline::update() {
	

}

//--------------------------------------------------------------
void gaTimeline::draw() {
	if(timeline.isSwitchOn("switches")){
		ofBackground(timeline.getColor("colors"));
	}
	else{
		ofBackground(255*.15);
	}
	timeline.draw();
    
    
}

//--------------------------------------------------------------
void gaTimeline::bangFired(ofxTLBangEventArgs& args){
	//cout << "bang fired!" << args.flag << endl;
}

//--------------------------------------------------------------
void gaTimeline::keyPressed(int key) { 
	
}

//--------------------------------------------------------------
void gaTimeline::keyReleased(int key) { 
	
}

//--------------------------------------------------------------
void gaTimeline::mouseMoved(int x, int y) { 
	
}

//--------------------------------------------------------------
void gaTimeline::mouseDragged(int x, int y, int button) {
	
}

//--------------------------------------------------------------
void gaTimeline::mousePressed(int x, int y, int button) { 
	
}

//--------------------------------------------------------------
void gaTimeline::mouseReleased() { 
	
}

//--------------------------------------------------------------
void gaTimeline::mouseReleased(int x, int y, int button ){ 
	
}

//--------------------------------------------------------------
void gaTimeline::mouseScrolled(float x, float y) { 
	
}

//--------------------------------------------------------------
void gaTimeline::windowResized(int w, int h){
    timeline.timelineResizeWithWindow(w,h);
}

//--------------------------------------------------------------
void gaTimeline::dragEvent(ofDragInfo dragInfo){
    
}

