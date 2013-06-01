/***********************************************************************

 Copyright (c) 2008, 2009, Memo Akten, www.memo.tv
 * Adapted for Windows by Juan Pablo Manson
 * Cross platform architecture and convenience fucntions by James George
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of MSA Visuals nor the names of its contributors
 *       may be used to endorse or promote products derived from this software
 *       without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * ***********************************************************************/

#pragma once

#include "ofMain.h"

#if defined(TARGET_WIN32)
    #if not defined(NOMINMAX)
        #define NOMINMAX
    #endif
    #include <windows.h>
#elif defined(TARGET_OSX)
	#include <sys/time.h>
	#include <mach/mach_time.h>
#elif defined(TARGET_LINUX)
	#include "time.h"
	#include <inttypes.h>
#endif

#include "stdio.h"
#include "stdint.h"

class ofxMSATimer {
  public:
    ofxMSATimer();

	float getAppTimeSeconds();
	uint32_t getAppTimeMillis();
	uint64_t getAppTimeMicros();

	void setStartTime();
	float getElapsedSeconds();
	uint32_t getElapsedMillis();
	uint64_t getElapsedMicros();

	float getSecondsSinceLastCall();
	uint32_t getMillisSinceLastCall();
	uint64_t getMicrosSinceLastCall();

protected:

	uint64_t timerStartTimeMicros;
    uint64_t lastCallTimeMicros;

	#if defined(TARGET_WIN32)
    LARGE_INTEGER ticksPerSecond;
    LARGE_INTEGER startTime, stopTime;
	#elif defined(TARGET_OSX)
    mach_timebase_info_data_t info;
    uint64_t machStartTime; //nanos
	#elif defined(TARGET_LINUX)
    struct timespec startTime;
    struct timespec tmpTime;
	#endif

};

