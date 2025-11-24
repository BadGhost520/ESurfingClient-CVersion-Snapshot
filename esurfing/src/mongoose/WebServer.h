//
// Created by bad_g on 2025/11/24.
//

#ifndef ESURFINGCLIENT_WEBSERVER_H
#define ESURFINGCLIENT_WEBSERVER_H

#include "../headFiles/utils/PlatformUtils.h"

/**
 * 启动Web服务器（在单独的线程中）
 * @param listen_addr 监听地址，例如 "http://0.0.0.0:8000"
 * @return 线程句柄
 */
thread_handle_t start_web_server(const char* listen_addr);

/**
 * 停止Web服务器
 */
void stop_web_server();

#endif //ESURFINGCLIENT_WEBSERVER_H