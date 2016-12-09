# [GAmuza](http://www.gamuza.cc) [![GAmuza](http://gamuza.d3cod3.org/graphics/gaLogo.png)](http://www.gamuza.cc)


# About

[![GAmuza](http://gamuza.d3cod3.org/graphics/gaIDE.jpg)](http://www.gamuza.cc)

The original idea was to make creative coding easier; then, usually jumping from [Processing](http://www.processing.org) to [OF](http://www.openframeworks.cc), always trying new libraries/addons, the desire was, having OF with a Processing like IDE, + a bunch of GUI modules to avoid the technical programming stuff like Computer Vision, Audio Analysis, Arduino communication, etc..

So, this is it, this is GAmuza, made with OF, inspired by Processing, binding the (almost) entire OF language v.0.8.4 with his official addons included, the entire OpenGL 1.1 language, a bunch of other addons , and the small GAmuza framework of functions and GUI modules to make creative coding a lot more easier, all of it embedded into a slight modified Lua scripting environment.

# Licence

The code in this repository is available under the [MIT License](https://secure.wikimedia.org/wikipedia/en/wiki/Mit_license).

Copyright (c) [2008-2015] [Emanuele Mazza]

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


# Download

Last Release - GAmuza 0595 [here](http://gamuza.d3cod3.org/downloads/GAmuza-0595-OSX.zip)


# Installation

Just drag to Application folder.

# Dependencies

## OF

openFrameworks 0.8.4 with this [patch](https://github.com/d3cod3/GAmuza/blob/master/GA_ofPatch.patch) and all the official addons.

## Additional Libraries

* Boost Library & headers


## OFXADDONS

Due to a lot of modification applied to most of them, are all included in this repo in src/ofxAddons/

## Frameworks

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

openFrameworks 0.8.4

# Compilation

Apple LLVM Compiler 4.1, for 32-bit architecture using OS X 10.7 base sdk.

# Sketching (Live Coding)

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

### OF 0.8.4 language **EXCLUDING**:

 * ofArduino  --> managed from Arduino GUI module + GAmuza framework related functions
 * ofSoundStream -- managed from AudioAnalysis GUI module + GAmuza framework related functions
 * ofLog, ofLogFatalError, ofLogError, ofLogVerbose, ofLogWarning, ofLogNotice --> covered by GAmuza console panel
 * ofPoint --> use ofVec3f instead
 * ofRendererCollection
 * ofEvents
 * ofPtr


### OF 0.8.4 official addons

### GAmuza framework

 * functions list [here](https://github.com/d3cod3/GAmuza/blob/master/gaFunctionsList)

### OPENGL 1.1

 * language [reference](http://www.talisman.org/opengl-1.1/Reference.html)

## Modules

 * ARDUINO

[![GAmuza](http://gamuza.d3cod3.org/graphics/arduinoModule.jpg)](http://www.gamuza.cc)

 * AUDIO ANALYSIS

[![GAmuza](http://gamuza.d3cod3.org/graphics/audioAnalysisModule.jpg)](http://www.gamuza.cc)

 * COMPUTER VISION from cameras (wrapped within a class and available from code)

[![ScreenShot](http://gamuza.d3cod3.org/graphics/cameraTrackingModule.jpg)](http://www.d3cod3.org/gamuza/footage/gaComputerVision.mov)

 * COMPUTER VISION from Kinect 	(wrapped within a class and available from code)

[![GAmuza](http://gamuza.d3cod3.org/graphics/kinectModule.jpg)](http://www.gamuza.cc)

 * TIMELINE

[![GAmuza](http://gamuza.d3cod3.org/graphics/timelineModule.jpg)](http://www.gamuza.cc)

 * MAPPER

 [![GAmuza](http://gamuza.d3cod3.org/graphics/mapperModule.jpg)](http://www.gamuza.cc)


# Known issues

A lot


# Contribute

Actually GAmuza v1.0 is in development (this repo) and is not finished yet, but this is just a matter of time, the real deal is porting this project to Linux and Windows (just for mac now, compatible from osx 10.7 Lion), so, if anyone interested in join me in this project, is more than welcome!!


# Version history

=======
## v1.0  |  Rel. 0435

* Updated GAmuza to OF 0.8.4 last official release
* a lot of bug fixing

## v1.0  |  Rel. 0433

* Updated XCode project, now compiling with Apple LLVM Compiler 4.1, goodbye old GCC 4.2!!!
* ofxTwitter fixed & updated to API 1.1, included OAuth and JSON parser addons
* small bug fixing

## v1.0  |  Rel. 0432

* Fixed wrapper
* general bug fixing

## v1.0  |  Rel. 0431

* Fixed Preview aspect ratio texture scaling
* Added export to HTML (simple script documentation)
* Added Archive sketch (save everything to .zip)
* Cleaning editor interface

## v1.0  |  Rel. 0426

* initial version
