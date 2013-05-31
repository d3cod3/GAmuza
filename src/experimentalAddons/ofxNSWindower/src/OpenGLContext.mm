//
//  OpenGLContext.m
//
//  Created by Will Gallia on 14/04/2012.
//  Copyright 2012 . All rights reserved.
//

#include "ofMain.h"
#import <AppKit/NSOpenGL.h>
#import <OpenGL/OpenGL.h>

#import "OpenGLContext.h"

@implementation OpenGLContext

- (id) init {
	
	if (self = [super init]) {
		
		pixelFormat = nil;
		context = nil;
		
		GLuint attrs[] = 
		{
			NSOpenGLPFAWindow,
			NSOpenGLPFAAccelerated,
			NSOpenGLPFADoubleBuffer,
			NSOpenGLPFAColorSize, 24,
			NSOpenGLPFAAlphaSize, 8,
			NSOpenGLPFADepthSize, 24,
			NSOpenGLPFAMinimumPolicy,
			0
		};
		
		pixelFormat = [[NSOpenGLPixelFormat alloc] 
									 initWithAttributes:(NSOpenGLPixelFormatAttribute*) attrs];
		
		if (pixelFormat == nil) {
			NSLog(@"non valid pixel format");
			exit(1);
		}
		else {
			context = [[NSOpenGLContext alloc] initWithFormat:pixelFormat shareContext:nil];
		}
		
		//set this context to current...
		//we need to do this to init GLEW
		[context makeCurrentContext];
		
		//init GLEW
		glewExperimental = GL_TRUE;
		GLenum err = glewInit();
		if (GLEW_OK != err) {
			NSLog(@"GLEW init error... bailing");
			exit(1);
		}
		
		//init oF
		ofSetCurrentRenderer(ofPtr<ofBaseRenderer>(new ofGLRenderer(false)));
		
		
	}
	return self;	
}

- (NSOpenGLPixelFormat*) pixelFormat {
	return pixelFormat;
}

- (NSOpenGLContext*) context {
	return context;
}

+ (OpenGLContext*) instance {
	
	static OpenGLContext *sharedContext = nil;
	
	if (sharedContext == nil) {
		sharedContext = [[OpenGLContext alloc] init];
		
	}
	return sharedContext;
}



@end
