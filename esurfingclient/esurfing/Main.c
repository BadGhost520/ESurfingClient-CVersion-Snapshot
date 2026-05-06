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
}
