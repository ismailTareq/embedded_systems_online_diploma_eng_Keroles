#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "math.h"
int char_occured(char str[],char ch,int length)
{
    int i,count=0;
    for(i=0;i<length;i++)
    {
        if(str[i]==ch)
        {
            count++;

        }
    }
    return count;
}

int main()
{
    char str[30],count,ch;
    printf("enter the string: ");
    gets(str);
    int len = strlen(str);
    printf("enter the character u want to know: ");
    scanf("%c",&ch);
    count=char_occured(str,ch,len);
    printf("total occurence : %d",count);
    return 0;
}
