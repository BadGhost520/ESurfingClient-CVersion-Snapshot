//
// Created by bad_g on 2025/9/22.
//

#ifndef ESURFINGCLIENT_STATES_H
#define ESURFINGCLIENT_STATES_H

#include "utils/PlatformUtils.h"

extern char* clientId;
extern char* algoId;
extern char* macAddress;
extern char* ticket;
extern char* userIp;
extern char* acIp;

extern int isRunning;
extern int isLogged;
extern int isInitialized;
extern int isWebserverRunning;

extern long long authTime;

extern char* schoolId;
extern char* domain;
extern char* area;
extern char* ticketUrl;
extern char* authUrl;

extern threadHandle webServerInstance;

/**
 * 刷新状态函数
 */
void refreshStates();

#endif //ESURFINGCLIENT_STATES_H