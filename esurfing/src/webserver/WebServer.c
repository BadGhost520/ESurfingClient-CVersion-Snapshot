//
// Created by bad_g on 2025/11/24.
//
#include <stdio.h>

#include "../headFiles/webserver/mongoose.h"
#include "../headFiles/utils/Logger.h"
#include "../headFiles/utils/PlatformUtils.h"
#include "../headFiles/States.h"
#include "../headFiles/utils/CheckAdapters.h"

const char* listenAddr = "http://0.0.0.0:9191";

static void httpHandler(struct mg_connection *c, int ev, void *ev_data)
{
    if (ev == MG_EV_HTTP_MSG)
    {
        struct mg_http_message *hm = ev_data;

        if (hm->uri.len == 1 && hm->uri.buf[0] == '/')
        {
            mg_printf(c,
                "HTTP/1.1 301 Moved Permanently\r\n"
                "Location: /index.html\r\n"
                "Content-Length: 0\r\n"
                "\r\n");
            return;
        }

        if (mg_match(hm->uri, mg_str("/api/getStatus"), NULL))
        {
            if (mg_strcmp(hm->method, mg_str("GET")) == 0)
            {
                char* response_data = getAdapterJSON();

                mg_printf(c,
                    "HTTP/1.1 200 OK\r\n"
                    "Content-Type: application/json\r\n"
                    "Content-Length: %d\r\n"
                    "\r\n"
                    "%s",
                    (int)strlen(response_data), response_data);

                free(response_data);
                return;
            }
        }

        struct mg_http_serve_opts opts = {0};
        opts.root_dir = "./webEsurfingclient";

        mg_http_serve_dir(c, hm, &opts);
    }
}

static void* webServerThread()
{
    struct mg_mgr mgr;

    mg_mgr_init(&mgr);

    if (mg_http_listen(&mgr, listenAddr, httpHandler, NULL) == NULL)
    {
        LOG_ERROR("无法启动 Web 服务器");
        LOG_WARN("请检查 9191 端口是否被占用");
        mg_mgr_free(&mgr);
        return NULL;
    }

    LOG_INFO("Web 服务器已启动，后台访问地址: %s", listenAddr);

    isWebserverRunning = 1;
    while (isWebserverRunning)
    {
        mg_mgr_poll(&mgr, 1000);
    }

    mg_mgr_free(&mgr);
    LOG_INFO("Web 服务器已停止");
    return NULL;
}

threadHandle startWebServer()
{
    return createThread(webServerThread, NULL);
}

void stopWebServer()
{
    isWebserverRunning = 0;
}