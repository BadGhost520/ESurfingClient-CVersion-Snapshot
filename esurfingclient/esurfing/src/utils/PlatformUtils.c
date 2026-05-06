#include "utils/PlatformUtils.h"

#include <curl/curl.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <time.h>

#ifdef _WIN32

#include <sysinfoapi.h>
#include <iphlpapi.h>

#endif

char* xml_parser(const char* xml_data, const char* tag)
{
    if (xml_data == NULL || tag == NULL) return NULL;

    char start_tag[256];
    snprintf(start_tag, sizeof(start_tag), "<%s>", tag);

    char end_tag[256];
    snprintf(end_tag, sizeof(end_tag), "</%s>", tag);

    const char* start_pos = strstr(xml_data, start_tag);
    if (!start_pos) return NULL;
    start_pos += strlen(start_tag);

    const char* end_pos = strstr(start_pos, end_tag);
    if (!end_pos) return NULL;

    const size_t content_length = end_pos - start_pos;
    if (content_length <= 0) return NULL;

    char* content = malloc(content_length + 1);
    if (!content) return NULL;

    strncpy(content, start_pos, content_length);
    content[content_length] = '\0';
    return content;
}

bytes_t str_2_bytes(const char* str)
{
    bytes_t ba = {0};
    if (!str) return ba;
    ba.length = strlen(str);
    ba.data = (uint8_t*)malloc(ba.length);
    if (ba.data) memcpy(ba.data, str, ba.length);
    return ba;
}

uint64_t str_2_uint64(const char* str)
{
    if (!str) return 0;
    while (isspace(*str)) str++;
    if (*str == '\0') return 0;
    char* end_ptr;
    errno = 0;
    const uint64_t value = strtoll(str, &end_ptr, 10);
    if (errno == ERANGE) return 0;
    if (end_ptr == str) return 0;
    while (isspace(*end_ptr)) end_ptr++;
    if (*end_ptr != '\0') return 0;
    return value;
}

char* uint64_2_str(const uint64_t num)
{
    char* result = malloc(22);
    if (!result) return NULL;
    snprintf(result, 22, "%" PRIu64, num);
    return result;
}

uint64_t get_cur_tm_ms()
{
#ifdef _WIN32
    FILETIME ft;
    ULARGE_INTEGER uli;
    GetSystemTimeAsFileTime(&ft);
    uli.LowPart = ft.dwLowDateTime;
    uli.HighPart = ft.dwHighDateTime;
    return uli.QuadPart / 10000LL - 11644473600000LL;
#else
    struct timeval tv;
    if (gettimeofday(&tv, NULL) != 0) return 0;
    return tv.tv_sec * 1000LL + tv.tv_usec / 1000LL;
#endif
}

void get_rand_bytes(uint8_t* buf, const size_t len)
{
#ifdef _WIN32
    HCRYPTPROV h_crypt_prov;
    if (!CryptAcquireContext(&h_crypt_prov, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT)) return;
    CryptGenRandom(h_crypt_prov, len, buf);
    CryptReleaseContext(h_crypt_prov, 0);
#else
    const int fd = open("/dev/urandom", O_RDONLY);
    if (fd == -1) return;
    read(fd, buf, len);
    close(fd);
#endif
}

void sleep_ms(const uint64_t ms)
{
    if (ms <= 0) return;
#ifdef _WIN32
    Sleep(ms);
#else
    usleep(ms * 1000);
#endif
}

void get_fmt_time(char* buf, const TimeFormat fmt)
{
    time_t raw_tm;
    if (time(&raw_tm) == (time_t) - 1)
    {
        fprintf(stderr, "ERROR: 获取系统时间失败\n");
        return;
    }
    struct tm local_tm;
#ifdef _WIN32
    if (localtime_s(&local_tm, &raw_tm) != 0)
    {
        fprintf(stderr, "ERROR: 时间转换失败\n");
        return;
    }
#else
    if (localtime_r(&raw_tm, &local_tm) == NULL)
    {
        fprintf(stderr, "ERROR: 时间转换失败\n");
        return;
    }
#endif
    switch (fmt)
    {
    case CONSOLE_FORMAT:
        if (strftime(buf, 32, "%Y-%m-%d %H:%M:%S", &local_tm) == 0)
        {
            fprintf(stderr, "ERROR: 格式化时间失败\n");
            return;
        }
        return;
    case FILE_FORMAT:
        if (strftime(buf, 32, "%Y%m%d-%H%M%S", &local_tm) == 0)
        {
            fprintf(stderr, "ERROR: 格式化时间失败\n");
        }
    }
}

const char* safe_str(const char* str)
{
    return str ? str : "";
}
