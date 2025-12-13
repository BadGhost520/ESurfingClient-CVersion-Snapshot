#include <pthread.h>
#include <string.h>
#include <stdlib.h>

#include "headFiles/utils/PlatformUtils.h"
#include "headFiles/utils/Logger.h"
#include "headFiles/States.h"

char* macAddress;
char* clientId;
char* algoId;
char* ticket;
char* userIp;
char* acIp;

int isWebserverRunning = 0;
int isSettingsChange = 0;
int webServerStatus = 0;
int isInitialized = 0;
int isConnected = 0;
int isRunning = 0;
int isLogged = 0;

int64_t connectTime = 0;
int64_t authTime = 0;

char* ticketUrl;
char* schoolId;
char* authUrl;
char* domain;
char* area;

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