//  Modified by Seth Hunter (hunters@mit.edu) on 8/14/12. 
//  2012 MIT Media Lab - use it as you please. 
//

#include "ofxQTKitRecorder.h"  
#include "ofImage.h"  
  
ofxQTKitRecorder::ofxQTKitRecorder() :  
    qtMovie(nil),  
    insertion(nil),
    previousFrame(),  
    previewFrameTimestampMS(0)  
{  
    audioFileWritten = false;
}  
  
ofxQTKitRecorder::~ofxQTKitRecorder() {  
    if ((qtMovie != nil) && (!audioFileWritten)) {  
        if (previousFrame.isAllocated()) {  
            unsigned long nowTimestampMS = ofGetSystemTime();  
            assert(nowTimestampMS >= previewFrameTimestampMS);  
            unsigned long previousFrameDurationMS = nowTimestampMS - previewFrameTimestampMS;  
            if (previousFrameDurationMS > 0) {  
                outputFrame(previousFrame, previousFrameDurationMS);  
            }  
        }  
        flushToFile();  
        [qtMovie release];  
        qtMovie = nil;  
        [insertion release];
        insertion = nil; 
    }  
}  


void ofxQTKitRecorder::releaseRecording() {
    if(qtMovie != nil) {
        [qtMovie release];  
        qtMovie = nil; 
        insertion = nil; 
        audioFileWritten = false;
        previewFrameTimestampMS = ofGetSystemTime(); 
    }
}
  
void ofxQTKitRecorder::setup(std::string filePath) {  
    NSError* error = nil;  
    qtMovie = [[QTMovie alloc] initToWritableFile:[NSString stringWithUTF8String:filePath.c_str()] error:&error];  
    
    if(error != nil) {
        printf("ERROR %s: ", error.description.UTF8String);
    }
    
    if ((qtMovie == nil) && (error != nil)) {  
        NSLog(@"%@", [error localizedDescription]);  
    }  
    [qtMovie setAttribute:[NSNumber numberWithBool:YES] forKey:QTMovieEditableAttribute];  
}  
  
void ofxQTKitRecorder::addFrame(ofPixels& framePixels) {  
    if (qtMovie != nil) {  
        unsigned long nowTimestampMS = ofGetSystemTime();  
        if (previousFrame.isAllocated()) {  
            assert(nowTimestampMS >= previewFrameTimestampMS);  
            unsigned long previousFrameDurationMS = nowTimestampMS - previewFrameTimestampMS;  
            if (previousFrameDurationMS > 0) {  
                outputFrame(previousFrame, previousFrameDurationMS);  
            }  
        }  
        previousFrame = framePixels;  
        previewFrameTimestampMS = nowTimestampMS;  
    }   else {
        printf("QTMovie is NIL");
    }
}  


void ofxQTKitRecorder::loadAudioTrack(char* filename) {
    
    
    printf("\nLOADING audio track %s to movie.",filename); 
    
    NSDictionary *editableAttribute = [NSDictionary dictionaryWithObject:[NSNumber numberWithBool:YES] forKey:QTMovieEditableAttribute];
    
    // load and prepare the insertion
    NSString* fileString = [NSString stringWithCString: filename];
    NSError* myError = nil;

    //NSURL also works just fine, but I'm not sure if the data is copied with this method.
    //insertion = [QTMovie movieWithURL:[NSURL fileURLWithPath:fileString] error:&myError];

    insertion = [QTMovie movieWithFile:fileString error:&myError]; //cant find it. 
    [insertion retain];   //needed to add it to the pool, make sure to release later. 
    [insertion setMovieAttributes:editableAttribute];

}



void ofxQTKitRecorder::addAudioTrack(char* videoPath) {

    //error comes up if it can't find the data referance. 
    if(insertion == nil) {
        printf("\nCannot find an AudioTrack to add");         
    }
    
    //method using Insert Track: (also does not embed it in the same file)
    NSArray *audioTracks = [insertion tracksOfMediaType:QTMediaTypeSound];
    QTTrack *audioTrack = nil;
    if( [audioTracks count] > 0 ){    
        audioTrack = [audioTracks objectAtIndex:0];
    }
    
    QTMedia *audioTrackMedia = audioTrack.media;
    
    if( audioTrack ){   
        
        QTTimeRange totalRange;    
        totalRange.time = QTZeroTime;    
        totalRange.duration = [[insertion attributeForKey:QTMovieDurationAttribute] QTTimeValue];
        [qtMovie insertSegmentOfTrack:audioTrack timeRange:totalRange atTime:QTZeroTime];
        [qtMovie updateMovieFile];  
    }

    
    // same method using insertSegment of Movie, decided not to use it because it might insert two tracks. 
    /*
    QTTimeRange sourceRange = QTMakeTimeRange( QTZeroTime, [insertion duration] );
    QTTimeRange destinationRange = sourceRange;
    [qtMovie insertSegmentOfMovie:insertion fromRange:sourceRange scaledToRange:destinationRange];
    [qtMovie updateMovieFile];  
      */
    
    
    // The audio file is not copied into the movie - its referenced. Therefore I need to save a new flattened movie with a different filename. 
    NSDictionary *flattenAttributes = [NSDictionary dictionaryWithObjectsAndKeys: [NSNumber numberWithBool:YES], QTMovieFlatten, nil]; 
    NSString* videoPathStr = [NSString stringWithCString: videoPath];
    NSError* writeError = nil;
    [qtMovie writeToFile:videoPathStr withAttributes:flattenAttributes error:&writeError];
    
    if(writeError != nil) {
        [NSApp presentError:writeError];
    }

    audioFileWritten = true; 
    
#if !__LP64__
    //[audioTrack autorelease];		// This causes a crash - says it's already freed, so the bug below must have been fixed. 
#endif
    
}


void ofxQTKitRecorder::removeTempFiles(char* audioPath,char* videoPath) {
     if( remove( audioPath ) != 0 ) printf( "\nError deleting audio file" );
     else printf( "\n Temp audio file successfully deleted" );
    
    if( remove( videoPath ) != 0 ) printf( "\nError deleting video file" );
    else printf( "\n Temp video file successfully deleted" );
}
  
void ofxQTKitRecorder::flushToFile() {  
    if (qtMovie != nil) {  
        [qtMovie updateMovieFile];  
    }  
}  
  
void ofxQTKitRecorder::outputFrame(ofPixels& framePixels, unsigned long frameDurationMS) {  
    assert(frameDurationMS > 0);  
    QTTime duration = QTMakeTimeWithTimeInterval(static_cast<double>(frameDurationMS) / 1000.0);  
  
    NSDictionary* attributesDictionary =  
        [NSDictionary dictionaryWithObjectsAndKeys:  
            @"jpeg", QTAddImageCodecType,  
            [NSNumber numberWithLong:codecNormalQuality], QTAddImageCodecQuality,  
            nil];  
  
    int imageWidth = framePixels.getWidth();  
    int imageHeight = framePixels.getHeight();  
    int bitsPerChannel = framePixels.getBitsPerChannel();  
    int numChannels = framePixels.getNumChannels();  
    int bitsPerPixel = framePixels.getBitsPerPixel();  
    int bytesPerRow = framePixels.getBytesPerPixel() * imageWidth;  
    unsigned char* pixelsPointer = framePixels.getPixels();  
    NSBitmapImageRep* imageRep =  
        [[NSBitmapImageRep alloc]  
            initWithBitmapDataPlanes:&pixelsPointer  
            pixelsWide:imageWidth  
            pixelsHigh:imageHeight  
            bitsPerSample:bitsPerChannel  
            samplesPerPixel:numChannels  
            hasAlpha:NO  
            isPlanar:NO  
            colorSpaceName:(bitsPerPixel <= 8) ? NSDeviceWhiteColorSpace : NSDeviceRGBColorSpace  
            bytesPerRow:bytesPerRow  
            bitsPerPixel:bitsPerPixel];  
    [imageRep autorelease];  
    NSImage* frameNSImage = [[[NSImage alloc] initWithSize:NSMakeSize(imageWidth, imageHeight)] autorelease];  
    [frameNSImage addRepresentation:imageRep];  
    [qtMovie addImage:frameNSImage forDuration:duration withAttributes:attributesDictionary];  
}



//****************** RESEARCH/EXAMPLES ON QT KIT BELOW *******

// Possible to also do this with AVFoundation.framework: http://stackoverflow.com/questions/9213088/qtkit-merge-two-videos-with-different-width-and-height 


//This is pretty straightforward with QTKit. You load your audio data in a QTMovie object and extract out the audio track. Then you can add that track object to your QTMovie object with the video in it. Something like this:

//audioTrackMovie is the QTMovie object that contains the audio track. movie is the QTMovie object that contains the video track.


// from: http://osdir.com/ml/quicktime-api/2009-04/msg00122.html  

//Someone else added the video to the audio (same difference): 

//QTTimeRange videoRange = QTMakeTimeRange(QTZeroTime, [videoTrkOnlyMovie duration]);
//[audioTrkOnlyMovie insertSegmentOfTrack:[videoTrkOnlyMovie firstVideoTrack] timeRange:videoRange atTime:QTZeroTime];

//additional post in of forum: http://forum.openframeworks.cc/index.php?topic=8145.0  

/*
 
 void ofxQTKitVideoSaver::addAudioTrack(QTMovie *movie, QTMovie *audioTrackMovie) {
 
 //extracts all audio tracks of type QTMediaTypeSound
 NSArray *audioTracks = [audioTrackMovie tracksOfMediaType:QTMediaTypeSound];
 QTTrack *audioTrack = nil;
 
 //gets the first audio track from the audioTrackMovie (a QTMovie object where we only saved the audio)
 if( [audioTracks count] > 0 ) {
 audioTrack = [audioTracks objectAtIndex:0];  
 }
 
 //then it inserts the audio track
 if( audioTrack )  {    
 QTTimeRange totalRange;    
 totalRange.time = QTZeroTime;    
 totalRange.duration = [[audioTrackMovie attributeForKey:QTMovieDurationAttribute] QTTimeValue];
 
 //insert segment of Movie or of Track
 [movie insertSegmentOfTrack:audioTrack timeRange:totalRange atTime:QTZeroTime];
 }
 }
 
 */

/*
 I have found a bug in Quicktime that has recently (1/25/11) been confirmed by Apple and I just wanted to let people know so some may benefit from the week worth of time I spent trying to find and resolve this problem.
 
 If you use QTMovies insertSegmentOfTrack:timeRange:atTime:, there is a memory leak that can wreak havoc when calling it a lot of times. If you are running a 64-bit app (and QTKitServer automatically starts up), this problem does not exist. It only happens when running a 32-bit QT app. The track returned by this method needs to be manually autoreleased like this:
 
 QTTrack* vtrk = [movie insertSegmentOfTrack:videoTrack timeRange:videoTrkSegmentSize atTime:videoTrkTotalDuration];
 #if !__LP64__
 [vtrk autorelease];		// Resolves the bug in 32-bit only
 #endif
 */




