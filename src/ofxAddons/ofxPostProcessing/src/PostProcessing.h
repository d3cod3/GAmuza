/*
 *  PostProcessing.h
 *
 *  Copyright (c) 2012, Neil Mendoza, http://www.neilmendoza.com
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *  * Neither the name of Neil Mendoza nor the names of its contributors may be used
 *    to endorse or promote products derived from this software without
 *    specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 *  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *
 */
#pragma once

#include "RenderPass.h"
#include "ofCamera.h"
#include "ofEasyCam.h"

#include "BloomPass.h"
#include "ConvolutionPass.h"
#include "DofPass.h"
#include "DofAltPass.h"
#include "EdgePass.h"
#include "FxaaPass.h"
#include "KaleidoscopePass.h"
#include "NoiseWarpPass.h"
#include "PixelatePass.h"
#include "LUTPass.h"
#include "ContrastPass.h"
#include "SSAOPass.h"
#include "HorizontalTiltShifPass.h"
#include "VerticalTiltShifPass.h"
#include "RGBShiftPass.h"
#include "FakeSSSPass.h"
#include "ZoomBlurPass.h"
#include "BleachBypassPass.h"
#include "ToonPass.h"
#include "GodRaysPass.h"
#include "RimHighlightingPass.h"
#include "LimbDarkeningPass.h"

namespace itg
{
    class PostProcessing : public ofBaseDraws
    {
    public:
        typedef shared_ptr<PostProcessing> Ptr;
        
        void init(unsigned width = ofGetWidth(), unsigned height = ofGetHeight());
        void begin();
        void begin(ofCamera& cam);
        // GAmuza util
        void begin(ofEasyCam& cam);
        void end(bool autoDraw = true);
        // GAmuza util
        void end() { end(true);}
        
        // float rather than int and not const to override ofBaseDraws
        void draw(float x = 0.f, float y = 0.f);
        void draw(float x, float y, float w, float h);
        float getWidth() { return width; }
        float getHeight() { return height; }
        
        void debugDraw();
        
        template<class T>
        shared_ptr<T> createPass()
        {
            shared_ptr<T> pass = shared_ptr<T>(new T(ofVec2f(width, height)));
            passes.push_back(pass);
            return pass;
        }
        
        // GAmuza utils
        void createBleachBypass() { createPass<BleachBypassPass>()->setEnabled(true); }
        void createBloom() { createPass<BloomPass>()->setEnabled(true); }
        void createContrast() { createPass<ContrastPass>()->setEnabled(true); }
        void createConvolution() { createPass<ConvolutionPass>()->setEnabled(true); }
        void createDof() { createPass<DofPass>()->setEnabled(true); }
        void createEdge() { createPass<EdgePass>()->setEnabled(true); }
        void createFxaa() { createPass<FxaaPass>()->setEnabled(true); }
        void createGodRays() { createPass<GodRaysPass>()->setEnabled(true); }
        void createHorizontalTiltShift() { createPass<HorizontalTiltShifPass>()->setEnabled(true); }
        void createKaleidoscope() { createPass<KaleidoscopePass>()->setEnabled(true); }
        void createLimbDarkening() { createPass<LimbDarkeningPass>()->setEnabled(true); }
        void createLUT() { createPass<LUTPass>()->setEnabled(true); }
        void createNoiseWarp() { createPass<NoiseWarpPass>()->setEnabled(true); }
        void createPixelate() { createPass<PixelatePass>()->setEnabled(true); }
        void createRGBShift() { createPass<RGBShiftPass>()->setEnabled(true); }
        void createRimHighlighting() { createPass<RimHighlightingPass>()->setEnabled(true); }
        void createSSAO() { createPass<SSAOPass>()->setEnabled(true); }
        void createToon() { createPass<ToonPass>()->setEnabled(true); }
        void createVerticalTiltShif() { createPass<VerticalTiltShifPass>()->setEnabled(true); }
        void createZoomBlur() { createPass<ZoomBlurPass>()->setEnabled(true); }
        
        
        ofTexture& getProcessedTextureReference();
        
        // advanced
        void process(ofFbo& raw);
        
        /**
         * Set flip.
         * Turn on if using ofEasyCam to fix flipping bug.
         */
        void setFlip(bool flip) { this->flip = flip; }
        
        unsigned size() const { return passes.size(); }
        RenderPass::Ptr operator[](unsigned i) const { return passes[i]; }
        vector<RenderPass::Ptr>& getPasses() { return passes; }
        unsigned getNumProcessedPasses() const { return numProcessedPasses; }
        
        ofFbo& getRawRef() { return raw; }
        
    private:
        void process();
        
        unsigned currentReadFbo;
        unsigned numProcessedPasses;
        unsigned width, height;
        bool flip;
        
        ofFbo raw;
        ofFbo pingPong[2];
        vector<RenderPass::Ptr> passes;
    };
}
