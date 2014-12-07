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

#include "ofxMSATimer.h"


#if defined(TARGET_OSX)

ofxMSATimer::ofxMSATimer(){
    mach_timebase_info(&info);    
    machStartTime = mach_absolute_time();
    getMicrosSinceLastCall();
}

uint64_t ofxMSATimer::getAppTimeMicros(){
	return (mach_absolute_time() - machStartTime) * info.numer / (info.denom * 1000);	
}

#elif defined(TARGET_WIN32)

ofxMSATimer::ofxMSATimer(){
    QueryPerformanceFrequency(&ticksPerSecond);
    QueryPerformanceCounter(&startTime);
    getMicrosSinceLastCall();
}

uint64_t ofxMSATimer::getAppTimeMicros(){
    QueryPerformanceCounter(&stopTime);
	return ((stopTime.QuadPart - startTime.QuadPart) * 1000000) / ticksPerSecond.QuadPart;
}

#elif defined(TARGET_LINUX)

ofxMSATimer::ofxMSATimer(){
	clock_gettime(CLOCK_MONOTONIC_RAW, &startTime);
	getMicrosSinceLastCall();
}

timespec diff(timespec& start, timespec& end)
{
	timespec temp;
	if ((end.tv_nsec-start.tv_nsec)<0) {
		temp.tv_sec = end.tv_sec-start.tv_sec-1;
		temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
	} else {
		temp.tv_sec = end.tv_sec-start.tv_sec;
		temp.tv_nsec = end.tv_nsec-start.tv_nsec;
	}
	return temp;
}

uint64_t ofxMSATimer::getAppTimeMicros(){
	clock_gettime(CLOCK_MONOTONIC_RAW, &tmpTime);
	timespec diffTime = diff(startTime, tmpTime);
	return  ((int64_t)diffTime.tv_sec*1000000000 + (int64_t)diffTime.tv_nsec)/1000;
}

#endif

float ofxMSATimer::getAppTimeSeconds(){
    return getAppTimeMicros() / 1000000.0;
}

uint32_t ofxMSATimer::getAppTimeMillis(){
    return getAppTimeMicros() / 1000;
}

float ofxMSATimer::getElapsedSeconds(){
	return getElapsedMicros() / 1000000.0;
}

uint32_t ofxMSATimer::getElapsedMillis(){
    return getElapsedMicros() / 1000;
}

float ofxMSATimer::getSecondsSinceLastCall(){
    return getMicrosSinceLastCall() / 1000000.0;
}

uint32_t ofxMSATimer::getMillisSinceLastCall(){
    return getMicrosSinceLastCall() / 1000;
}

uint64_t ofxMSATimer::getMicrosSinceLastCall(){
    uint64_t ret = getAppTimeMicros() - lastCallTimeMicros;
    lastCallTimeMicros = getAppTimeMicros();
    return ret;
}

uint64_t ofxMSATimer::getElapsedMicros(){
    return getAppTimeMicros() - timerStartTimeMicros;
}

void ofxMSATimer::setStartTime(){
    timerStartTimeMicros = getAppTimeMicros();
}
