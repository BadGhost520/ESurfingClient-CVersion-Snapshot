#ifndef CIPHER_INTERFACE_H
#define CIPHER_INTERFACE_H

#include "cipher/impl/mod_xtea_cbc_triple_pc.h"
#include "cipher/impl/des_ecb_six_pc.h"
#include "cipher/impl/desede_cbc_pc.h"
#include "cipher/impl/mod_xtea_pc.h"
#include "cipher/impl/aes_cbc_pc.h"
#include "cipher/impl/aes_ecb_pc.h"

#include "cipher/impl/mod_xtea_iv.h"
#include "cipher/impl/desede_cbc.h"
#include "cipher/impl/desede_ecb.h"
#include "cipher/impl/mod_xtea.h"
#include "cipher/impl/aes_cbc.h"
#include "cipher/impl/aes_ecb.h"
#include "cipher/impl/sm4_cbc.h"
#include "cipher/impl/sm4_ecb.h"
#include "cipher/impl/zuc.h"

#include <stdbool.h>

typedef struct cipherInterface {
    char* (*encrypt)(struct cipherInterface* self, const char* text);
    char* (*decrypt)(struct cipherInterface* self, const char* hex);
    void (*destroy)(struct cipherInterface* self);
    void* private_data;
} cipher_interface_t;

/**
 * 销毁加解密工厂
 */
void destroy_cipher_factory();

/**
 * 初始化加解密工厂
 * @param algo_id 算法 ID
 * @return 初始化状态
 */
bool init_cipher(const char* algo_id);

/**
 * 加密函数
 * @param text 需要加密的文本
 * @return 加密后文本
 */
char* session_encrypt(const char* text);

/**
 * 解密函数
 * @param text 需要解密的文本
 * @return 加密后文本
 */
char* session_decrypt(const char* text);

#endif // CIPHER_INTERFACE_H
