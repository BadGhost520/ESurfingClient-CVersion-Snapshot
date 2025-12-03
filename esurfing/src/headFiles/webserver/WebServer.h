//
// Created by bad_g on 2025/11/24.
//

#ifndef ESURFINGCLIENT_WEBSERVER_H
#define ESURFINGCLIENT_WEBSERVER_H

#include "../utils/PlatformUtils.h"

/**
 * 启动Web服务器（在单独的线程中）
 * @return 线程句柄
 */
threadHandle startWebServer();

/**
 * 停止Web服务器
 */
void stopWebServer();

#endif //ESURFINGCLIENT_WEBSERVER_H