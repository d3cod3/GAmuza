#ifndef _GAMUZACONSOLE
#define _GAMUZACONSOLE

#include "gamuzaConstants.h"

//--------------------------------------------------------------
void gamuzaMain::sendGALog(string _message){
    currentGlobalLog = _message;
    [[NSNotificationCenter defaultCenter] postNotificationName:@"GAConsoleLog" object:NULL ];
}

//--------------------------------------------------------------
void gamuzaMain::sendPrivateMessage(int _type, string _message){
    if(_type == GAMUZA_CONSOLE_LOG){
        currentLog      = _message;
        [[NSNotificationCenter defaultCenter] postNotificationName:@"GALogMessageEvent" object:NULL ];
    }else if(_type == GAMUZA_CONSOLE_ERROR){
        currentErrorLog = _message;
        [[NSNotificationCenter defaultCenter] postNotificationName:@"GALogErrorEvent" object:NULL ];
    }
}


#endif
