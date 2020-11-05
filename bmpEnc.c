//��������ͼ����˾���
#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"
#include "SM4.H"
int main()
{
    //�ļ�ָ��
    FILE *fp = NULL;
    //���ڴ洢imread�Ľ��
    size_t result;
    //SM4������ϵ
    sm4_context ctx;
    //��ʵ�������Ĵ�С
    int num;
    //�Ƿ���Ҫ������ʵͼ�����  Ĭ��Ϊ0 ����������ͼ�����
    int flag = 0;
    //����ͼ��ʱ�Ƿ���μ���  Ĭ��Ϊ0 �����ö��μ���
    int state = 0;
    //������������ĳ���
    int length_whole;
    //��Ҫ��ȫ�ķ�������ĳ���
    int length_extra;
    //bmpͼ��Ŀ�� �߶�
    int bmpWidth, bmpHeight;
    //��ʵ���ݾ���ĸ߶� ���
    int materixHeight, materixWidth;
    //��ʵ���ݾ���
    int *matrix = NULL;
    //ͼ��ͷָ��
    unsigned char *imageBmpHead;
    //ͼ���ȡָ��
    unsigned char *imageBin;
    //�洢��ʵͼ�����ݵ�ָ��
    unsigned char *realImageData = NULL;
    //���ܺ��ʮ����������
    unsigned char *afterEnc;
    //16���ȵ�ʮ����������
    unsigned char tem[16];
    //���ܵõ���ʮ����������
    unsigned char Enc[16];
    //��Կ
    unsigned char key[16] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef, 0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10};
    //��֪��Ϊʲô�����ڵ�������
    unsigned char end[2] = {0x00, 0x00};

    //��ͼƬ��������ʵ����
    fp = fopen("image\\lena.bmp", "rb");
    if (fp == NULL)
    {
        printf("file open failed\r\n");
        return -1;
    }
    bmpWidth = getBmpWidth(fp);
    bmpHeight = getBmpHeight(fp);
    materixHeight = bmpHeight;
    materixWidth = bmpWidth * 3;
    while (materixWidth % 4 != 0)
    {
        //�ܽ���˵����Ҫ������ʵ����
        flag = 1;
        materixWidth++;
    }
    //������ʵ���ݶ�Ӧ����
    if (flag == 1)
    {
        matrix = (int *)malloc(sizeof(int) * materixHeight * materixWidth);
        for (int i = 0; i < materixHeight; i++)
        {
            for (int j = 0; j < materixWidth; j++)
            {
                if (j < bmpWidth * 3)
                {
                    matrix[i * materixWidth + j] = 1;
                }
                else
                {
                    matrix[i * materixWidth + j] = 0;
                }
            }
        }
    }

    //���ļ�ͷ����ռ�
    fseek(fp, 0, SEEK_SET);
    imageBmpHead = (unsigned char *)malloc(sizeof(unsigned char) * 54);
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

    //��ͼ�����ݷ���ռ�
    imageBin = (unsigned char *)malloc(sizeof(unsigned char) * materixHeight * materixWidth);
    if (imageBin == NULL)
    {
        printf("imageBin malloc failed");
        return -1;
    }
    //�洢ͼ������
    fseek(fp, 54, SEEK_SET);
    result = fread(imageBin, 1, materixHeight * materixWidth, fp);
    if (result != materixHeight * materixWidth)
    {
        printf("file read failed");
        return -1;
    }
    else
    {
        printf("ImageSize:%d\n", result);
    }

    //Ϊ��ʵ���ݷ���ռ�
    realImageData = (unsigned char *)malloc(sizeof(unsigned char) * bmpHeight * bmpWidth * 3);
    //����ʵ���ݴ洢���ռ�

    if (flag == 1) //����ͼ�����
    {
        num = 0; //
        for (int i = 0; i < materixHeight * materixWidth; i++)
        {
            if (matrix[i] == 1)
            {

                realImageData[num] = imageBin[i];
                num++;
            }
        }
    }
    else //�����ͼ�����ݾ�����ʵ����
    {
        num = 0; //
        for (int i = 0; i < materixHeight * materixWidth; i++)
        {
            realImageData[num] = imageBin[i];
            num++;
        }
    }
    /* printf("realImageData:\n");
    for (size_t i = 0; i < num; i++)
    {
        printf("%02X  ", realImageData[i]);
    }
    printf("\n"); */

    //�����ݽ��м���
    //Ϊ���ܺ�����ݷ���ռ�
    afterEnc = (unsigned char *)malloc(sizeof(unsigned char) * bmpHeight * bmpWidth * 3);
    sm4_setkey_enc(&ctx, key); //������Կ
    //�ж��Ƿ���Ҫ���μ���
    if ((bmpHeight * bmpWidth * 3) % 16 != 0) //4px*4pxͼ����48�� unsigned char ��Ӧstate=0
    {
        state = 1;
    }
    if (state == 1) //��Ҫ���μ���
    {
        for (int i = 0;; i += 16)
        {
            if (i + 16 >= bmpHeight * bmpWidth * 3)
            {
                length_whole = i; //���±�Ϊ׼���м���
                break;
            }
            for (int j = 0; j < 16; j++)
            {
                tem[j] = realImageData[i + j];
            //    printf("%02X  ",tem[j]);
            }
            //printf("\n");
            sm4_crypt_ecb(&ctx, 1, 16, tem, Enc); //��16Ϊһ����м���
            for (int k = 0; k < 16; k++)
            {
                afterEnc[i + k] = Enc[k];
            //    printf("%02X  ",afterEnc[i+k]);
            }
            //printf("\n");
        }
        //���ж��ⲿ�ֵļ���
        printf("extraMingwen:\n");
        for (int i = bmpHeight * bmpWidth * 3 - 16; i < length_whole; i++)
        {
            tem[i - bmpHeight * bmpWidth * 3 + 16] = afterEnc[i];
        }
        for (int j = length_whole; j < bmpHeight * bmpWidth * 3; j++)
        {
            tem[j - bmpHeight * bmpWidth * 3 + 16] = realImageData[j];
        }
       /*  for (size_t i = 0; i < 16; i++)
        {
            printf("%02X  ", tem[i]);
        }
        printf("\n"); */
        sm4_crypt_ecb(&ctx, 1, 16, tem, Enc); //��16Ϊһ����м���
        printf("AfterEnc extraMingwen:\n");
        for (int i = bmpHeight * bmpWidth * 3 - 16; i < bmpHeight * bmpWidth * 3; i++)
        {
            afterEnc[i] = Enc[i - bmpHeight * bmpWidth * 3 + 16];
        //    printf("%02X  ",Enc[i - bmpHeight * bmpWidth * 3 + 16]);
        }
        //printf("\n");
    }
    else //ֱ�ӽ��м���
    {
        for (int i = 0; i < bmpHeight * bmpWidth * 3; i += 16)
        {
            for (int j = 0; j < 16; j++)
            {
                tem[j] = realImageData[i + j];
            //    printf("%02X  ",tem[j]);
            }
            //printf("\n");
            sm4_crypt_ecb(&ctx, 1, 16, tem, Enc); //��16Ϊһ����м���
            for (int k = 0; k < 16; k++)
            {
                afterEnc[i + k] = Enc[k];
            //    printf("%02X  ",Enc[k]);
            }
            //printf("\n");
        }
    }
    //�����ܺ�����ݷ��ص�ͼƬ��
    //�ж��Ƿ���������ʵ���ݾ���
    if (flag == 1) //��������ʵ����
    {
        num = 0; //
        for (int i = 0; i < materixHeight * materixWidth; i++)
        {
            if (matrix[i] == 1)
            {
                imageBin[i] = afterEnc[num];
            //    printf("%02X  ", afterEnc[num]);
                num++;
            }
        }
    }
    else //�޷��ν�
    {
        num = 0; //
        for (int i = 0; i < materixHeight * materixWidth; i++)
        {
            imageBin[num] = afterEnc[i];
            num++;
        }
    }

    fp = fopen("image\\afterEncImage.bmp", "wb");
    if (fp == 0)
    {
        return -1;
    }
    fwrite(imageBmpHead, 1, 54, fp);
    fwrite(imageBin, 1, materixHeight * materixWidth, fp);
    fwrite(end, 1, 2, fp);
    fclose(fp);
    free(imageBin);
    free(imageBmpHead);
    free(realImageData);
    free(afterEnc);
    return 0;
}