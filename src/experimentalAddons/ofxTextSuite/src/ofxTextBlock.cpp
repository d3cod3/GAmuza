/***********************************************************************

 Copyright (c) 2009, Luke Malcolm, www.lukemalcolm.com

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.

 ***********************************************************************/

#include "ofxTextBlock.h"

ofxTextBlock::ofxTextBlock()
{

    scale       =   1.0f;

}

ofxTextBlock::~ofxTextBlock()
{
    //dtor
}

void ofxTextBlock::init(string fontLocation, float fontSize){

    defaultFont.loadFont(fontLocation, fontSize, true, true);

    //Set up the blank space word
    blankSpaceWord.rawWord = " ";
    blankSpaceWord.width   = defaultFont.stringWidth ("x");
    blankSpaceWord.height  = defaultFont.stringHeight("i");
    blankSpaceWord.color.r = blankSpaceWord.color.g = blankSpaceWord.color.b = 255;

}

void ofxTextBlock::setText(string _inputText){
    rawText     = _inputText;
    _loadWords();
    wrapTextForceLines(1);
}

void ofxTextBlock::draw(float x, float y){

    drawLeft(x, y);

}

void ofxTextBlock::drawLeft(float x, float y){

    string  strToDraw;
    int     currentWordID;
    float   drawX;
    float   drawY;

    float currX = 0;

    if (words.size() > 0) {

        for(int l=0;l < lines.size(); l++)
        {
            for(int w=0;w < lines[l].wordsID.size(); w++)
            {
                currentWordID = lines[l].wordsID[w];

                drawX = x + currX;
                drawY = y + (defaultFont.getLineHeight() * (l + 1));

                ofSetColor(words[currentWordID].color.r, words[currentWordID].color.g, words[currentWordID].color.b);
                glPushMatrix();
                //glTranslatef(drawX, drawY, 0.0f);
                glScalef(scale, scale, scale);

                defaultFont.drawString(words[currentWordID].rawWord.c_str(), drawX, drawY);
                currX += words[currentWordID].width;

                glPopMatrix();

            }
            currX = 0;

        }
    }
}

void ofxTextBlock::drawCenter(float x, float y){

    string  strToDraw;
    int     currentWordID;
    float   drawX;
    float   drawY;
    float   lineWidth;

    float currX = 0;

    if (words.size() > 0) {

        for(int l=0;l < lines.size(); l++)
        {

            //Get the length of the line.
            lineWidth = 0;
            for(int w=0;w < lines[l].wordsID.size(); w++)
            {
                currentWordID = lines[l].wordsID[w];
                lineWidth += words[currentWordID].width;
            }

            for(int w=0;w < lines[l].wordsID.size(); w++)
            {
                currentWordID = lines[l].wordsID[w];

                drawX = -(lineWidth / 2) + currX;
                drawY = defaultFont.getLineHeight() * (l + 1);

                ofSetColor(words[currentWordID].color.r, words[currentWordID].color.g, words[currentWordID].color.b);

                glPushMatrix();

                //Move to central point using pre-scaled co-ordinates
                glTranslatef(x, y, 0.0f);

                glScalef(scale, scale, scale);

                defaultFont.drawString(words[currentWordID].rawWord.c_str(), drawX, drawY);
                currX += words[currentWordID].width;

                glPopMatrix();

            }
            currX = 0;

        }
    }
}

void ofxTextBlock::drawJustified(float x, float y, float boxWidth){

    string  strToDraw;
    int     currentWordID;
    float   drawX;
    float   drawY;
    int     spacesN;
    float   nonSpaceWordWidth;
    float   pixelsPerSpace;

    float currX = 0;

    if (words.size() > 0) {


        for(int l=0;l < lines.size(); l++)
        {
            //Find number of spaces and width of other words;
            spacesN = 0;
            nonSpaceWordWidth = 0;

            for(int w=0;w < lines[l].wordsID.size(); w++)
            {
                currentWordID = lines[l].wordsID[w];
                if (words[currentWordID].rawWord == " ") spacesN++;
                else nonSpaceWordWidth += words[currentWordID].width;
            }

            pixelsPerSpace = ((boxWidth / scale) - (x / scale) - nonSpaceWordWidth) / spacesN;

            for(int w=0;w < lines[l].wordsID.size(); w++)
            {
                currentWordID = lines[l].wordsID[w];

                drawX = currX;
                drawY = defaultFont.getLineHeight() * (l + 1);

                ofSetColor(words[currentWordID].color.r, words[currentWordID].color.g, words[currentWordID].color.b);
                glPushMatrix();
                //Move to top left point using pre-scaled co-ordinates
                glTranslatef(x, y, 0.0f);
                glScalef(scale, scale, scale);

                if (words[currentWordID].rawWord != " ") {
                    defaultFont.drawString(words[currentWordID].rawWord.c_str(), drawX, drawY);
                    currX += words[currentWordID].width;
                }
                else {
                    currX += pixelsPerSpace;
                }


                glPopMatrix();

            }
            currX = 0;

        }
    }
}

void ofxTextBlock::drawRight(float x, float y){

    string  strToDraw;
    int     currentWordID;
    float   drawX;
    float   drawY;

    float currX = 0;

    if (words.size() > 0) {

        for(int l=0;l < lines.size(); l++)
        {

            for(int w=lines[l].wordsID.size() - 1; w >= 0; w--)
            {

                currentWordID = lines[l].wordsID[w];

                drawX = -currX - words[currentWordID].width;
                drawY = defaultFont.getLineHeight() * (l + 1);

                ofSetColor(words[currentWordID].color.r, words[currentWordID].color.g, words[currentWordID].color.b);

                glPushMatrix();

                //Move to top left point using pre-scaled co-ordinates
                glTranslatef(x, y, 0.0f);
                glScalef(scale, scale, scale);

                defaultFont.drawString(words[currentWordID].rawWord.c_str(), drawX, drawY);
                currX += words[currentWordID].width;

                glPopMatrix();

            }
            currX = 0;

        }
    }
}

void ofxTextBlock::_trimLineSpaces()
{
        if (words.size() > 0) {
            //Now delete all leading or ending spaces on each line
            for(int l=0;l < lines.size(); l++)
            {
                //Delete the first word if it is a blank
                if (lines[l].wordsID.size() > 0){
                    if (words[lines[l].wordsID[0]].rawWord == " ")   lines[l].wordsID.erase(lines[l].wordsID.begin());
                }

                //Delete the last word if it is a blank
                if (lines[l].wordsID.size() > 0){
                    if (words[lines[l].wordsID[lines[l].wordsID.size() - 1]].rawWord == " ") lines[l].wordsID.erase(lines[l].wordsID.end() - 1);
                }
            }
        }

}

int ofxTextBlock::_getLinedWords(){

    int wordCount = 0;

    if (words.size() > 0) {

        for(int l=0;l < lines.size(); l++)
        {
            wordCount += lines[l].wordsID.size();
        }
        return wordCount;
    }
    else return 0;
}

void ofxTextBlock::wrapTextArea(float rWidth, float rHeight){

    float tmpScale = 0.0f;
    float maxIterations = _getLinedWords();
    float scales[1000];
    scale = 1.0f;  //Reset the scale for the height and width calculations.

    if (words.size() > 0) {

        //Check each possible line layout and check it will fit vertically
        for (int iteration=1; iteration <= maxIterations; iteration++){

            //printf("Iteration %i...\n", iteration);
            wrapTextForceLines(iteration);

            tmpScale = rWidth / getWidth();
            if ((tmpScale * getHeight()) < rHeight) {
                scales[iteration] = tmpScale;
            }
            else {
                scales[iteration] = -1;
            }
        }

        //Now see which is biggest
        int maxIndex = 1;
        bool bScaleAvailable = false;

        for (int i=1; i <= maxIterations; i++) {
            ofLog(OF_LOG_VERBOSE,"Scales %i = %f\n", i, scales[maxIndex]);
            if (scales[i] != -1) bScaleAvailable = true;

            if (scales[i] > scales[maxIndex]) {
                maxIndex = i;
            }
        }

        //When only one line is needed an appropriate on the Y scale can sometimes not be found.  In these occasions scale the size to the Y dimension
        if (bScaleAvailable) {
            scale = scales[maxIndex];
        }
        else {
            scale = (float)rHeight / (float)getHeight();
        }

        float persistScale = scale; //Need to persist the scale as the wrapTextForceLines will overwrite.
        wrapTextForceLines(maxIndex);
        scale = persistScale;

        ofLog(OF_LOG_VERBOSE,"Scaling with %i at scale %f...\n", maxIndex, scale);
    }


}


bool ofxTextBlock::wrapTextForceLines(int linesN){

    if (words.size() > 0) {

        if (linesN > words.size()) linesN = words.size();

        float lineWidth = _getWidthOfWords() * (1.1f / (float)linesN);

        int curLines = 0;
        bool bGotLines;

        //keep increasing the line width until we get the desired number of lines.
        while (!bGotLines) {

            curLines = wrapTextX(lineWidth);
            if (curLines == linesN) return true;
            if (curLines > linesN) return false;
            lineWidth-=10;

        }

    }

}


int ofxTextBlock::wrapTextX(float lineWidth){

    scale = 1.0f;

    if (words.size() > 0) {

        float   runningWidth = 0.0f;

        lines.clear();

        bool        newLine = true;
        lineBlock   tmpLine;
        tmpLine.wordsID.clear();
        int         activeLine = 0;

        for(int i=0;i < words.size(); i++)
        {

            runningWidth += words[i].width;

            if (runningWidth <= lineWidth) {
                newLine = false;
            }
            else {

                newLine = true;
                lines.push_back(tmpLine);
                tmpLine.wordsID.clear();
                runningWidth = 0.0f + words[i].width;;
                activeLine++;
            }

            tmpLine.wordsID.push_back(i);
        }

        //Push in the final line.
        lines.push_back(tmpLine);
        _trimLineSpaces(); //Trim the leading and trailing spaces.

    }

    return lines.size();

}

void ofxTextBlock::_loadWords(){

    wordBlock tmpWord;

    istringstream iss(rawText);

    vector<string> tokens;
    copy(istream_iterator<string>(iss),
             istream_iterator<string>(),
             back_inserter<vector<string> >(tokens));

    words.clear();

    for(int i=0;i < tokens.size(); i++)
    {
        tmpWord.rawWord = tokens.at(i);
        tmpWord.width   = defaultFont.stringWidth(tmpWord.rawWord);
        tmpWord.height  = defaultFont.stringHeight(tmpWord.rawWord);
        tmpWord.color.r = tmpWord.color.g = tmpWord.color.b = 150;
        words.push_back(tmpWord);
        //add spaces into the words vector if it is not the last word.
        if (i != tokens.size()) words.push_back(blankSpaceWord);
    }

    for(int i=0;i < words.size(); i++)
    {
        ofLog(OF_LOG_VERBOSE, "Loaded word: %i, %s\n", i, words[i].rawWord.c_str());
    }


}

float ofxTextBlock::_getWidthOfWords(){

    float widthTotal = 0.0f;

    if (words.size() > 0) {
        for(int i=0;i < words.size(); i++)
        {
            widthTotal += words[i].width;

        }
        return widthTotal;
    }
    else {
        return 0.0f;
    }

}

float ofxTextBlock::getWidth(){

    int   currentWordID;

    float currX = 0.0f;
    float maxWidth  = 0.0f;

    if (words.size() > 0) {

        for(int l=0;l < lines.size(); l++)
        {
            for(int w=0;w < lines[l].wordsID.size(); w++)
            {
                currentWordID = lines[l].wordsID[w];
                currX += words[currentWordID].width;
            }
            maxWidth = MAX(maxWidth, currX);
            currX = 0.0f;
        }
        return maxWidth * scale;
    }
    else return 0;

}

float ofxTextBlock::getHeight(){

    if (words.size() > 0) {
        return defaultFont.getLineHeight() * scale * lines.size();
    }
    else return 0;

}

void ofxTextBlock::setLineHeight(float lineHeight){

    defaultFont.setLineHeight(lineHeight);

}

void ofxTextBlock::setColor(int r, int g, int b, int a){

    ofColor tmpColor;
    tmpColor.r = r;
    tmpColor.g = g;
    tmpColor.b = b;
    tmpColor.a = a;

    if (words.size() > 0) {
        for(int i=0;i < words.size(); i++)
        {
           words[i].color = tmpColor;

        }
    }

}

void ofxTextBlock::forceScale(float _scale){
    scale = _scale;
}


