/*
//测试读取文件内容并加密的功能
#include <stdio.h>
#include <stdlib.h>
#include "Bytetohex.h"
#include "stringtohex.h"
#include "SM4.H"

int main()
{
    int i = 0;
    FILE *fp;
    size_t size;
    sm4_context ctx;
    unsigned char input[64];
    unsigned char output[64];
    //加密前的十六进制数组
    unsigned char *beforeEnc;
    //加密后的十六进制数组
    unsigned char *afterEnc;
    //16长度的十六进制数组
    unsigned char tem[16];
    //加密得到的十六进制数组
    unsigned char Enc[16];
    //密钥
    unsigned char key[16] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef, 0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10};
    fp = fopen("image.txt", "rb+");
    if (fp == NULL)
    {
        printf("file open failed");
        return -1;
    }
    size = fread(input, 1, 32, fp);
    if (size != 32)
    {
        printf("file read failed");
        return -1;
    }
    //将二进制流转化为十六进制字符串
    Hex2Str(input, output, size * 2);
    output[size * 2] = '\0';
    printf("Output:%s \n", output);
    printf("OutputSize:%d\n", strlen(output));
    //将十六进制字符转化为十六进制数组
    beforeEnc = malloc(sizeof(char) * size);
    afterEnc = malloc(sizeof(char) * size);
    StringToHex(output, beforeEnc);

    //对十六进制数组加密
    printf("\n");
    sm4_setkey_enc(&ctx, key); //设置密钥
    for (size_t i = 0; i < 32; i += 16)
    {
        for (size_t j = 0; j < 16; j++)
        {
            tem[j] = output[i + j];
        }
        sm4_crypt_ecb(&ctx, 1, 16, tem, Enc); //以16为一组进行加密
        for (size_t k = 0; k < 16; k++)
        {
            afterEnc[k] = Enc[i + k];
        }
        for (size_t l = 0; l < 16; l++)
        {
            printf("%02X", Enc[l]);
        }
        printf("\n");
    }
    system("pause");
    return 0;
} */