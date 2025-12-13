#ifndef ESURFINGCLIENT_STATES_H
#define ESURFINGCLIENT_STATES_H

#include <pthread.h>
#include <stdint.h>

extern char* macAddress;
extern char* clientId;
extern char* algoId;
extern char* ticket;
extern char* userIp;
extern char* acIp;

extern int isWebserverRunning;
extern int isSettingsChange;
extern int webServerStatus;
extern int isInitialized;
extern int isConnected;
extern int isRunning;
extern int isLogged;

extern int64_t connectTime;
extern int64_t authTime;

extern char* ticketUrl;
extern char* schoolId;
extern char* authUrl;
extern char* domain;
extern char* area;

extern pthread_t webServerThread;

/**
 * 刷新状态函数
 */
void refreshStates();

#endif //ESURFINGCLIENT_STATES_H