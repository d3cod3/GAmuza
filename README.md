# [GAmuza](http://www.gamuza.cc) [![GAmuza](http://gamuza.d3cod3.org/graphics/gaLogo.png)](http://www.gamuza.cc)


# About

[![GAmuza](http://gamuza.d3cod3.org/graphics/gaIDE.jpg)](http://www.gamuza.cc)

The original idea was to making creative coding easier; then, usually jumping from [Processing](http://www.processing.org) to [OF](http://www.openframeworks.cc), always trying new libraries/addons, the desire was, having OF with a Processing like IDE, + a bunch of GUI modules to avoid (if you prefer), the technical programming stuff like Computer Vision, Audio Analysis, Arduino communication, etc..

So, this is it, this is GAmuza, made with OF, son of Processing, binding the (almost) entire OF language v.0.7.4, plus OpenGL 1.1 (just for simple opengl drawing stuff), plus som custom functions from GAmuza to making creative coding even easier than OF (is it's possible).

# Licence

The code in this repository is available under the [MIT License](https://secure.wikimedia.org/wikipedia/en/wiki/Mit_license).

Copyright (c) [17/06/2013] [Emanuele Mazza]

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

 openFrameworks 0074 with this [patch](https://github.com/d3cod3/GAmuza/gaPatch.patch) and all the official addons.


 ## OFXADDONS

 A list [here](https://github.com/d3cod3/GAmuza/gaAddonsList) of all the addons needed.
 Due to a lot of modification applied to most of them, are all included in this repo in src/experimentalAddons/

 ## Frameworks

 	* **[BWToolkitFramework.framework](http://brandonwalkin.com/bwtoolkit/)** 
 	* **[Sparkle.framework](http://sparkle.andymatuschak.org/)** and the [github repo](https://github.com/andymatuschak/Sparkle/wiki)**

 	* **Accelerate.frameworks**
 	* **AGL.frameworks**
 	* **AppKit.frameworks**
 	* **ApplicationServices.frameworks**
 	* **AudioToolbox.frameworks**
 	* **Carbon.frameworks**
 	* **Cocoa.frameworks**
 	* **CoreAudio.frameworks**
 	* **CoreData.frameworks**
 	* **CoreFoundation.frameworks**
 	* **CoreMIDI.frameworks**
 	* **CoreServices.frameworks**
 	* **CoreVideo.frameworks**
 	* **Foundation.frameworks**
 	* **IOKit.frameworks**
 	* **OpenAL.frameworks**
 	* **OpenGL.frameworks**
 	* **QTKit.frameworks**
 	* **QuickTime.frameworks**

 ## 

# Compatibilities

openFrameworks 0074

# Compilation

Compile with LLVM GCC 4.2 (NOT Apple LLVM Compiler 4.1), for 32-bit architecture using OS X 10.7 base sdk.

# Sketching (like every Processing's son do)

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
   
 GAmuza 0.4.1 examples 
 ---------------------
 Basics/emptyExample.ga
 
 The empty GAmuza script (you can start from here).
 
 created by n3m3da | www.d3cod3.org
 
*/

function setup()

end

function update()
    
end

function draw()
    gaBackground(0.0,1.0)
end

```
 

## Bindings


## Modules


# Known issues

none


# Contribute

Actually GAmuza 1.0 is in development (this repo) and is not finished yet, but this is just a matter of time, the real deal is porting this project to Linux and Windows (just for mac now, compatible from osx 10.7 Lion), so, if anyone interested in join me in this project, is more than welcome!!

# Working on:

 * The TIMELINE GUI Module, making ofxNSWindower fully compatible with OF Events and the last version of [ofxTimeline](https://github.com/YCAMInterlab/ofxTimeline)

# Version history

## v1.1
 * 

## v1.0
 
 * initial version
