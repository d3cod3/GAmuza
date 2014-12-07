/*
 *  ofxSubtitles.cpp
 *  Colaborama
 *
 *  Created by Patricio González Vivo on 22/10/10.
 *  Copyright 2010 PatricioGonzalezVivo.com. All rights reserved.
 *
 */
#include "ofxSubtitles.h"

ofxSubtitles::ofxSubtitles(){
	screenWidth = ofGetWidth();
	screenHeight = ofGetHeight();
	color.r = 255;
	color.g = 250;
	color.b = 0;
	color.a = 255;
}

void ofxSubtitles::load(const string& path){
	ifstream	fs( ofToDataPath(path).c_str());
	
	if (fs.is_open()){
		vector <string> file;
		string line;
		
		file.clear();
		
		// Load the data to a temporal vector call ´file´
		while(!(fs >> line).fail())
			file.push_back(line);
		
		fs.close();
		
		int counter = 1;
		// Now it populate the subtitles vector
		for (int i = 0; i < file.size(); i++) {
			// If the line start with a number that match the counter. Means it´s reading the start of a new subtitle line
			if (ofToInt(file[i].c_str()) == counter){
				// Look for IN & OUT TIME in seconds
				vector <string> inTimeRAW = ofSplitString(file[i+1], ":");	
				vector <string> outTimeRAW = ofSplitString(file[i+3], ":");
				
				vector <string> inPresTimeRAW = ofSplitString(file[i+1], ",");
				vector <string> outPresTimeRAW = ofSplitString(file[i+3], ",");
				
				// Extract the seconds
				float inSeg = ofToFloat(inTimeRAW[2].c_str()) + ( ofToFloat(inPresTimeRAW[1].c_str()) )*0.001;
				float outSeg = ofToFloat(outTimeRAW[2].c_str()) + (ofToFloat(outPresTimeRAW[1].c_str()) )*0.001;
				
 				// Add the minutes
				inSeg += 60 * ofToInt(inTimeRAW[1].c_str());
				outSeg += 60 * ofToInt(outTimeRAW[1].c_str());
				// Add the hour
				inSeg += 60 * 60 * ofToInt(inTimeRAW[0].c_str());
				outSeg += 60 * 60 * ofToInt(outTimeRAW[0].c_str());
				
				// Extract the TEXT
				string text = "";
				i += 4;
				while ( (file[i] != ofToString(counter+1)) && (i < file.size()-1 ) ){
					text = text + file[i] + " ";
					i++;
				}
				
				if ( text != "")
					add(inSeg,outSeg,text);
				
				counter++;
				i--;
			}
		}
			
	}
}

void ofxSubtitles::save(const string& path){
	ofstream	fs( ofToDataPath(path).c_str());

	for (int i = 0; i < subtitles.size() ; i++){
		fs << i+1 << endl;
		
		int inIntSeg = (int)(subtitles[i].inSec);
		float inMSeg = ((int)(subtitles[i].inSec * 1000))%1000;
		
		int inS =   inIntSeg % 60;
		int inM = ((inIntSeg - inS )/ 60 )%60;
		int inH = ( inIntSeg - inS - inM * 60)/3600;
		
		int outIntSeg = (int)(subtitles[i].outSec);
		float outMSeg = ((int)(subtitles[i].outSec * 1000))%1000;
		
		int outS =	  outIntSeg % 60;
		int outM = (( outIntSeg - outS)/60)%60;
		int outH = (  outIntSeg - outS - outM*60)/3600;
		
		fs << setfill('0');
		fs << setw(2) << inH << ":" << setw(2) << inM << ":" << setw(2) << inS << "," << setw(3) << inMSeg << " --> " << setw(2) << outH << ":" << setw(2) << outM << ":" << setw(2) << outS << "," << setw(3) << outMSeg << endl;
		
		fs << subtitles[i].text << endl;
		fs << endl;
	}
	fs.close();
}

void ofxSubtitles::add(float _in, string _text){
	float SxL = 0.3;
	float totalSec = _text.length() * SxL;
	
	add(_in, _in+totalSec, _text);
}

void ofxSubtitles::add(float _in, float _out, string _text){
	subTitle tempSub;
	tempSub.inSec	= _in;
	tempSub.outSec	= _out;
	tempSub.text	= _text;
	
	// SI es la primera ...
	if (subtitles.size() <= 0) subtitles.push_back(tempSub);  // ...la AGREGA directamente
	// SI NO es la primera pregunta:
	else { 
		// SI es la última ...
		if ( _in >= subtitles[subtitles.size()-1].outSec ) subtitles.push_back(tempSub); // ...la AGREGA al final
		// Si NO es la última...
		else {
			int inFill = 0;
			int inClean = 0;
			int outFill = 0;
			int outClean = 0;
			// ... pregunta a cada una de las entradas ...
			for(int i = subtitles.size()-1; i > 0; i--){
				// si el principio esta entre la entrada y la salida de un subtítulo existente
				if ( ( subtitles[i].inSec <= _in ) && ( _in <= subtitles[i].outSec) ) inFill = i;
				// o en el espacio entre ella y la anterior.
				else if ( ( subtitles[i-1].outSec <= _in ) && (_in <= subtitles[i].inSec) ) inClean = i;
				// si la salida esta entre la entrada y la salida de un subtítulo existente
				if ( (_out >= subtitles[i].inSec ) && (_out <= subtitles[i].outSec) ) outFill = i;
				// o en el espacio entre ella y la anterior.
				else if ( (_out >= subtitles[i-1].outSec ) && (_out <= subtitles[i].inSec) ) outClean = i;
			}
			
			// SI la entrada esta dentro de un subtítulo existente... 
			if (inFill > 0) {
				if (outFill > 0){
					if (inFill == outFill) subtitles[inFill] = tempSub;
					else if (inFill == outFill - 1){
						subtitles[inFill] = tempSub; // REEMPLAZA el subtitulo y
						subtitles.erase(subtitles.begin()+outFill); 
					} else cout << "ERROR 1: seams to much large entry " << endl;
				} else if ( outClean > 0){
					if (inFill == outClean - 1) subtitles[inFill] = tempSub;
					else if (inFill == outClean - 2){
						subtitles[inFill] = tempSub;
						subtitles.erase(subtitles.begin()+outClean-1); 
					} else cout << "ERROR 2: seams to much large entry " << endl;
				} else cout << "ERROR 3: no end address: outFill=" << outFill << " outClean=" << outClean << endl; 
			// SI la entrada esta en un espacio vacío ...
			} else if ( (inClean > 0 )){
				// ... la salida también ... 
				if ( outClean > 0) { 
					// ... y esa salida esta en el mismo espacio vacío
					if (inClean == outClean )subtitles.insert(subtitles.begin()+inClean,tempSub); // La INSERTA en ese espacio
					// SI esta en el espacio vacío de la anterior entrada
					else if (inClean == outClean - 1 ) subtitles[inClean] = tempSub; // REEMPLAZA la entrada completa
					else cout << "ERROR 4: seams to much large entry " << endl; 
				// Si la salida esta en un espacio ocupado	
				} else if ( outFill > 0 ) {
					// ... y ese espacio ocupado es continuo a la salida ...
					if (inClean == outFill) subtitles[inClean] = tempSub; // la REEMPLAZA
					// SI la salida es en el espacio ocupado por la entrada anterior o sea que sobrepasa dos subtítulos continuos
					else if (inClean == outFill - 1) { 
						subtitles[inClean] = tempSub; // REEMPLAZA el subtitulo y
						subtitles.erase(subtitles.begin()+outFill); // ... borra el subtítulo donde se solapa con el que termina
					} else cout << "ERROR 5: seams to much large entry " << endl; 
				} else cout << "ERROR 6: no end address: outFill=" << outFill << " outClean=" << outClean << endl; 
				
			} else cout << "ERROR 7: no start address: inFill=" << inFill << " inClean=" << inClean << endl; 
		}
	}
}

bool ofxSubtitles::isStringAt(string search, float sec){
	bool its = false;
	
	for(int i = 0 ; i < subtitles.size(); i++)
		if ( (sec >= subtitles[i].inSec) && ( sec <= subtitles[i].outSec ) && (subtitles[i].text == search ) ){
			its = true;
			break;
		}
	
	return its;
}

int	ofxSubtitles::getHowMany(float _fromSec, float _untilSec){
	int counter = 0;
	
	for(int i = 0; i < subtitles.size(); i++){
		if ( (subtitles[i].inSec >= _fromSec) && (subtitles[i].outSec <= _untilSec) )
			counter++;
	}
	
	return counter;
}

int	ofxSubtitles::getFirstSubN(float _fromSec ){
	for(int i = 0; i < subtitles.size(); i++){
		if ( subtitles[i].inSec >= _fromSec){
			return i;
			break;
		}
	}
}

subTitle ofxSubtitles::getSubTitleAt(float _sec){
	subTitle sub;
	sub.text = "";
	
	for(int i = 0; i < subtitles.size(); i++){
		if ( (_sec > subtitles[i].inSec) && (_sec < subtitles[i].outSec) ){
			sub = subtitles[i];
			break;
		}
	}
	
	return sub;
}


void ofxSubtitles::replace(string search, string replace, float sec){
	for(int i = 0 ; i < subtitles.size(); i++)
		if ( ((sec+50) >= subtitles[i].inSec) && ( sec <= subtitles[i].outSec ) && (subtitles[i].text == search ) ){
			subtitles[i].text = replace;
			break;
		}
}

// ----------------------------------------------------------
void ofxSubtitles::draw(int x, int y, int w, int h, float sec){
	string text = getLineAt(sec);
	
	ofSetColor(color.r,color.g,color.b,color.a);
	
	if (font.stringWidth(text) < w*0.8 ){
		font.drawString(text,x + w*0.5 - font.stringWidth(text)*0.5, y + h - font.stringHeight(text));
	} else {
		vector <string> words = ofSplitString(text, " ");
		vector <string> lines;
		string tempText = "";
		
		for (int i = 0; i < words.size(); i++){
			if (font.stringWidth(tempText + " " + words[i]) < w*0.8 ) tempText = tempText + " " + words[i];
			else {
				lines.push_back(tempText);
				tempText = words[i];
			}
		}
		lines.push_back(tempText);
		
		for (int i = 0; i < lines.size(); i++)
			font.drawString(lines[i], x + w*0.5 - font.stringWidth(lines[i])*0.5, y + h - (font.stringHeight(lines[i])*lines.size()) + font.stringHeight(lines[i])*i );
	}
}

