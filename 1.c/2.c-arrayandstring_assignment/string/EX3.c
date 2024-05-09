#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    char ch[50],reverse;
    int i,j;
    printf("enter the  string :");
    gets(ch);

    i=0;
    j=strlen(ch)-1;
    while(i<j)
    {
        reverse = ch[i];
        ch[i] =ch[j];
        ch[j]= reverse;
        i++;
        j--;
    }

    printf("reverse string is %s",ch);
    return 0;
}
