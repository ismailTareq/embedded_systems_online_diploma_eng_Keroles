#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "math.h"
void replaceSpace(char str[],char ch,int len)
{
    for(int i =0;i<len;i++)
    {
        if(str[i]==' ')
            str[i]=ch;
    }
}
int main()
{
    char str[100],ch;
    int i,j,len;
    printf("Enter the string : ");
    gets(str);
    len = strlen(str);
    printf("Enter a char you want to replace with space : ");
    scanf("%c",&ch);
    replaceSpace(str,ch,len);
    printf("String after removing ' ' String Become: %s", str);
    return 0;
}
