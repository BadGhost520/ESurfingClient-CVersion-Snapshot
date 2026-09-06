#include "utils/PlatformUtils.h"
#include "utils/Shutdown.h"
#include "utils/Service.h"
#include "utils/Logger.h"
#include "States.h"

#include <stdlib.h>
#include <stdio.h>

extern bool start_web_server();

int main()
{
#ifdef _WIN32
    system("chcp 65001 >nul");
#endif
    char choice;

    g_start_run_tm = get_cur_tm_ms(); // 获取开始运行的时间

    g_prog_status = calloc(1, sizeof(prog_status_t)); // 初始化 g_prog_status 指针并分配 1 个空间

    init_shutdown_hook(); // 初始化关闭钩子

    if (init_logger() == false) return 1; // 初始化日志系统

    if (start_web_server() == false) shut(1); // 启动 Web 服务器线程

    printf("是否要加载配置文件?(Y/n)");
    scanf_s("%c", &choice);
    getchar();
    if (choice == 'N' || choice == 'n')
    {
        // 不加载配置文件
    }
    else
    {
        if (load_cfg() == false) shut(1); // 加载配置文件
    }

    printf("1. 加解密\n");
    printf("2. 选项二\n");
    printf("0. 退出\n");
    printf("请输入你的选择：");
    scanf_s("%c", &choice);
    getchar();

    switch (choice) {
    case '1':
        printf("加解密\n");
        char algo_id[40] = {0};
        printf("algo id: ");
        scanf("%s", algo_id);
        init_cipher(algo_id);
        printf("\n要解密的内容: ");

        char buffer[1024] = {0};
        scanf("%s", buffer);
        char* decrypt = session_decrypt(buffer);
        printf("\n解密后的内容: %s", decrypt);
        system("pause >nul");
        break;
    case '2':
        printf("你选择了选项二\n");
        break;
    case '0':
        printf("正在退出...\n");
        break;
    default:
        printf("无效选择\n");
    }

    shut(0);
}
