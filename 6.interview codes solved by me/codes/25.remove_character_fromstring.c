#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "math.h"
void removechar(char str[],char ch,int length)
{
    int i,j;
    for(i=j=0;i<length;i++)
    {
        if(str[i]!=ch)
        {
            str[j++]=str[i];

        }
    }
    str[j]='\0';
}

int main()
{
    char str[30],ch;
    printf("enter the string: ");
    gets(str);
    int len = strlen(str);
    printf("enter the character u want to remove: ");
    scanf("%c",&ch);
    removechar(str,ch,len);
    printf("string after removing it : %s",str);
    return 0;
}
