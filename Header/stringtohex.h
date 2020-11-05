//字符转换用头文件
#include <string.h>
#include <stdio.h>
#include <ctype.h>
int htoi(char s)
{
	int n = 0;
	if (tolower(s) > '9')
	{
		n = 10 + tolower(s) - 'a';
	}
	else
	{
		n = tolower(s) - '0';
	}
	return n; 
}
//二进制流变为十六进制字符串
void Hex2Str(const char *sSrc, char *sDest, int nSrcLen)
{
    int i;
    char szTmp[3];
    for (i = 0; i < nSrcLen; i++)
    {
        sprintf(szTmp, "%02X", (unsigned char)sSrc[i]);
        memcpy(&sDest[i * 2], szTmp, 2);
    }
    return;
}

//16进制字符串转化为16进制数组
void StringToHex(char *str, unsigned char *strhex) //字符转16进制
{
	int i, cnt = 0;
	int result = 0;
	int high = 0;
	int low = 0;
	printf("String To Hex:");
	while (*str != '\0')
	{
		high = htoi(*str);
		low = htoi(*(str + 1));
		result = high * 16 + low;
		strhex[cnt] = (unsigned char)(result + 0X00);
		printf("%02X",strhex[cnt]);
		str += 2; //指向下下一个字符
		cnt++;
	}
}