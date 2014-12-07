/********************************************************************************** 
 
 Copyright (C) 2012 Syed Reza Ali (www.syedrezaali.com)
 
 Permission is hereby granted, free of charge, to any person obtaining a copy of
 this software and associated documentation files (the "Software"), to deal in
 the Software without restriction, including without limitation the rights to
 use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 of the Software, and to permit persons to whom the Software is furnished to do
 so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 
 **********************************************************************************/

#ifndef OFX_GENERATIVE
#define OFX_GENERATIVE

#include "ofxCircle.h"
#include "ofxGenericShape.h"
#include "ofxSuperShape.h"

#include "ofxSpring.h"
#include "ofxParticle.h"
#include "ofxTrailParticle.h"
#include "ofxParticleSystem.h"
#include "ofxSpringSystem.h"

#include "ofxBoidParticle.h"
#include "ofxBoidSystem.h"

#include "ofxSmartParticle.h"
#include "ofxSmartParticleSystem.h"

#include "ofxRezaParticle.h"
#include "ofxRezaParticleSystem.h"

#include "ofx1DExtruder.h"

#ifndef TARGET_OPENGLES

#include "ofxHOCParticle.h"
#include "ofxHOCParticleSystem.h"

#endif

#include "ofxField2D.h"
#include "ofxFieldAgitator.h"

#include "ofxSolver.h"
#include "ofxVerletSolver.h"
#include "ofxRParticle.h"
#include "ofxRParticleSystem.h"
#include "ofxRParticleRenderer.h"
#include "ofxRParticleGlowieRenderer.h"
#include "ofxBehavior.h"
#include "ofxSphericalAttractionBehavior.h"
#include "ofxHomingBehavior.h"
#include "ofxDamperBehavior.h"
#include "ofxDistorterBehavior.h"
#include "ofxPerlinBehavior.h"
#include "ofxSwarmBehavior.h"
#include "ofxElectroStaticBehavior.h"
#include "ofxBufferEffectorBehavior.h"

#endif
