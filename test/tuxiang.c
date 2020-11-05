/* 
//总函数
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stdint.h>
#include "sm4.h"
#include "stringtohex.h"
int main()
{
    FILE *fp = NULL;
    sm4_context ctx;
    unsigned int imageSize;       //图片字节数
    char *imageBmpHead;           //图像文件头指针
    char *imageBin;               //图像读取指针
    char *imageBase64;            //图像编码指针
    char *imageOutput;            //图像输出指针
    unsigned char key[16] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef, 0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10};
    size_t result;                //
    unsigned int base64StrLength; //编码后长度
    char *strhex;                 //转化的16进制
    int i;                        //用于存储字符
    //加密前的十六进制数组
    unsigned char *beforeEnc;
    //加密后的十六进制数组
    unsigned char *afterEnc;
    //16长度的十六进制数组
    unsigned char tem[16];
    //加密得到的十六进制数组
    unsigned char Enc[16];
    //读取待编码图片，rb表示以二进制打开
    fp = fopen("image\\greatwall2px4px.bmp", "rb");
    if (fp == NULL)
    {
        printf("file open failed");
        return -1;
    }

    //成功读取之后获取图片大小
    fseek(fp, 0L, SEEK_END);
    imageSize = ftell(fp) - 54;
    fseek(fp, 0L, SEEK_SET);

    //给文件头分配空间
    imageBmpHead = (char *)malloc(sizeof(char) * 54);
    if (imageBmpHead == NULL)
    {
        printf("imageBmpHead malloc failed");
        return -1;
    }
    //读取文件头
    result = fread(imageBmpHead, 1, 54, fp);
    if (result != 54)
    {
        printf("file read failed");
        return -1;
    }
    else
    {
        printf("bmpHeaderSize:%d\n", result);
    }

    fseek(fp, 54, SEEK_SET);
    //给图像数据分配空间
    imageBin = (char *)malloc(sizeof(char) * imageSize);
    if (imageBin == NULL)
    {
        printf("imageBin malloc failed");
        return -1;
    }
    //存储图像数据
    result = fread(imageBin, 1, imageSize, fp);
    if (result != imageSize)
    {
        printf("file read failed");
        return -1;
    }
    else
    {
        printf("ImageSize:%d\n", result);
    }

    strhex = (char *)malloc(sizeof(char) * imageSize);

    //将二进制流转换为16进制字符串
    Hex2Str(imageBin, strhex, imageSize);
    strhex[imageSize * 2] = '\0';
    //将16进制字符串转化为字符数组
    printf("Output:%s \n", strhex);
    printf("OutputSize:%d\n", strlen(strhex));
    beforeEnc=malloc(sizeof(unsigned char)*imageSize);
    StringToHex(strhex,beforeEnc);
    
    //对十六进制数组加密
    printf("\n");
    sm4_setkey_enc(&ctx, key); //设置密钥
    for (size_t i = 0; i < 32; i += 16)
    {
        for (size_t j = 0; j < 16; j++)
        {
            tem[j] = beforeEnc[i + j];
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