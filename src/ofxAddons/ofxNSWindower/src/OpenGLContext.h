//
//  OpenGLContext.h
//
//  Created by Will Gallia on 14/04/2012.
//  Copyright 2012 . All rights reserved.
//

//this is a singleton class encapsulating a 
//shared NSOpenGLContext

//the code was based on the example in:
//OpenGL Programming on Mac OS X p.141

//there are extra calls in the contructor to initialise 
//the openFrameworks renderer

#import <Cocoa/Cocoa.h>

@interface OpenGLContext : NSObject {
@private
	NSOpenGLPixelFormat *pixelFormat; 
	NSOpenGLContext *context;
}

- (NSOpenGLPixelFormat*) pixelFormat;
- (NSOpenGLContext*) context;
+ (OpenGLContext*) instance;

@end