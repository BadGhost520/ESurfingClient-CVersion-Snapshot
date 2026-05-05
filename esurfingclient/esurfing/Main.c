#include "cipher/CipherInterface.h"
#include "utils/Shutdown.h"
#include "utils/Logger.h"

#include <stdlib.h>

int main()
{
#ifdef _WIN32
    system("chcp 65001 >nul");
#endif

    init_shutdown_hook(); // 初始化关闭钩子

    if (init_logger() == false) shut(1); // 初始化日志系统

    char* algo_id = NULL;

    while (true)
    {
        printf("输入 Algo-id: ");
        scanf("%s", algo_id);
        init_cipher(algo_id);
        int choose = 0;
        do
        {
            printf("\n");
            printf("1. 加密数据\n");
            printf("2. 解密数据\n");
            printf("0. 返回\n");
            printf("输入选项: ");
            scanf("%d", &choose);
            char* text = NULL;
            switch (choose)
            {
            case 1:
                ;
                printf("\n");
                printf("输入要加密的数据: ");
                scanf("%s", text);
                char* encrypt = session_encrypt(text);
                printf("加密后的数据: %s", encrypt);
                break;
            case 2:
                ;
                printf("\n");
                printf("输入要解密的数据: ");
                scanf("%s", text);
                char* dncrypt = session_encrypt(text);
                printf("解密后的数据: %s", dncrypt);
                break;
            default:
                break;
            }
        } while (choose != 0);
    }
}
