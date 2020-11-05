/*
//���Զ�ȡ�ļ����ݲ����ܵĹ���
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
    //����ǰ��ʮ����������
    unsigned char *beforeEnc;
    //���ܺ��ʮ����������
    unsigned char *afterEnc;
    //16���ȵ�ʮ����������
    unsigned char tem[16];
    //���ܵõ���ʮ����������
    unsigned char Enc[16];
    //��Կ
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
    //����������ת��Ϊʮ�������ַ���
    Hex2Str(input, output, size * 2);
    output[size * 2] = '\0';
    printf("Output:%s \n", output);
    printf("OutputSize:%d\n", strlen(output));
    //��ʮ�������ַ�ת��Ϊʮ����������
    beforeEnc = malloc(sizeof(char) * size);
    afterEnc = malloc(sizeof(char) * size);
    StringToHex(output, beforeEnc);

    //��ʮ�������������
    printf("\n");
    sm4_setkey_enc(&ctx, key); //������Կ
    for (size_t i = 0; i < 32; i += 16)
    {
        for (size_t j = 0; j < 16; j++)
        {
            tem[j] = output[i + j];
        }
        sm4_crypt_ecb(&ctx, 1, 16, tem, Enc); //��16Ϊһ����м���
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