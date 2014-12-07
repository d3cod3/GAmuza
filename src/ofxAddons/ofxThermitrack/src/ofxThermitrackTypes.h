/*

    Thermitrack Camera addon
    http://www.thermitrack.com
    
    v1.5
    May 2011

*/

#ifndef _OFX_THERMITRACK_TYPES
#define _OFX_THERMITRACK_TYPES

// ------- status from camera ----------------------

#define THERMITRACK_STATUS_FAULT 16
#define THERMITRACK_STATUS_WARMUP 4095

// ------- image and pixel size from camera ----------------------

#define THERMITRACK_PIXEL_WIDTH 16
#define THERMITRACK_POINTS_MAXWIDTH 4095 // points x or y are 0-4095 coming from camera

// ------- param -------------------------------------------------

#define THERMITRACK_PARAM_TRCKMODE 0
#define THERMITRACK_PARAM_IMGFILT 1
#define THERMITRACK_PARAM_IMGMODE 2
//#define THERMITRACK_PARAM_IMGFILT 3
#define THERMITRACK_PARAM_IMGMIN 4
#define THERMITRACK_PARAM_IMGMAX 5
#define THERMITRACK_PARAM_NETID 5

// ------- types of packets --------------------------------------

#define THERMITRACK_PACKET_TYPE_VERSION 'V'
#define THERMITRACK_PACKET_TYPE_STATUS 'S'
#define THERMITRACK_PACKET_TYPE_SINGLE 'O'
#define THERMITRACK_PACKET_TYPE_SINGLE_BINARY 'U' // not needed in this addon
#define THERMITRACK_PACKET_TYPE_MULTI 'M'
#define THERMITRACK_PACKET_TYPE_MULTI_BINARY 'N' // not needed in this addon
#define THERMITRACK_PACKET_TYPE_IMAGE 'I'
#define THERMITRACK_PACKET_TYPE_ASCIIART 'A' // not needed in this addon
#define THERMITRACK_PACKET_TYPE_RESPONSE '='

// ------- point --------------------------------------------------

typedef struct{
        int id;
        float x;
        float y;
}ThermitrackPoint;

// ------- types --------------------------------------------------

class thermitrackPacket{
  public:
    char type;
    int interval;
    int intervalStringLength;
    char intervalChar[5];

    thermitrackPacket(){
    };
    thermitrackPacket( char _type=' ', int _interval=255 ) {
        type = _type;
        interval = _interval;
        string intervalString = ofToString(interval);
        intervalStringLength = intervalString.length();
        sprintf(intervalChar, "%i", interval);
    }
};

class thermitrackPacketList{
    public:
        vector <thermitrackPacket> pckts;
        thermitrackPacketList(){
            clear();
        };
        void addPacket(char type, int interval){
            interval = max(0, interval);
            interval = min(255, interval);
            pckts.push_back( thermitrackPacket(type, interval) );
        }
        void clear(){
            pckts.clear();
        }
        int size(){
            return pckts.size();
        }
};

#endif
