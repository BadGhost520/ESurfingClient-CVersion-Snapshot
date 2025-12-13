//
// Created by bad_g on 2025/11/24.
//
#include <stdio.h>

#include "../headFiles/NetClient.h"
#include "../headFiles/utils/PlatformUtils.h"
#include "../headFiles/utils/CheckAdapters.h"
#include "../headFiles/webserver/mongoose.h"
#include "../headFiles/utils/Logger.h"
#include "../headFiles/utils/cJSON.h"
#include "../headFiles/Options.h"
#include "../headFiles/States.h"

#define VERSION "v2.1.0-r1"

const char* listenAddr = "http://0.0.0.0:8888";

static void fn(struct mg_connection *c, const int ev, void *ev_data)
{
    if (ev == MG_EV_HTTP_MSG)
    {
        struct mg_http_message *hm = (struct mg_http_message *) ev_data;

        if (mg_match(hm->uri, mg_str("/"), NULL) || mg_match(hm->uri, mg_str(""), NULL))
        {
            mg_printf(c,
                "HTTP/1.1 301 Moved Permanently\r\n"
                "Location: /index.html\r\n"
                "Content-Length: 0\r\n"
                "\r\n");
            return;
        }

        // GET 请求
        if (mg_strcmp(hm->method, mg_str("GET")) == 0)
        {
            // 获取内存日志内容
            if (mg_match(hm->uri, mg_str("/api/getLogs"), NULL))
            {
                const LogContent response = getLog();
                mg_http_reply(c,
                    200,
                    "Content-Type: text/plain;charset=utf-8\r\n",
                    "%s",
                    response.data);
                free(response.data);
            }
            // 获取当前设置
            else if (mg_match(hm->uri, mg_str("/api/getSettings"), NULL))
            {
                cJSON* settings = cJSON_CreateObject();
                cJSON_AddStringToObject(settings, "username", usr);
                cJSON_AddStringToObject(settings, "password", pwd);
                cJSON_AddStringToObject(settings, "channel", chn);
                cJSON_AddNumberToObject(settings, "debug", isDebug);
                cJSON_AddNumberToObject(settings, "smallDevice", isSmallDevice);
                char* temp = cJSON_Print(settings);
                char* response = strdup(temp);
                cJSON_Delete(settings);
                free(temp);
                mg_http_reply(c,
                    200,
                    "Content-Type: application/json;charset=utf-8\r\n",
                    "%s",
                    response);
                free(response);
            }
            // 获取联网状态
            else if (mg_match(hm->uri, mg_str("/api/getNetworkStatus"), NULL))
            {
                switch (simGet("http://www.baidu.com"))
                {
                case RequestSuccess:
                    isConnected = 1;
                    if (connectTime == 0) connectTime = currentTimeMillis();
                    break;
                default:
                    isConnected = 0;
                    connectTime = 0;
                }
                cJSON* status = cJSON_CreateObject();
                cJSON_AddNumberToObject(status, "isConnected", isConnected);
                cJSON_AddStringToObject(status, "connectTime", longLongToString(connectTime));
                char* temp = cJSON_Print(status);
                char* response = strdup(temp);
                cJSON_Delete(status);
                free(temp);
                mg_http_reply(c,
                    200,
                    "Content-Type: application/json;charset=utf-8\r\n",
                    "%s",
                    response);
                free(response);
            }
            // 获取软件状态
            else if (mg_match(hm->uri, mg_str("/api/getSoftwareStatus"), NULL))
            {
                cJSON* status = cJSON_CreateObject();
                cJSON_AddNumberToObject(status, "isRunning", isRunning);
                cJSON_AddNumberToObject(status, "isLogged", isLogged);
                cJSON_AddStringToObject(status, "authTime", longLongToString(authTime));
                cJSON_AddStringToObject(status, "version", VERSION);
                char* temp = cJSON_Print(status);
                char* response = strdup(temp);
                cJSON_Delete(status);
                free(temp);
                mg_http_reply(c,
                    200,
                    "Content-Type: application/json;charset=utf-8\r\n",
                    "%s",
                    response);
                free(response);
            }
            // 获取适配器状态
            else if (mg_match(hm->uri, mg_str("/api/getAdapterInfo"), NULL))
            {
                char* response = getAdapterJSON();
                mg_http_reply(c,
                    200,
                    "Content-Type: application/json;charset=utf-8\r\n",
                    "%s",
                    response);
                free(response);
            }
        }
        // POST 请求
        else if (mg_strcmp(hm->method, mg_str("POST")) == 0)
        {
            // 更新设置
            if (mg_match(hm->uri, mg_str("/api/updateSettings"), NULL))
            {
                const struct mg_str body = hm->body;
                cJSON* jsonData = cJSON_Parse(body.buf);
                if (jsonData)
                {
                    cJSON* settings = cJSON_GetObjectItem(jsonData, "settings");
                    if (!settings)
                    {
                        mg_http_reply(c,
                            400,
                            "Content-Type: text/plain;charset=utf-8\r\n",
                            "设置更新失败");
                        cJSON_Delete(jsonData);
                    }
                    else
                    {
                        const cJSON* username = cJSON_GetObjectItem(settings, "username");
                        const cJSON* password = cJSON_GetObjectItem(settings, "password");
                        const cJSON* channel = cJSON_GetObjectItem(settings, "channel");
                        const cJSON* debug = cJSON_GetObjectItem(settings, "debug");
                        const cJSON* smallDevice = cJSON_GetObjectItem(settings, "smallDevice");
                        if (username && cJSON_IsString(username))
                        {
                            usr = strdup(username->valuestring);
                        }
                        if (password && cJSON_IsString(password))
                        {
                            pwd = strdup(password->valuestring);
                        }
                        if (channel && cJSON_IsString(channel))
                        {
                            chn = strdup(channel->valuestring);
                        }
                        if (isDebug && cJSON_IsNumber(debug))
                        {
                            isDebug = debug->valueint;
                        }
                        if (smallDevice && cJSON_IsNumber(smallDevice))
                        {
                            isSmallDevice = smallDevice->valueint;
                        }
                        cJSON_Delete(settings);
                        cJSON_Delete(jsonData);
                        isSettingsChange = 1;
                        mg_http_reply(c,
                            204,
                            "",
                            "");
                    }
                }
                else
                {
                    mg_http_reply(c,
                        400,
                        "Content-Type: text/plain;charset=utf-8\r\n",
                        "设置更新失败");
                }
            }
        }
        const struct mg_http_serve_opts opts = {.root_dir = "./webEsurfingclient", .fs = &mg_fs_posix};
        mg_http_serve_dir(c, hm, &opts);
    }
}

void* webServerMain()
{
    struct mg_mgr mgr;
    mg_mgr_init(&mgr);
    mg_http_listen(&mgr, listenAddr, fn, NULL);

    LOG_INFO("Web 服务器已启动，后台访问地址: http://127.0.0.1:8888");

    isWebserverRunning = 1;
    while (isWebserverRunning) mg_mgr_poll(&mgr, 1000);

    mg_mgr_free(&mgr);
    LOG_INFO("Web 服务器已停止");
    return 0;
}

void startWebServer()
{
    createThread(webServerMain, NULL);
}

void stopWebServer()
{
    isWebserverRunning = 0;
}