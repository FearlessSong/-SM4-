/* 
//�ܺ���
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
    unsigned int imageSize;       //ͼƬ�ֽ���
    char *imageBmpHead;           //ͼ���ļ�ͷָ��
    char *imageBin;               //ͼ���ȡָ��
    char *imageBase64;            //ͼ�����ָ��
    char *imageOutput;            //ͼ�����ָ��
    unsigned char key[16] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef, 0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10};
    size_t result;                //
    unsigned int base64StrLength; //����󳤶�
    char *strhex;                 //ת����16����
    int i;                        //���ڴ洢�ַ�
    //����ǰ��ʮ����������
    unsigned char *beforeEnc;
    //���ܺ��ʮ����������
    unsigned char *afterEnc;
    //16���ȵ�ʮ����������
    unsigned char tem[16];
    //���ܵõ���ʮ����������
    unsigned char Enc[16];
    //��ȡ������ͼƬ��rb��ʾ�Զ����ƴ�
    fp = fopen("image\\greatwall2px4px.bmp", "rb");
    if (fp == NULL)
    {
        printf("file open failed");
        return -1;
    }

    //�ɹ���ȡ֮���ȡͼƬ��С
    fseek(fp, 0L, SEEK_END);
    imageSize = ftell(fp) - 54;
    fseek(fp, 0L, SEEK_SET);

    //���ļ�ͷ����ռ�
    imageBmpHead = (char *)malloc(sizeof(char) * 54);
    if (imageBmpHead == NULL)
    {
        printf("imageBmpHead malloc failed");
        return -1;
    }
    //��ȡ�ļ�ͷ
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
    //��ͼ�����ݷ���ռ�
    imageBin = (char *)malloc(sizeof(char) * imageSize);
    if (imageBin == NULL)
    {
        printf("imageBin malloc failed");
        return -1;
    }
    //�洢ͼ������
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

    //����������ת��Ϊ16�����ַ���
    Hex2Str(imageBin, strhex, imageSize);
    strhex[imageSize * 2] = '\0';
    //��16�����ַ���ת��Ϊ�ַ�����
    printf("Output:%s \n", strhex);
    printf("OutputSize:%d\n", strlen(strhex));
    beforeEnc=malloc(sizeof(unsigned char)*imageSize);
    StringToHex(strhex,beforeEnc);
    
    //��ʮ�������������
    printf("\n");
    sm4_setkey_enc(&ctx, key); //������Կ
    for (size_t i = 0; i < 32; i += 16)
    {
        for (size_t j = 0; j < 16; j++)
        {
            tem[j] = beforeEnc[i + j];
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