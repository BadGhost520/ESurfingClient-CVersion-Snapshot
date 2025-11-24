//
// Created by bad_g on 2025/11/24.
//
#include "mongoose.h"
#include "../headFiles/utils/Logger.h"
#include "../headFiles/utils/PlatformUtils.h"
#include <stdio.h>
#include <stdlib.h>

// Web服务器运行标志
static int s_web_server_running = 0;

// 尝试找到web_root目录的函数
static const char* find_web_root() {
    // 定义可能的web_root路径
    static const char* possible_paths[] = {
        "./web_root",
        NULL
    };

    // 测试每个路径
    for (int i = 0; possible_paths[i] != NULL; i++) {
        char test_path[256];
        snprintf(test_path, sizeof(test_path), "%s/index.html", possible_paths[i]);

        FILE* f = fopen(test_path, "r");
        if (f) {
            fclose(f);
            return possible_paths[i];
        }
    }

    LOG_ERROR("无法找到web_root目录");
    return "./web_root"; // 返回默认值
}

// HTTP请求处理函数
static void http_handler(struct mg_connection *c, int ev, void *ev_data) {
    if (ev == MG_EV_HTTP_MSG) {
        struct mg_http_message *hm = (struct mg_http_message *) ev_data;

        // 记录请求信息 - 使用正确的字段名
        char method_buf[32], uri_buf[256];
        snprintf(method_buf, sizeof(method_buf), "%.*s", (int)hm->method.len, hm->method.buf);
        snprintf(uri_buf, sizeof(uri_buf), "%.*s", (int)hm->uri.len, hm->uri.buf);

        // 检查是否请求的是根路径"/"
        if (hm->uri.len == 1 && hm->uri.buf[0] == '/') {
            // 对于根路径请求，重定向到index.html
            mg_printf(c,
                "HTTP/1.1 301 Moved Permanently\r\n"
                "Location: /index.html\r\n"
                "Content-Length: 0\r\n"
                "\r\n");
            return;
        }

        // 设置静态文件服务选项
        struct mg_http_serve_opts opts = {0};
        opts.root_dir = find_web_root();

        // 检查根目录是否存在
        char index_test[256];
        snprintf(index_test, sizeof(index_test), "%s/index.html", opts.root_dir);
        FILE* f = fopen(index_test, "r");
        if (f) {
            fclose(f);
        } else {
            LOG_ERROR("无法找到index.html: %s", index_test);
        }

        // 处理请求
        mg_http_serve_dir(c, hm, &opts);
    }
}

// Web服务器主循环函数
static void *web_server_thread(void *arg) {
    const char* listen_addr = (const char*)arg;
    struct mg_mgr mgr;
    struct mg_connection *c;

    // 初始化事件管理器
    mg_mgr_init(&mgr);

    // 启动监听连接
    c = mg_http_listen(&mgr, listen_addr, http_handler, NULL);
    if (c == NULL) {
        LOG_ERROR("无法启动Web服务器，监听地址: %s", listen_addr);
        mg_mgr_free(&mgr);
        return NULL;
    }

    LOG_INFO("Web服务器已启动，访问地址 %s", listen_addr);

    // 事件循环
    s_web_server_running = 1;
    while (s_web_server_running) {
        mg_mgr_poll(&mgr, 1000);  // 每秒处理一次事件
    }

    // 清理资源
    mg_mgr_free(&mgr);
    LOG_INFO("Web服务器已停止");
    return NULL;
}

// 启动Web服务器（在单独的线程中）
thread_handle_t start_web_server(const char* listen_addr) {
    return create_thread(web_server_thread, (void*)listen_addr);
}

// 停止Web服务器
void stop_web_server() {
    s_web_server_running = 0;
}