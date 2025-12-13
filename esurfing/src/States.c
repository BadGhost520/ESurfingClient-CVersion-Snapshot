//
// Created by bad_g on 2025/9/22.
//
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

#include "headFiles/utils/PlatformUtils.h"
#include "headFiles/utils/Logger.h"
#include "headFiles/States.h"

char* clientId;
char* algoId;
char* macAddress;
char* ticket;
char* userIp;
char* acIp;

int isConnected = 0;
int isRunning = 0;
int isLogged = 0;
int isInitialized = 0;
int isWebserverRunning = 0;
int isSettingsChange = 0;
int webServerStatus = 0;

int64_t authTime = 0;
int64_t connectTime = 0;

char* schoolId;
char* domain;
char* area;
char* ticketUrl;
char* authUrl;

pthread_t webServerThread;

void refreshStates()
{
    if (clientId) free(clientId);
    if (algoId) free(algoId);
    if (macAddress) free(macAddress);
    if (ticket) free(ticket);
    if (schoolId) free(schoolId);
    if (domain) free(domain);
    if (area) free(area);
    clientId = strdup(setClientId());
    algoId = strdup("00000000-0000-0000-0000-000000000000");
    macAddress = strdup(randomMacAddress());
    LOG_DEBUG("Client Id: %s", clientId);
    LOG_DEBUG("MAC: %s", macAddress);
}