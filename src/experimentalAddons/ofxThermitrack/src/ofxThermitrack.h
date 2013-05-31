/*

    Thermitrack Camera addon
    http://www.thermitrack.com

    v1.5
    May 2011

*/
#ifndef _THERMITRACK
#define _THERMITRACK

#include "ofMain.h"

#include "ofxThermitrackTypes.h"

class ofxThermitrack{

	public:
        ofxThermitrack();
        ~ofxThermitrack();

        void            setup(string port, int baud, int id);
        void            update();

        // commands from software to camera
        void            flushCameraBuffer();
        void            getVersion();
        void            setBaudRate();
        void            factoryReset();

        // requested packed types
        void            clearRequestedPacketTypes();
        void            addRequestedPacketType(char _type, int _interval);
        void            updateRequestedPacketTypeOnCamera();
        void            setRequestedPacketTypeNone();

        // temp todo sort -------------


		int             getStatus(){ return camStatus; }
		bool            isCamOK(){ return camOk; }
		bool            isSerialOK(){ return serialOk; }

                        // commands (host to camera)

        void            setDefaultPacket(thermitrackPacketList packets);
        void            setDefaultPacketNone();

        void            setParameters(int type, int val);

        // advanced
        void            sendPacketType(thermitrackPacketList packets);


        void            reset();
        void            restartWithWarmup();
        void            getPackets();
        void            waitForPackets();

        int             camPixelVals[THERMITRACK_PIXEL_WIDTH*THERMITRACK_PIXEL_WIDTH];

    protected:

        // process data
        void            processVersion();
        void            processDataStatus();
        void            processDataSinglePoint();
        void            processDataMultiPoints();
        void            processDataImage();
        void            processDataAsciiImage();
        void            processDataResponse();

        // send out
        void            sendData(int nBytes);

        // serial comms
        ofSerial        serial;
        string          comPort;
        int             comBaudRate;
        unsigned char   * inputBuffer;
        int             inputBufferSize;
        unsigned char   * sendBuffer;
        int             sendBufferSize;
        unsigned char   * tempSendBuffer;
        int             tempSendBufferSize;

        // properties
        int             camId;
        char            camIdChar;
        int             myCamSize;
        int             hardwareCamSize;
        bool            bInited;
        bool            fliph;
        bool            flipv;
        int             camStatus;
		bool            camOk;
		bool            serialOk;


        // process variables


        float           onCamPointPosMaxVal;
        vector          <unsigned char> dataIn;

        thermitrackPacketList packetsRequested;

    // -----------------------------------------------------


        vector <ThermitrackPoint> points;

        void addPoint(int id, float x, float y);


};

#endif
