#include <string.h>
#include <stdio.h>

#ifdef _WIN32

#include <winsock2.h>
#include <iphlpapi.h>
#pragma comment(lib, "IPHLPAPI.lib")

#else

#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <ifaddrs.h>

#endif

#include "../headFiles/utils/cJSON.h"
#include "../headFiles/States.h"

char* getAdapterJSON()
{
    cJSON* root = cJSON_CreateObject();
    cJSON* adapters = cJSON_CreateArray();
#ifdef _WIN32
    PIP_ADAPTER_INFO pAdapter = NULL;
    ULONG ulOutBufLen = sizeof(IP_ADAPTER_INFO);

    PIP_ADAPTER_INFO pAdapterInfo = malloc(sizeof(IP_ADAPTER_INFO));

    if (GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) == ERROR_BUFFER_OVERFLOW)
    {
        free(pAdapterInfo);
        pAdapterInfo = (IP_ADAPTER_INFO *) malloc(ulOutBufLen);
    }

    if (GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) == NO_ERROR)
    {
        pAdapter = pAdapterInfo;
        while (pAdapter)
        {

            cJSON* adapter = cJSON_CreateObject();
            cJSON_AddStringToObject(adapter, "name", pAdapter->Description);
            cJSON_AddStringToObject(adapter, "ip", pAdapter->IpAddressList.IpAddress.String);
            cJSON_AddItemToArray(adapters, adapter);
            pAdapter = pAdapter->Next;
        }
    }
    if (pAdapterInfo) free(pAdapterInfo);
#else
    struct ifaddrs *ifaddrs_ptr, *ifa;

    if (getifaddrs(&ifaddrs_ptr) == 0)
    {
        for (ifa = ifaddrs_ptr; ifa; ifa = ifa->ifa_next)
        {
            if (ifa->ifa_addr && ifa->ifa_addr->sa_family == AF_INET && strcmp(ifa->ifa_name, "lo") != 0)
            {
                struct sockaddr_in *addr = (struct sockaddr_in*)ifa->ifa_addr;
                char ip[INET_ADDRSTRLEN];
                inet_ntop(AF_INET, &addr->sin_addr, ip, sizeof(ip));
                cJSON* adapter = cJSON_CreateObject();
                cJSON_AddStringToObject(adapter, "name", ifa->ifa_name);
                cJSON_AddStringToObject(adapter, "ip", ip);
                cJSON_AddItemToArray(adapters, adapter);
            }
        }
        freeifaddrs(ifaddrs_ptr);
    }
#endif
    cJSON_AddItemToObject(root, "adapters", adapters);
    char* temp = cJSON_Print(root);
    char* json = strdup(temp);
    cJSON_free(temp);
    cJSON_Delete(root);
    return json;
}