//
//  ofxQTKitAVScreenRecorder.m
//  ofxQTKitAVScreenRecorder
//
//  Created by Seth Hunter (hunters@mit.edu) on 8/14/12. 
//  2012 MIT Media Lab - use it as you please. 
//

#import "ofxQTKitAVScreenRecorder.h"


ofxQTKitAVScreenRecorder::ofxQTKitAVScreenRecorder() {  
    stopAddingFrames = false; 
    isRecording = false;
    addAudioTrack = 0; 

}  

ofxQTKitAVScreenRecorder::~ofxQTKitAVScreenRecorder() {  
    
}

string* ofxQTKitAVScreenRecorder::listAudioDevices() {
    vector<string> devs = audioTrack.listAudioDevices();
    string* _temp = new string[devs.size()];
    for(int i=0;i<devs.size();i++){
        _temp[i] = devs[i];
    }
    return _temp;
    
}

string* ofxQTKitAVScreenRecorder::listAudioCodecs() {
    vector<string> cods = audioTrack.listAudioCodecs();
    string* _temp = new string[cods.size()];
    for(int i=0;i<cods.size();i++){
        _temp[i] = cods[i];
    }
    return _temp;
}

void ofxQTKitAVScreenRecorder::setup(string device, string compression) {
    initAudio(device,compression); 
}

void ofxQTKitAVScreenRecorder::initAudio(string device, string compression) {
    //initialize the audio source
    audioTrack.initGrabberWithoutPreview();
    audioTrack.setAudioDeviceID(device); // "Built-in Microphone"
    audioTrack.setAudioCodec(compression); // "QTCompressionOptionsVoiceQualityAACAudio"
    audioTrack.initRecording(); 
}


void ofxQTKitAVScreenRecorder::initAVRecording() {
    
    //temp audio file
    char $audiofilename[1024];
	time_t now = time(NULL);
	struct tm *ts = localtime(&now);
	strftime($audiofilename, sizeof($audiofilename), "%m_%d_%H_%M_%S_audio.mov", ts);
    audioFullPath = string($audiofilename);    
    audioTrack.startRecording(audioFullPath);
    
    //temp video file
    char $videofilename[1024];
	now = time(NULL);
	struct tm *ts2 = localtime(&now);
	strftime($videofilename, sizeof($videofilename), "%m_%d_%H_%M_%S_video.mov", ts2);
    videoFullPath = string($videofilename);
    recorder.setup(videoFullPath);
    
    //final output combining both files. 
    char $temp[1024];
	now = time(NULL);
	struct tm *ts3 = localtime(&now);
	strftime($temp, sizeof($temp), "%m_%d_%H_%M_%S_Recording.mov", ts3);
    selfContainedFullPath = string($temp);
    
    isRecording = true; 
}

void ofxQTKitAVScreenRecorder::startNewRecording() {
    if(!isRecording) {
        recorder.releaseRecording();
        initAVRecording();
        stopAddingFrames = false;
    } else {
        printf("/n AUDIO RECORDER: a recording is already in progress "); 
    }
}

void ofxQTKitAVScreenRecorder::update() {
    doWeNeedToAddAudio();
}

void ofxQTKitAVScreenRecorder::addFrame(ofPixels& framePixels) {
    if(!stopAddingFrames) recorder.addFrame(framePixels);
}

void ofxQTKitAVScreenRecorder::exit() {
    if(!stopAddingFrames) {
        finishMovie(true); 
    }
}

//3 second process is safe to output most files in my testing (I couldn't get event handlers working)
void ofxQTKitAVScreenRecorder::doWeNeedToAddAudio() {
    if(addAudioTrack > 0) {
        addAudioTrack++; 
        //delay adding the audio track by 1 second so that the threaded QTKit can load the flushed audio
        if(addAudioTrack == 24) {
            recorder.loadAudioTrack((char*)audioFullPath.c_str());
        }
        //wait one more second and append the audio track to the video track and save as a new movie. 
        else if(addAudioTrack == 48) {
            recorder.addAudioTrack((char*)selfContainedFullPath.c_str());
        }
        //one last second then remove the temp files. 
        else if(addAudioTrack == 72) {
            recorder.removeTempFiles((char*)audioFullPath.c_str(), (char*)videoFullPath.c_str());
            addAudioTrack=0;
            isRecording = false;
            printf("\n AV Recorder: File has been recorded sucessfully as: %s", selfContainedFullPath.c_str());
        }
    }
}


void ofxQTKitAVScreenRecorder::finishMovie(bool exiting) {
    if(isRecording) {
        audioTrack.stopRecording(); 
        recorder.flushToFile();
        if(exiting) {
            ofSleepMillis(1000);
            recorder.addAudioTrack((char*)videoFullPath.c_str());
        } else {
            stopAddingFrames = true;  //toggle prevents the movie from accumulating anymore. 
            addAudioTrack = 1;
        }
    } else {
        printf("\nAUDIO RECORDER: No recording is available to finish.");
    }
}
