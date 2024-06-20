#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "math.h"

int main()
{
    char str[100];
    int len=0,i,vowels=0,consonsant=0;
    printf("Please enter a string: ");
    gets(str);
    len = strlen(str);
    for(i=0;i<len;i++)
    {
        if(str[i]=='a'||str[i]=='e'||str[i]=='i'||str[i]=='o'||str[i]=='u'||str[i]=='A'||str[i]=='E'||str[i]=='I'||str[i]=='O'||str[i]=='U')
        {
            str[i] = '_';
            break;
        }
    }
    printf("%s",str);
    return 0;
}
