#include <stdio.h>
#include "string.h"
#include <stdlib.h>
unsigned char reverse_bits(unsigned char num)
{
    unsigned char i,temp=0;
    for(i=0; i<8; i++)
    {
           if(num&(1<<i))
            temp|=1<<(7-i);
    }
    return temp;
}
void display_binary(unsigned char num)
{
   char i;
   for(i=7; i>=0; i--)
   {
    (num &(1<<i))?printf("1"):printf("0");

   }
}
int main()
{
  unsigned char num=149;
  printf("num in decimal is %d\n",num);
  display_binary(num);
  printf("\nafter reverse\n");
  unsigned char ret=reverse_bits(num);
  printf("reverse in decimal is %d\n",ret);
  display_binary(ret);
  return 0;
}
