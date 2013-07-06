# [GAmuza](http://www.gamuza.cc) [![GAmuza](http://gamuza.d3cod3.org/graphics/gaLogo.png)](http://www.gamuza.cc)


# About

[![GAmuza](http://gamuza.d3cod3.org/graphics/gaIDE.jpg)](http://www.gamuza.cc)

The original idea was to make creative coding easier; then, usually jumping from [Processing](http://www.processing.org) to [OF](http://www.openframeworks.cc), always trying new libraries/addons, the desire was, having OF with a Processing like IDE, + a bunch of GUI modules to avoid the technical programming stuff like Computer Vision, Audio Analysis, Arduino communication, etc..

So, this is it, this is GAmuza, made with OF, inspired by Processing, binding the (almost) entire OF language v.0.7.4 with his official addons included, the entire OpenGL 1.1 language, a bunch of other addons (list [here](https://github.com/d3cod3/GAmuza/blob/master/bindedAddons)), and the small GAmuza framework of functions and GUI modules to make creative coding a lot more easier, all of it embedded into a slight modified Lua scripting environment.

# Licence

The code in this repository is available under the [MIT License](https://secure.wikimedia.org/wikipedia/en/wiki/Mit_license).

Copyright (c) [04/06/2013] [Emanuele Mazza]

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


# Download

Last version (this one in development) ready soon for download

Older versions [here](http://gamuza.d3cod3.org/download/)


# Installation

Just drag to Application folder.

# Dependencies

## OF

openFrameworks 0074 with this [patch](https://github.com/d3cod3/GAmuza/blob/master/GA_ofPatch.patch) and all the official addons.

## Additional Libraries

* Boost Library & headers


## OFXADDONS

A list [here](https://github.com/d3cod3/GAmuza/blob/master/gaAddonsList) of all the addons needed.
Due to a lot of modification applied to most of them, are all included in this repo in src/experimentalAddons/

## Frameworks

* [BWToolkitFramework.framework](http://brandonwalkin.com/bwtoolkit/)  
* [Sparkle.framework](https://github.com/andymatuschak/Sparkle/wiki): [project page](http://sparkle.andymatuschak.org/)
* [Syphon.framework](http://syphon.v002.info/)

* Accelerate.framework
* AGL.framework
* AppKit.framework
* ApplicationServices.framework
* AudioToolbox.framework
* AudioUnit.framework
* Carbon.framework
* Cocoa.framework
* CoreAudio.framework
* CoreAudioKit.framework
* CoreData.framework
* CoreFoundation.framework
* CoreMIDI.framework
* CoreServices.framework
* CoreVideo.framework
* Foundation.framework
* IOKit.framework
* OpenAL.framework
* OpenGL.framework
* QTKit.framework
* QuickTime.framework
* ScriptingBrigde.framework


# Compatibilities

openFrameworks 0074

# Compilation

Compile with LLVM GCC 4.2 (NOT Apple LLVM Compiler 4.1), for 32-bit architecture using OS X 10.7 base sdk.

# Sketching (like every Processing's child do)

### These are some of the GAmuza IDE futures:

* **Line Numbering**
* **Syntax Coloring**
* **Code Completion**
* **Multi Tab sketch editor (Processing like)**
* **Live Coding**
* **Various GUI Modules (Audio Analysis, Computer Vision, Arduino, Timeline)**
* **Various tools (RGB/HSV Color selector, Custom Console)**

## Language
```c++

/* 
   
 GAmuza 1.0 examples 
 ---------------------
 Basics/emptyExample.ga
 
 Draw a flicking circle over mouse position.
 
 created by n3m3da | www.d3cod3.org
 
*/

function setup()
	ofSetCircleResolution(50)
end

function update()
    
end

function draw()
    gaBackground(0.0,1.0)

    ofSetColor(255)
    ofCircle(gaMouseX(),gaMouseY(),ofRandom(20,200))
end

```
 
GAmuza scripting language is based on [LUA](http://www.lua.org/), integrated in OF with a modified version of [ofxLua](https://github.com/danomatika/ofxLua) addon; a patched version of LUA 5.1 is compiled as a static library, and the entire binding of OF 0.7.4 with all the ofxAddons is made through [LUABIND](http://www.rasterbar.com/products/luabind.html), while the binding of OpenGL 1.1 is coded directly from LUA using [luaglut](https://github.com/LuaDist/luaglut).

These are the most important LUA 5.1 patches

* **C/C++ style comments**						[see the patch](http://lua-users.org/files/wiki_insecure/power_patches/5.2/cppcomt.diff)
* **Compound Assignment Operators**				[see the patch](http://lua-users.org/files/wiki_insecure/power_patches/5.2/increment.patch)
* **Accepts both ~= and != for comparison**		[see the patch](http://lua-users.org/files/wiki_insecure/power_patches/5.1/bitwise_operators_5.1.4_1.patch)
* **Lua Bit Operation Module** 					[http://bitop.luajit.org/](http://bitop.luajit.org/)

## Bindings

### LUA language

LUA 5.1 programming environment [manual](http://www.lua.org/manual/5.1/manual.html)

### OF 0.7.4 language **EXCLUDING**:

 * ofArduino  --> managed from Arduino GUI module + GAmuza framework related functions
 * ofVideoGrabber --> managed from ComputerVision GUI module + GAmuza framework related functions
 * ofSoundStream -- managed from AudioAnalysis GUI module + GAmuza framework related functions
 * ofLog, ofLogFatalError, ofLogError, ofLogVerbose, ofLogWarning, ofLogNotice --> covered by GAmuza console panel
 * ofPoint --> use ofVec3f instead
 * ofRendererCollection
 * ofEvents
 * ofPtr
 

### OF 0.7.4 official addons

### others OFXADDONS

 * list [here](https://github.com/d3cod3/GAmuza/blob/master/bindedAddons)

### GAmuza framework

 * work in progress

### OPENGL 1.1

 * language [reference](http://www.talisman.org/opengl-1.1/Reference.html)

## Modules

 * ARDUINO					- READY
 * AUDIO ANALYSIS 			- READY
 * COMPUTER VISION 			- working on it
 * OSC 						- NOT READY YET
 * TIMELINE 				- READY


# Known issues

none


# Contribute

Actually GAmuza 1.0 is in development (this repo) and is not finished yet, but this is just a matter of time, the real deal is porting this project to Linux and Windows (just for mac now, compatible from osx 10.7 Lion), so, if anyone interested in join me in this project, is more than welcome!!

# NOW Working on:

* The COMPUTER VISION GUI Module

# Version history

## v1.1
* 

## v1.0
 
* initial version
