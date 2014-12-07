/*

    Thermitrack Camera addon
    http://www.thermitrack.com

    v1.5
    May 2011

*/

#include "ofxThermitrack.h"

ofxThermitrack::ofxThermitrack(){

    // defaults
    camId = 1;
    camStatus = 77;

    bInited = false;

	camOk = false;
	serialOk = false;

    string myNumString = ofToString( camId );
    const char * myNumChars = myNumString.c_str();
    camIdChar = myNumChars[0];

    inputBufferSize = 600;
    sendBufferSize = 10;
    tempSendBufferSize = 13;

    inputBuffer = new unsigned char[inputBufferSize];
    for(int i=0; i<inputBufferSize; i++){
        inputBuffer[i] = (unsigned char)0;
    }
    sendBuffer = new unsigned char[sendBufferSize];
    for(int i=0; i<sendBufferSize; i++){
        sendBuffer[i] = (unsigned char)0;
    }
    tempSendBuffer = new unsigned char[tempSendBufferSize];
    for(int i=0; i<tempSendBufferSize; i++){
        tempSendBuffer[i] = (unsigned char)0;
    }

    // set pixel buffer vals to zero
    for(int i=0; i<(THERMITRACK_PIXEL_WIDTH*THERMITRACK_PIXEL_WIDTH); i++){
        camPixelVals[i] = 0;
    }

    dataIn.clear();

}
// ----------------------------------------------------------------------------
ofxThermitrack::~ofxThermitrack(){
    dataIn.clear();
    if(bInited){
        bInited = false;
        serial.close();
    }
}
// ----------------------------------------------------------------------------
void ofxThermitrack::setup(string port, int baud, int id){

    comPort = port;
    comBaudRate = baud;

    serial.enumerateDevices();
    serialOk = serial.setup(comPort, comBaudRate);

    // todo : change to verbose
    printf("thermitrack: serialOk = %i port=%s\n", (int)serialOk, port.c_str());

    if(serialOk) bInited = true;

    getVersion();

}
// ----------------------------------------------------------------------------
void ofxThermitrack::update(){

    // if setup has been called
    if(bInited){

        memset(inputBuffer, 0, inputBufferSize);

        // is there a buffer from serial port?
        int nRead = serial.readBytes(inputBuffer, inputBufferSize);
        if(nRead > 0){

            // loop through each byte
            for(int i=0; i<nRead; i++){

                // if its not a new line, push into vector dataIn
                if(inputBuffer[i] != 13){
                    dataIn.push_back( inputBuffer[i] );

                // byte must be a new line, time to process the buffer
                }else{

                    // 0 byte = network id
                    // 1 byte = first val
                    char firstValChar = (char)dataIn[0];
                    char secondValChar = (char)dataIn[1];

                    // process the incoming data depending on the packet type
                    switch (secondValChar){
                        case THERMITRACK_PACKET_TYPE_VERSION:
                            processVersion();
                            break;
                        case THERMITRACK_PACKET_TYPE_STATUS:
                            processDataStatus();
                            break;
                        case THERMITRACK_PACKET_TYPE_SINGLE:
                            processDataSinglePoint();
                            break;
                        case THERMITRACK_PACKET_TYPE_SINGLE_BINARY:
                            // not needed in this addon
                            break;
                        case THERMITRACK_PACKET_TYPE_MULTI:
                            processDataMultiPoints();
                            break;
                        case THERMITRACK_PACKET_TYPE_MULTI_BINARY:
                            // not needed in this addon
                            break;
                        case THERMITRACK_PACKET_TYPE_IMAGE:
                            processDataImage();
                            break;
                        case THERMITRACK_PACKET_TYPE_ASCIIART:
                            // not needed in this addon
                            break;
                            case THERMITRACK_PACKET_TYPE_RESPONSE:
                            processDataResponse();
                        break;
                    }

                    // clear storage buffer vector
                    dataIn.clear();
                }
            }
        }else{
            camOk = false;
        }
    }//bInited
}
// ----------------------------------------------------------------------------
void ofxThermitrack::processDataStatus(){

    // e.g. S99,00,0
    int imageBytesSize = dataIn.size();
    string temp = "";
    for(int i=0; i<imageBytesSize; i++){
        temp += (char)dataIn[i];
    }
    printf("string = %s\n", temp.c_str());
    string st = temp.substr(2,2);
    camStatus = ofToInt(st);
    printf("cam status = %i\n", camStatus);
}
// ----------------------------------------------------------------------------
void ofxThermitrack::processDataSinglePoint(){

    points.clear();



    // make sure there are 13 chars in the array
    // 0 = cam id
    // 1 = type
    if(dataIn.size() == 13){

        // if there are any single objects being tracked
        if(((char)dataIn[1])=='O'){

            string temp = "";

            // tracked object id
            temp = (char)dataIn[2];
            int id = ofToInt(temp);

            // xposition
            temp = "";
            temp += (char)dataIn[4];
            temp += (char)dataIn[5];
            temp += (char)dataIn[6];
            temp += (char)dataIn[7];
            int tx = ofToInt(temp);

            // yposition
            temp = "";
            temp += (char)dataIn[9];
            temp += (char)dataIn[10];
            temp += (char)dataIn[11];
            temp += (char)dataIn[12];
            int ty = ofToInt(temp);

            float txNorm = tx / (float)THERMITRACK_POINTS_MAXWIDTH;
            float tyNorm = ty / (float)THERMITRACK_POINTS_MAXWIDTH;

            addPoint(id, txNorm, tyNorm);


        }
    }

}
// ----------------------------------------------------------------------------
void ofxThermitrack::processDataMultiPoints(){

    points.clear();

    // put data into string
    string temp = "";
    for(int i=0; i<dataIn.size(); i++){
        temp += (char)dataIn[i];
    }

    // how many points are there?
    string numponts = temp.substr(1, 2);
    int nPoints = ofToInt(numponts);

	// todo: tidy this up, commented out for now
	
    if(nPoints > 0){
/*
        // get the string without the first 4 chars
        temp = temp.substr(4, temp.size());

        // split the string into an array
        vector<string> vecstrResult;
        int startpos=0;
        int endpos = temp.find_first_of(",", startpos);
        while (endpos != -1){
            vecstrResult.push_back(temp.substr(startpos, endpos-startpos)); // add to vector
            startpos = endpos+1; //jump past sep
            endpos = temp.find_first_of(",", startpos); // find next
            if(endpos==-1){
            //lastone, so no 2nd param required to go to end of string
            vecstrResult.push_back(temp.substr(startpos));
            }
        }
        for(int i=0; i<nPoints; i++){
            //trackedPoints.push_back( irisysTrackPoint() );
            //trackedPoints[i].id = (myNum*100)+ofToInt(vecstrResult[i*3]);
           // trackedPoints[i].pos.x = ofToInt(vecstrResult[(i*3)+1]);
            //trackedPoints[i].pos.y = ofToInt(vecstrResult[(i*3)+2]);
            //trackedPoints[i].posNormalised.x = trackedPoints[i].pos.x / pointMaxPosVal;
            //trackedPoints[i].posNormalised.y = trackedPoints[i].pos.y / pointMaxPosVal;

            //float txNorm = tx / (float)THERMITRACK_POINTS_MAXWIDTH;
            //float tyNorm = ty / (float)THERMITRACK_POINTS_MAXWIDTH;

            //addPoint(id, txNorm, tyNorm);
        }*/
    }


}

// ----------------------------------------------------------------------------
void ofxThermitrack::addPoint(int id, float x, float y){

   // printf("%f %f\n", x, y);
    ThermitrackPoint temp;
    temp.id = id;
    temp.x = x;
    temp.y = y;

    points.push_back( temp );

}
// ----------------------------------------------------------------------------
void ofxThermitrack::processDataImage(){

    int imageBytesSize = dataIn.size();

    // image buffer bytes should be 258
    // (id)+I+256 pixels (16x16)
    if(imageBytesSize == 258){
        //printf("got image\n");
        int counter = 0;
        for(int i=0; i<THERMITRACK_PIXEL_WIDTH; i++){ // y
            for(int j=0; j<THERMITRACK_PIXEL_WIDTH; j++){ // x

                 // ignore camera id, and I char
                int tb = dataIn[counter+2];

                // this pixel val
                camPixelVals[counter] = tb;

                counter++;
            }
        }
    }

}
// ----------------------------------------------------------------------------
void ofxThermitrack::processDataResponse(){
    /*
    string temp = "";
    for(int i=0; i<dataIn.size(); i++){
        temp += (char)dataIn[i];
    }
    printf("%s", temp.c_str());
    */
}
// ----------------------------------------------------------------------------
void ofxThermitrack::sendData(int nBytes){

    // add network id to the front of list
    sendBuffer[0] = (unsigned char)'*';
    sendBuffer[1] = (unsigned char)camIdChar;

    // copy from tempSendBuffer to sendBuffer
    for(int i=0; i<nBytes; i++){
        sendBuffer[i+2] = tempSendBuffer[i];
    }

    int realNumBytes = nBytes+3;

    // carriage return at the end
    sendBuffer[realNumBytes-1] = (unsigned char)13;

    // write bytes to serial port
    int byteswritten = serial.writeBytes(sendBuffer, realNumBytes);

    // error check
    bool ok = true;
    if(byteswritten != realNumBytes){
        ok = false;
        // todo event call here
    }

}

// ----------------------------------------------------------------------------
void ofxThermitrack::getVersion(){
    tempSendBuffer[0] = (unsigned char)'V';
    sendData(1);
}
void ofxThermitrack::processVersion(){

    // todo stor in array?

    for(int i=0; i<dataIn.size(); i++){
    printf("%c", (char)dataIn[i]);
    }
    printf("\n");

}

// ----------------------------------------------------------------------------

void ofxThermitrack::clearRequestedPacketTypes(){
    packetsRequested.clear();
}
void ofxThermitrack::addRequestedPacketType(char _type, int _interval){
    packetsRequested.addPacket(_type, _interval);
}
void ofxThermitrack::updateRequestedPacketTypeOnCamera(){

    sendPacketType( packetsRequested);

}
void ofxThermitrack::setRequestedPacketTypeNone(){
    clearRequestedPacketTypes();
    tempSendBuffer[0] = (unsigned char)'T';
    sendData(1);
}

// ----------------------------------------------------------------------------
void ofxThermitrack::setDefaultPacket(thermitrackPacketList packets){
/*
    tempSendBuffer[0] = (unsigned char)'D';
    tempSendBuffer[1] = (unsigned char)THERMITRACK_CR;
    int writenbytes = serial.writeBytes(tempSendBuffer, 2);
*/
}
// ----------------------------------------------------------------------------
void ofxThermitrack::setDefaultPacketNone(){
    tempSendBuffer[0] = (unsigned char)'D';
    sendData(1);
}
// ----------------------------------------------------------------------------
void ofxThermitrack::setBaudRate(){
    // todo
}
// ----------------------------------------------------------------------------
void ofxThermitrack::factoryReset(){
    tempSendBuffer[0] = (unsigned char)'Z';
    tempSendBuffer[1] = (unsigned char)'Y';
    sendData(2);
}
// ----------------------------------------------------------------------------
void ofxThermitrack::setParameters(int type, int val){

    string strType = ofToString(type);
    const char * strTypeChar = strType.c_str();
    string strVal = ofToString(val);
    const char * strValChar = strVal.c_str();

    tempSendBuffer[0] = (unsigned char)'P';
    tempSendBuffer[1] = (unsigned char)strTypeChar[0];
    tempSendBuffer[2] = (unsigned char)'=';
    tempSendBuffer[3] = (unsigned char)strValChar[0];

    sendData(4);

}
// ----------------------------------------------------------------------------
void ofxThermitrack::sendPacketType(thermitrackPacketList packets){

    tempSendBuffer[0] = (unsigned char)'T';
    int bufsize = 1;

    int numPackets = packets.size();

    // for each packet
    for(int i=0; i<numPackets; i++){

        // what type of packet?
        tempSendBuffer[bufsize] = (unsigned char)packets.pckts[i].type;
        bufsize++;

        // comma
        tempSendBuffer[bufsize] = (unsigned char)',';
        bufsize++;

        // the frame interval, as a string, how many chars?
        int intervalStringLen = packets.pckts[i].intervalStringLength;

        // add each number of the interval to the output buffer
        for(int j=0; j<intervalStringLen; j++){
            tempSendBuffer[bufsize] = (unsigned char)packets.pckts[i].intervalChar[j];
            bufsize++;
        }

        if(i<(numPackets-1)){
            // comma
            tempSendBuffer[bufsize] = (unsigned char)',';
            bufsize++;
        }
    }
    sendData(bufsize);
}
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
void ofxThermitrack::reset(){
/*
    // send some empty returns
    tempSendBuffer[0] = (unsigned char)'';
    sendData(1);

    // restart
    tempSendBuffer[0] = (unsigned char)'R';
    sendData(1);
    */
}
// ----------------------------------------------------------------------------
void ofxThermitrack::getPackets(){
}
// ----------------------------------------------------------------------------
void ofxThermitrack::waitForPackets(){
}
// ----------------------------------------------------------------------------
void ofxThermitrack::flushCameraBuffer(){
    tempSendBuffer[0] = (unsigned char)'X';
    sendData(1);
}

