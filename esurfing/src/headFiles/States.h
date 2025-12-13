//
// Created by bad_g on 2025/9/22.
//

#ifndef ESURFINGCLIENT_STATES_H
#define ESURFINGCLIENT_STATES_H

#include <pthread.h>
#include <stdint.h>

extern char* clientId;
extern char* algoId;
extern char* macAddress;
extern char* ticket;
extern char* userIp;
extern char* acIp;

extern int isConnected;
extern int isRunning;
extern int isLogged;
extern int isInitialized;
extern int isWebserverRunning;
extern int isSettingsChange;
extern int webServerStatus;

extern int64_t authTime;
extern int64_t connectTime;

extern char* schoolId;
extern char* domain;
extern char* area;
extern char* ticketUrl;
extern char* authUrl;

extern pthread_t webServerThread;

/**
 * 刷新状态函数
 */
void refreshStates();

#endif //ESURFINGCLIENT_STATES_H