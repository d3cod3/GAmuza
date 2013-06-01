#include "audioInputChannel.h"

int	barkEdges[BARK_SCALE_CRITICAL_BANDS] = {100,200,300,400,510,630,770,920,1080,1270,1480,1720,2000,2320,
											2700,3150,3700,4400,5300,6400,7700,9500,12000,22000};

//---------------------------------------------------------------
audioInputChannel::audioInputChannel(){
	
	
}

//---------------------------------------------------------------
void audioInputChannel::setupChannel(int _id,int _sampleRate,int _bufferSize,int _nChannels,int fftWindow){
	
	sampleRate			= _sampleRate;
	bufferSize			= _bufferSize;
	numChannels			= _nChannels;
	
	chRaw					= new float[bufferSize];
	chClean					= new float[bufferSize];
	autoCorrelation			= new float[bufferSize];
	autoCorrelationNorm		= new float[bufferSize];
	
	chID				= _id;
	captureAudioCH		= true;
	applyCorrelation	= true;
	applyNormalize		= true;
	
	captureAudio		= true;
	drawGraphics		= true;
	computeChannel		= false;
	_volume				= 1.0f;
	_internalMute		= 1.0f;
	_mute				= false;
	
	font.loadFont("fonts/D3Litebitmapism.ttf",8);
	
	// FFT setup
	switch (fftWindow) {
		case 0:
			fft = ofxFft::create(bufferSize, OF_FFT_WINDOW_RECTANGULAR);
			break;
		case 1:
			fft = ofxFft::create(bufferSize, OF_FFT_WINDOW_BARTLETT);
			break;
		case 2:
			fft = ofxFft::create(bufferSize, OF_FFT_WINDOW_HANN);
			break;
		case 3:
			fft = ofxFft::create(bufferSize, OF_FFT_WINDOW_HAMMING);
			break;
		case 4:
			fft = ofxFft::create(bufferSize, OF_FFT_WINDOW_SINE);
			break;
		default:
			break;
	}
	
	int	binSize			= fft->getBinSize();
	
	fft_binSizeHz		= ((sampleRate/2)/(binSize-1));
	
	fft_StrongestBinValue = 0.0f;
	
	fftBins				= new float[binSize];
	noiseFilterStep		= new float[binSize];
	noiseFilter			= new float[binSize];
	eqGaussianLOW		= new float[binSize];
	eqGaussianMID		= new float[binSize];
	eqGaussianHI		= new float[binSize];
	gaussianFilter		= new float[binSize];
	binsFiltered		= new float[binSize];
	binsToBark			= new int[binSize];
	barkBins			= new float[BARK_SCALE_CRITICAL_BANDS];
	barkGrouped			= new int[BARK_SCALE_CRITICAL_BANDS];
	
	setupBarkScale();
	
	chVolume				= 0.0f;
	chPitch					= 0.0f;
	fft_StrongestBinValue	= 0.0f;
	fft_StrongestBinIndex	= 0;
	fft_pitchBin			= 0;
	
	noiseRec			= false;
	bufferRecCounter	= 1;
	reduxFactor			= 1.0f;
	
	signalBackground.loadImage("img/timeDomain.png");
	eqBackground.loadImage("img/frequencyDomain.png");
	timeFreq.loadImage("img/timeFreq.png");
	
	// osc data vars setup
	_kalman_barkBins		= new float[BARK_SCALE_CRITICAL_BANDS];
	_s_barkBins				= new float[BARK_SCALE_CRITICAL_BANDS];
	_osc_barkBins			= new float[BARK_SCALE_CRITICAL_BANDS];
	
	sendOsc_VD			= false;
	sendOsc_PD			= false;
	sendOsc_BK			= false;
	
}

//---------------------------------------------------------------
void audioInputChannel::drawChannel(int x, int y, int w, int h){
	
	char temp[128];
	
	glPushMatrix();
		glTranslatef(x, y, 0.0f);
		ofEnableAlphaBlending();
		
		// background
		ofFill();
		glColor4f(0.941,0.941,0.941,0.05);
		ofRect(0,y,w,h*4);
	
		glColor4f(0.941,0.941,0.941,0.2);
		signalBackground.draw(0,y);
		signalBackground.draw(0,y+h);
		signalBackground.draw(0,y+h*2);
		signalBackground.draw(0,y+h*3);
		
		
		if(bufferSize > 0){
			float stretch		= w / (float)(bufferSize - 1);
			float zeroOffset	= h / 2.0;
			
			// scope RAW
			ofNoFill();
			
			glPushMatrix();	
				glTranslatef(0, y+zeroOffset, 0.0f);
				glColor4f(0.941,0.941,0.941,0.9);
				sprintf(temp,"TIME DOMAIN");
				font.drawString(temp, 0, -10-zeroOffset);
				glColor4f(1.0,0.906,0.463,0.9);
				sprintf(temp,"RAW SIGNAL");
				font.drawString(temp, 2, 8-zeroOffset);
				ofBeginShape();
				for (int i = 0; i < bufferSize - 1; i++){
					ofVertex(i * stretch, hardClip(chRaw[i]) * zeroOffset);
					ofVertex((i + 1) * stretch, hardClip(chRaw[i + 1]) * zeroOffset);
				}
				ofEndShape(false);
			glPopMatrix();
			
			// scope AUTOCORRELATION
			glColor4f(0.941,0.941,0.941,0.7);
			ofNoFill();
			
			glPushMatrix();	
				glTranslatef(0, y+(zeroOffset*3.0), 0.0f);
				sprintf(temp,"CORRELATED SIGNAL");
				font.drawString(temp, 2, 8-zeroOffset);
				ofBeginShape();
				for (unsigned int i = 0; i < bufferSize - 1; i++){
					ofVertex(i * stretch, hardClip(autoCorrelation[i]) * zeroOffset);
					ofVertex((i + 1) * stretch, hardClip(autoCorrelation[i + 1]) * zeroOffset);
				}
				ofEndShape(false);
			glPopMatrix();
			
			// scope AUTOCORRELATION NORMALIZED
			glColor4f(0.941,0.941,0.941,0.7);
			ofNoFill();
			
			glPushMatrix();	
				glTranslatef(0, y+(zeroOffset*5.0), 0.0f);
				sprintf(temp,"CORRELATED SIGNAL NORMALIZED");
				font.drawString(temp, 2, 8-zeroOffset);
				ofBeginShape();
				for (unsigned int i = 0; i < bufferSize - 1; i++){
					ofVertex(i * stretch, hardClip(autoCorrelationNorm[i]) * zeroOffset);
					ofVertex((i + 1) * stretch, hardClip(autoCorrelationNorm[i + 1]) * zeroOffset);
				}
				ofEndShape(false);
			glPopMatrix();
			
			// scope AUTOCORRELATION NOISE FILTERED
			glColor4f(1.0,0.906,0.463,0.7);
			ofNoFill();
			
			glPushMatrix();	
			glTranslatef(0, y+(zeroOffset*7.0), 0.0f);
			sprintf(temp,"FILTERED CORRELATED SIGNAL");
			font.drawString(temp, 2, 8-zeroOffset);
			ofBeginShape();
			for (unsigned int i = 0; i < bufferSize - 1; i++){
				ofVertex(i * stretch, hardClip(chClean[i]) * zeroOffset);
				ofVertex((i + 1) * stretch, hardClip(chClean[i + 1]) * zeroOffset);
			}
			ofEndShape(false);
			glPopMatrix();
			
			
			// FFT SPECTRUM
			glPushMatrix();
				glTranslatef(w+18, y, 0.0f);
			
				glColor4f(0.941,0.941,0.941,0.2);
				eqBackground.draw(0,0);
				eqBackground.draw(0,h);
				eqBackground.draw(0,h*2);
				eqBackground.draw(0,h*3);
			
				glColor4f(0.941,0.941,0.941,0.9);
				sprintf(temp,"FREQUENCY DOMAIN");
				font.drawString(temp, 0, - 10);
				//glColor4f(0.847,0.25,0.25,0.9);
                ofSetColor(9,147,211,240);
				sprintf(temp,"NOISE FILTER");
				font.drawString(temp, 2, 8);
				sprintf(temp,"PARAMETRIC EQ [NORMALIZED RADIAL BASIS FUNCTION NETWORK]");
				font.drawString(temp, 2, 8+h);
				glColor4f(1.0,0.906,0.463,0.9);
				sprintf(temp,"FILTERED FFT BINS [%i]",fft->getBinSize());
				font.drawString(temp, 2, 8+(h*2));
				sprintf(temp,"BARK SCALE BINS [%i]",BARK_SCALE_CRITICAL_BANDS);
				font.drawString(temp, 2, 8+(h*3));
			
				glScalef(((float)w/fft->getBinSize()), 1.0f, 1.0f);
				
				// noise filter
                ofSetColor(9,147,211,255);
				//glColor4f(0.847,0.25,0.25,1.0); // 216, 64, 64
				
				ofSetLineWidth(2);
				ofBeginShape();
				for(unsigned int i = 1; i < fft->getBinSize()-1; i++){
					ofVertex(i, (hardClip(noiseFilter[i]*reduxFactor) * zeroOffset) + zeroOffset);
					ofVertex(i+1, (hardClip(noiseFilter[i+1]*reduxFactor) * zeroOffset) + zeroOffset);
				}
				ofEndShape(false);
				
				// gaussian filter
				//glColor4f(0.847,0.25,0.25,1.0);
                ofSetColor(9,147,211,255);
                ofSetLineWidth(2);
				ofBeginShape();
				for(unsigned int i = 0; i < fft->getBinSize()-1; i++){
					ofVertex(i, (hardClip(gaussianFilter[i]) * -zeroOffset) + zeroOffset + h);
					ofVertex(i+1, (hardClip(gaussianFilter[i+1]) * -zeroOffset) + zeroOffset + h);
				}
				ofEndShape(false);
			
				// filtered fft BINS
				ofSetLineWidth(1);
				for(unsigned int i = 2; i < fft->getBinSize(); i++){
					if(i == fft_pitchBin){
						//glColor4f(0.847,0.25,0.25,0.9);
                        ofSetColor(9,147,211,255);
						ofLine(i,h*3 - 1,i,h*3 - h + 1);
					}else{
						glColor4f(1.0,0.906,0.463,0.9);
					}
					ofLine(i,h*3 - 1,i,(hardClip(binsFiltered[i]) * -h) + h*3 - 1);
				}
			
				// BARK SCALE BINS
				glColor4f(1.0,0.906,0.463,0.9);
				float temp = (fft->getBinSize()*1.0f)/BARK_SCALE_CRITICAL_BANDS;
				for(unsigned int i=0;i<BARK_SCALE_CRITICAL_BANDS;i++){
					ofRect(i*temp, h*4 - 1, temp, hardClip(_osc_barkBins[i] / barkGrouped[i]) * -h);
				}
			
				// background
				ofFill();
				glColor4f(0.941,0.941,0.941,0.05);
				ofRect(0,0,fft->getBinSize(),h*4);
				
				// frame
				ofNoFill();
				glColor4f(0.941,0.941,0.941,0.4);
				ofRect(0,0,fft->getBinSize(),h);
				ofRect(0,h,fft->getBinSize(),h);
				ofRect(0,h*2,fft->getBinSize(),h);
				ofRect(0,h*3,fft->getBinSize(),h);
				
			glPopMatrix();
			
		}
	
		// frames
		glColor4f(0.941,0.941,0.941,0.4);
		ofRect(0,y,w,h);
		ofRect(0,y+h,w,h);
		ofRect(0,y+(h*2),w,h);
		ofRect(0,y+(h*3),w,h);
		
		// graphics gui
		glColor4f(0.941,0.941,0.941,0.8);
		timeFreq.draw(0,y+(h*4));
	
		ofDisableAlphaBlending();
	glPopMatrix();
	
}

//---------------------------------------------------------------
void audioInputChannel::captureChannel(float *input){
	
	/////////////////////
	// mute/unmute channel
	if(_mute){
		_internalMute = 0.0f;
	}else{
		_internalMute = 1.0f;
	}
	/////////////////////
	
	/////////////////////
	// capture channel
	for (unsigned int i = 0; i < bufferSize; i++){
		chRaw[i] = input[i*numChannels + chID] * (_volume*_internalMute);
	}
	/////////////////////
	
	// autocorrelation + normalization
	doAutoCorrelation();
	
	// get volume
	detectVolume();
	
	// get pitch
	detectPitch();
	
	// parametric eq [normalized radial basis function network]
	updateFilter();
	
	/////////////////////
	// FFT analysis
	fft_mutex.lock();
	if(noiseRec){
		fft->setSignal(autoCorrelationNorm);
		memcpy(fftBins, fft->getAmplitude(), sizeof(float) * fft->getBinSize());
		for(unsigned int i = 0; i < fft->getBinSize(); i++){
			noiseFilterStep[i] += fftBins[i];
			noiseFilter[i] = noiseFilterStep[i]/bufferRecCounter;
		}
		bufferRecCounter++;
		
	}else{
		fft->setSignal(autoCorrelation);
		memcpy(fftBins, fft->getAmplitude(), sizeof(float) * fft->getBinSize());
		
		fft_StrongestBinValue	= 0.0f;
		
		for(unsigned int j=0;j<BARK_SCALE_CRITICAL_BANDS;j++){
			barkBins[j] = 0.0f;
		}
		
		for(unsigned int i = 0; i < fft->getBinSize(); i++){
			// apply noise and parametric eq to fft bins
			binsFiltered[i] = fftBins[i] * (1.0 - (noiseFilter[i]*reduxFactor));
			binsFiltered[i] *= (gaussianFilter[i] + 1.0f);
			// storing strongest bin for pitch detection
			if(binsFiltered[i] > fft_StrongestBinValue){
				fft_StrongestBinValue = binsFiltered[i];
				fft_StrongestBinIndex = i;
			}
			// calculate bark scale bins from fft bins
			updateBarkScale(i);
			
		}
	}
	fft->setPolar(binsFiltered, fft->getPhase());
	fft->clampSignal();
	memcpy(chClean, fft->getSignal(), sizeof(float) * fft->getSignalSize());
	fft_mutex.unlock();
	/////////////////////
	
	//////////////////////////////////////////////
	// apply kalman filter (if selected) to every output value
	// smoothing & normalize numerical variable
	// (prepare it for sending via OSC)
	smoothingValues();
	normalizeValues();
	//////////////////////////////////////////////
		
}

//---------------------------------------------------------------
void audioInputChannel::doAutoCorrelation(){
	
	float sum;
	float autoCorrelationResults[bufferSize];
	
    for (unsigned int i = 0; i < bufferSize; i++) {
        sum = 0;
        for (int j = 0; j < bufferSize-i; j++) {
            sum += chRaw[j]*chRaw[j+i];
        }
        autoCorrelationResults[i]=sum;
		
    }
	
	memcpy(autoCorrelation, autoCorrelationResults, bufferSize * sizeof(float));
	
	float maxValue = 0;
	
	for (unsigned int i=0;i<bufferSize;i++) {
		if (fabs(autoCorrelationResults[i]) > maxValue){
			maxValue = fabs(autoCorrelationResults[i]);
		}
	}
	
	if (maxValue > 0){
		for(unsigned int i=0;i<bufferSize;i++) {
			autoCorrelationResults[i] /= maxValue;
		}
	}
	memcpy(autoCorrelationNorm, autoCorrelationResults, bufferSize * sizeof(float));
	
}

//---------------------------------------------------------------
void audioInputChannel::detectVolume(){
	for (unsigned int i = 0; i < bufferSize; i++) {
		chVolume += abs(autoCorrelation[i]);
	}
	chVolume /= bufferSize;
}

//---------------------------------------------------------------
void audioInputChannel::detectPitch(){
	
	chPitch = (fft_StrongestBinIndex*fft_binSizeHz) + (fft_binSizeHz/2.0f);
	
	fft_pitchBin = _s_chPitch * fft->getBinSize() /(sampleRate / 2);
	
}

//---------------------------------------------------------------
void audioInputChannel::updateFilter(){
	
	for(unsigned int i = 0; i < fft->getBinSize(); i++){
		eqGaussianLOW[i]	= gaGaussianFn(i, eqLOWAmplitude, eqLOWCenter, eqLOWWidth);
		eqGaussianMID[i]	= gaGaussianFn(i, eqMIDAmplitude, eqMIDCenter, eqMIDWidth);
		eqGaussianHI[i]		= gaGaussianFn(i, eqHIAmplitude, eqHICenter, eqHIWidth);
		
		gaussianFilter[i]	= (eqGaussianLOW[i]+eqGaussianMID[i]+eqGaussianHI[i])/3.0f;
	}
	
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// 24 critical bands of hearing (psychoacoustical Bark scale)
//
//---------------------------------------------------------------
void audioInputChannel::setupBarkScale(){
	// setup bark scale reduction (it depends on samplerate and buffersize)
	// first bin is the 0 Hz component (a constant DC offset to the signal), we do not consider it
	int tempFreq = 0;
	for(unsigned int j=0;j<BARK_SCALE_CRITICAL_BANDS;j++){
		barkGrouped[j] = 0;
		barkBins[j]	   = 0.0f;
		for(unsigned int i = 0; i < fft->getBinSize(); i++){
			tempFreq = (int)((i*fft_binSizeHz) + (fft_binSizeHz/2.0f));
			if(j == 0){
				if(tempFreq <= barkEdges[j]){
					barkGrouped[j]++;
					binsToBark[i] = j;
				}else{
					i = fft->getBinSize();
				}
			}else if(j > 0){
				if(tempFreq > barkEdges[j-1] && tempFreq <= barkEdges[j]){
					barkGrouped[j]++;
					binsToBark[i] = j;
				}
			}
		}
	}
	binsToBark[fft->getBinSize()-1] = 23;
}

//---------------------------------------------------------------
void audioInputChannel::updateBarkScale(int i){
	
	for(unsigned int j=0;j<BARK_SCALE_CRITICAL_BANDS;j++){
		if(binsToBark[i] == j){
			barkBins[j] += binsFiltered[i];
		}
	}
	
}


///////////////////////////////////////////////////////////////////////////
// <http://en.wikipedia.org/wiki/Bark_scale>
///////////////////////////////////////////////////////////////////////////

//---------------------------------------------------------------
void audioInputChannel::recNoiseFilter(){
	
	noiseRec = !noiseRec;
	
	bufferRecCounter = 1;
	
	if(noiseRec == false){
		saveNoiseFilter();
		printf("Saved noise correction filter for Channel %i\n",chID);
	}
	
}

//---------------------------------------------------------------
void audioInputChannel::loadNoiseFilter(){
	
	char temp[256];
	
	sprintf(temp,"settings/audioInput/noiseReduxCh%i.xml",chID);
	noiseReduxXml.loadFile(temp);
	
	for(unsigned int i = 0; i < fft->getBinSize(); i++){
		sprintf(temp,"bin%i",i);
		noiseFilter[i] = noiseReduxXml.getValue(temp,0.0,0.0);
	}
	
	
}

//---------------------------------------------------------------
void audioInputChannel::saveNoiseFilter(){
	
	char temp[256];
	
	for(unsigned int i = 0; i < fft->getBinSize(); i++){
		sprintf(temp,"bin%i",i);
		noiseReduxXml.setValue(temp,noiseFilter[i]);
	}
	
	sprintf(temp,"settings/audioInput/noiseReduxCh%i.xml",chID);
	noiseReduxXml.saveFile(temp);
	
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// In a race, the quickest runner can never overtake the slowest,
// since the pursuer must first reach the point whence the pursued started,
// so that the slower must always hold a lead.
//
//---------------------------------------------------------------
void audioInputChannel::smoothingValues(){
	// volume detection
	_s_chVolume = _s_chVolume*_smoothingFactor + (1.0-_smoothingFactor)*chVolume;
	// pitch detection
	_s_chPitch = _s_chPitch*_smoothingFactor + (1.0-_smoothingFactor)*chPitch;
	// bark scale bins
	for(unsigned int i=0;i<BARK_SCALE_CRITICAL_BANDS;i++){
		_s_barkBins[i] = _s_barkBins[i]*_smoothingFactor + (1.0-_smoothingFactor)*barkBins[i];
	}
}
//
//—Aristotle, Physics VI:9, 239b15
// http://en.wikipedia.org/wiki/Zeno%27s_paradoxes#Achilles_and_the_tortoise
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

//---------------------------------------------------------------
void audioInputChannel::normalizeValues(){
	// volume detection
	_osc_chVolume = ofNormalize(_s_chVolume,0.0f,10.0f);
	// pitch detection
	_osc_chPitch = ofNormalize(_s_chPitch,20.0f,20000.0f);
	// bark scale bins
	for(unsigned int i=0;i<BARK_SCALE_CRITICAL_BANDS;i++){
		_osc_barkBins[i] = hardClip(_s_barkBins[i]);
	}
}
