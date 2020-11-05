#include <stdio.h>
#include <stdlib.h>
#include "SM4.H"
int main()
{
  FILE *fp;
  int i;
  sm4_context ctx;
  size_t result;
  unsigned char hexInput[32];
  unsigned char output[16];
  //25  1F  21  2E  44  A0  42  EF  74  17  14  43  3E  5E  AF  BA
  unsigned char input[16] = {0x25, 0x1F, 0x21, 0x2E, 0x44, 0xA0, 0x42, 0xEF, 0x74, 0x17, 0x14, 0x43, 0x3E, 0x5E, 0xAF, 0xBA};
  unsigned char key[16] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef, 0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10};
  sm4_setkey_dec(&ctx, key);
  sm4_crypt_ecb(&ctx, 0, 16, input, output);
  for (i = 0; i < 16; i++)
  {
    printf("%02x ", output[i]);
  } 
  system("pause");
  return 0;
}
