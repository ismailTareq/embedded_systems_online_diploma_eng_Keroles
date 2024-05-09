#include <stdio.h>
#include <stdlib.h>

int main()
{
    char ch[50];
    int count=0;
    printf("enter the string: ");
    gets(ch);
    while(ch[count]!='\0')
    {
        count++;
    }
    printf("the length of string is %d",count);
    return 0;
}
