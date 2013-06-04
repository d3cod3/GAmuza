
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
	
	ofAddListener(timeline.events().bangFired, this, &gaTimeline::bangFired);
}

//--------------------------------------------------------------
void gaTimeline::update() {
	

}

//--------------------------------------------------------------
void gaTimeline::draw() {
    ofBackground(255*.15);
	timeline.draw();
}

//--------------------------------------------------------------
void gaTimeline::bangFired(ofxTLBangEventArgs& args){
    actualBang = args.flag;
     
    // timeline.getVideoPlayer("Video")->getPlayer()->setFrame(currentRenderFrame);
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

