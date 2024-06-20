#include <stdio.h>
#include "string.h"
#include <stdlib.h>
void reverse_string(char *str, int len)
{
    int i;
    char s[20];
    for(i=0; i<len; i++)
    {
        s[i]=str[len-1-i];
    }
    for(i=0; i<len; i++)
    {
        str[i]=s[i];
    }
}
int main()
{
   char str[20];
   puts("enter string");
   fgets(str,20,stdin);
   reverse_string(str,strlen(str));
   printf("str after reversing is %s",str);
    return 0;
}
