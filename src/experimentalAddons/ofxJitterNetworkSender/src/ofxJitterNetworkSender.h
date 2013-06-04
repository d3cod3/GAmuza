#pragma once

#include "ofMain.h"
#include "ofxNetwork.h"

// http://cycling74.com/sdk/MaxSDK-6.0.4/html/chapter_jit_networking.html
// https://github.com/Cycling74/max6-sdk
// Much of this (and the macros) were gathered from the MaxSDK.

#define MAXDATASIZE 1024 // max number of bytes we can get at once

#define	JIT_MATRIX_MAX_DIMCOUNT	32
#define	MATRIX_DIM		100
#define	MATRIX_PLANES	4
#define	MATRIX_BYTES	MATRIX_PLANES*MATRIX_DIM*MATRIX_DIM

#define SWAP16(x) ((short)(((((unsigned short)(x))>>8)&0x00ff)+((((unsigned short)(x))<<8)&0xff00)))
#define SWAP32(x) ((long)(((((unsigned long)(x))>>24L)&0x000000ff)+((((unsigned long)(x))>>8L)&0x0000ff00)+ \
((((unsigned long)(x))<<24L)&0xff000000)+((((unsigned long)(x))<<8L)&0x00ff0000)))

#define JIT_MATRIX_MAX_DIMCOUNT		32 			///< maximum dimension count
#define JIT_MATRIX_MAX_PLANECOUNT	32 			///< maximum plane count

#define JIT_MATRIX_TYPE_CHAR 0;
#define JIT_MATRIX_TYPE_LONG 1;
#define JIT_MATRIX_TYPE_FLOAT32 2;
#define JIT_MATRIX_TYPE_FLOAT64 3;

#define JIT_MATRIX_PACKET_ID  'JMTX'
#define JIT_MATRIX_LATENCY_PACKET_ID  'JMLP'
#define JIT_MESSAGE_PACKET_ID  'JMMP'

//This chunk header could be represented in C by the following struct:
typedef struct _jit_net_packet_header {
    long id;
    long size; //size of packet to come
} t_jit_net_packet_header;

typedef struct _jit_net_packet_matrix {
    long   id;
    long   size;
    long   planecount;
    long   type;         //0=char,1=long,2=float32,3=float64
    long   dimcount;
    long   dim[JIT_MATRIX_MAX_DIMCOUNT];
    long   dimstride[JIT_MATRIX_MAX_DIMCOUNT];
    long   datasize;
    double   time;
    
} t_jit_net_packet_matrix;

typedef struct _jit_net_packet_latency {
    long id;
    double client_time_original;
    double server_time_before_data; 
    double server_time_after_data;
} t_jit_net_packet_latency;

/* bakercp best guess ...*/

/*
typedef struct _jit_net_packet_message
	{
		long size; // the size of the serialized message in bytes
		long ac; // argument count
//		t_atom av[1024]; // the values
		
		
	} t_jit_net_packet_message;

*/

//typedef struct symbol {
//    char *s_name;			///< name: a c-string
//    struct object *s_thing;	///< possible binding to a t_object
//} Symbol, t_symbol;
//
//union word {
//    long w_long;			///< long integer
//    float w_float;			///< 32-bit float
//    struct symbol *w_sym;	///< pointer to a symbol in the Max symbol table
//    struct object *w_obj;	///< pointer to a #t_object or other generic pointer
//};
//
//typedef struct atom {
//    short a_type;			///< a value as defined in #e_max_atomtypes
//    union word a_w;			///< the actual data
//} Atom, t_atom;

//typedef enum {
//	A_NOTHING = 0,	///< no type, thus no atom
//	A_LONG,			///< long integer
//	A_FLOAT,		///< 32-bit float
//	A_SYM,			///< t_symbol pointer
//	A_OBJ,			///< t_object pointer (for argtype lists; passes the value of sym)
//	A_DEFLONG,		///< long but defaults to zero
//	A_DEFFLOAT,		///< float, but defaults to zero
//	A_DEFSYM,		///< symbol, defaults to ""
//	A_GIMME,		///< request that args be passed as an array, the routine will check the types itself.
//	A_CANT,			///< cannot typecheck args
//	A_SEMI,			///< semicolon
//	A_COMMA,		///< comma
//	A_DOLLAR,		///< dollar
//	A_DOLLSYM,		///< dollar
//	A_GIMMEBACK,	///< request that args be passed as an array, the routine will check the types itself. can return atom value in final atom ptr arg. function returns long error code 0 = no err. see gimmeback_meth typedef
//	
//	A_DEFER	=		0x41,	///< A special signature for declaring methods. This is like A_GIMME, but the call is deferred.
//	A_USURP =		0x42,	///< A special signature for declaring methods. This is like A_GIMME, but the call is deferred and multiple calls within one servicing of the queue are filtered down to one call.
//	A_DEFER_LOW =	0x43,	///< A special signature for declaring methods. This is like A_GIMME, but the call is deferref to the back of the queue.
//	A_USURP_LOW =	0x44	///< A special signature for declaring methods. This is like A_GIMME, but the call is deferred to the back of the queue and multiple calls within one servicing of the queue are filtered down to one call.
//} e_max_atomtypes;

// legacy macros...
//
//#define BAG(s) {error(s); return (0);}
//#define BAG2(s,t) {error(s,t); return (0);}
//#define ob_messlist(x) (((struct object *)(x))->o_messlist - 1)
//#define ob_class(x) ((struct maxclass *) \
//(((struct object *)(x))->o_messlist[-1].m_sym))
//#define ob_name(x) (ob_class(x)->c_sym->s_name)
//#define ob_sym(x) (ob_class(x)->c_sym)
//#define ob_filename(x) (ob_class(x)->c_filename->s_name)
//#define ob_filesym(x) (ob_class(x)->c_filename)
//#define mess0(x, y)  (*((zero_meth)(getfn(x, y))))(x)
//#define mess1(x, y, z1) (*((one_meth)(getfn(x, y))))(x, z1)
//#define mess2(x, y, z1,z2) (*((two_meth)(getfn(x, y))))(x, z1,z2)
//#define mess3(x, y, z1,z2,z3) (*(getfn(x, y)))(x, z1,z2,z3)
//#define mess4(x, y, z1,z2,z3,z4) (*(getfn(x, y)))(x, z1,z2,z3,z4)
//#define mess5(x, y, z1,z2,z3,z4,z5) (*(getfn(x, y)))(x, z1,z2,z3,z4,z5)
//#define NIL ((void *)0)
//#define SETCOMMA(ap) ((ap)->a_type = A_COMMA)
//#define SETSEMI(ap) ((ap)->a_type = A_SEMI)
//#define SETSYM(ap, x) ((ap)->a_type = A_SYM, (ap)->a_w.w_sym = (x))
//#define SETOBJ(ap, x) ((ap)->a_type = A_OBJ, (ap)->a_w.w_obj = (x))
//#define SETLONG(ap, x) ((ap)->a_type = A_LONG, (ap)->a_w.w_long = (x))
//#define SETFLOAT(ap, x) ((ap)->a_type = A_FLOAT, (ap)->a_w.w_float = (x))
//#define SETDOLLAR(ap, x) ((ap)->a_type = A_DOLLAR, (ap)->a_w.w_long = (x))

class ofxJitterNetworkSender : public ofxTCPClient {
public:

    void sendFrame(const ofPixelsRef pixels) {
        int planecount = pixels.getNumChannels();
        int dimcount = 2; // only sending 2d matrices from of
        int dim[dimcount];
        dim[0]       = pixels.getWidth();
        dim[1]       = pixels.getHeight();
        int typeSize = pixels.getBytesPerChannel();
        int type     = JIT_MATRIX_TYPE_CHAR;

        makeMatrixHeader(planecount, typeSize, type, dim, dimcount);

        char *matrix = (char*)pixels.getPixels();
        
        //////SEND ONE MATRIX
        sendRawBytes((char *)(&m_chunkHeader), sizeof(t_jit_net_packet_header));
        sendRawBytes((char *)(&m_matrixHeader), sizeof(t_jit_net_packet_matrix));
        
        int packSize = SWAP32(m_matrixHeader.dimstride[SWAP32(m_matrixHeader.dimcount)-1])
                    * SWAP32(m_matrixHeader.dim[SWAP32(m_matrixHeader.dimcount)-1]);

        sendRawBytes(matrix, packSize);

    }
    
    
    void sendText(const string& txt) {
        m_messageHeader.id = SWAP32(JIT_MESSAGE_PACKET_ID);
        m_messageHeader.size = SWAP32(sizeof(long) + // size
                                      sizeof(long) + // ac
                                      sizeof(char) + // type
                                      sizeof(char)*txt.length() + // number
                                      sizeof(char)); // null terminator
        
        sendRawBytes((char *)&m_messageHeader.id, sizeof(long));
        sendRawBytes((char *)&m_messageHeader.size, sizeof(long));
        
        // the packet
        long messageSizeBytes = m_messageHeader.size; //	32-bit integer that contains the size of the serialized message in bytes. 
        long ac = SWAP32(0);      //    Following that another 32-bit integer gives the argument count for the atoms. 
        /// Following that comes the message atoms themselves, starting with the leading symbol if it exists. 
        //  Each atom is represented in memory first with a char that indicates what type of atom it is:
        //		's' for symbol, 'l' for long, and 'f' for float. 
        //		For long and float atoms, the next 4 bytes contain the value of the atom; 
        //		for symbol atoms a null terminated character string follows. 
        
        
        char atomType = 's'; //'s' for symbol, 'l' for long, and 'f' for float. 
        const char *cp = txt.c_str(); // seriously
        char nullTerm = '\0';
        sendRawBytes((char *)&messageSizeBytes, sizeof(long));
        sendRawBytes((char *)&ac, sizeof(long));
        sendRawBytes((char *)&atomType, sizeof(char));
        sendRawBytes((char *)cp, txt.length()*sizeof(char));
        sendRawBytes((char *)&nullTerm, sizeof(char));
        
        //readResponse();
    }
    
    double getLastSent() {
        return lastSent;
    }

protected: 
    
    void readResponse() {
        // TODO read latency data here.
        
        
        char buf[MAXDATASIZE]; 
        int numBytes = receiveRawBytes(buf, MAXDATASIZE-1);
        if (numBytes == -1) {
            // printf("recv error\n");
            // skip it, there's nothing there
        } else {
            buf[numBytes] = '\0'; // end it
            
            m_latencyPacket.id                      = ((t_jit_net_packet_latency *)buf)->id; // cast it to get the id
            m_latencyPacket.client_time_original    = ((t_jit_net_packet_latency *)buf)->client_time_original;
            m_latencyPacket.server_time_before_data = ((t_jit_net_packet_latency *)buf)->server_time_before_data;
            m_latencyPacket.server_time_after_data  = ((t_jit_net_packet_latency *)buf)->server_time_after_data;
            
//printf("id: %d\n", (m_latencyPacket.id));
//printf("client time original %f\n",m_latencyPacket.client_time_original);
//printf("before Data %fl\n",m_latencyPacket.server_time_before_data);
//printf("after Data %f\n",m_latencyPacket.server_time_after_data);
//printf("diff=%f\n\n",m_latencyPacket.server_time_after_data - m_latencyPacket.server_time_before_data);
            
            // cout << buf << endl;
            
            // if(lastSent >= m_latencyPacket.client_time_original) {
            //  printf("GTOE => last sent=%f and client_time_original=%f\n",lastSent,m_latencyPacket.client_time_original);	
            // } else {
            //  printf("NNNWWW => last sent=%f and client_time_original=%f\n",lastSent,m_latencyPacket.client_time_original);	
            // }
        }
    }

    void makeMatrixHeader(int planecount, int typeSize, int type, int *dim, int dimcount) {
        long i, j, k;
        
        m_chunkHeader.id = SWAP32(JIT_MATRIX_PACKET_ID);
        m_chunkHeader.size = sizeof(t_jit_net_packet_matrix);
        
        m_matrixHeader.id = JIT_MATRIX_PACKET_ID;
        m_matrixHeader.size = SWAP32(sizeof(t_jit_net_packet_matrix));
        m_matrixHeader.planecount = SWAP32(planecount);
        m_matrixHeader.type = SWAP32(type);
        m_matrixHeader.dimcount = SWAP32(dimcount);
        
        for(i=0; i < dimcount; i++) {
            m_matrixHeader.dim[i] = SWAP32(dim[i]);
        }
        
        while(i < JIT_MATRIX_MAX_DIMCOUNT) {
            m_matrixHeader.dim[i] = SWAP32(0); // <-- in the jitter one, they seem to just copy the dim through ...
            i++;
        }
        
        //special case for first value
        m_matrixHeader.dimstride[0] = SWAP32(typeSize * planecount);
        
        for(i=1; i <= dimcount; i++) {
            m_matrixHeader.dimstride[i] = SWAP32(dim[i-1]*SWAP32(m_matrixHeader.dimstride[i-1])); // watch out for these .. they need to come back ...
        }
        
        while(i < JIT_MATRIX_MAX_DIMCOUNT) {
            m_matrixHeader.dimstride[i] = SWAP32(0);
            i++;
        }
        
        m_matrixHeader.datasize = SWAP32(SWAP32(m_matrixHeader.dimstride[dimcount-1])*SWAP32(m_matrixHeader.dim[dimcount-1]));
        m_matrixHeader.time = ofGetElapsedTimef();

        // just to keep track
        lastSent = m_matrixHeader.time;

    }

    
	double lastSent;
    
    t_jit_net_packet_header  m_chunkHeader;
    t_jit_net_packet_matrix  m_matrixHeader;
    t_jit_net_packet_latency m_latencyPacket;
    t_jit_net_packet_header  m_messageHeader;

};




