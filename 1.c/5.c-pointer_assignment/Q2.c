#include <stdio.h>
#include <stdlib.h>
/*
int main()
{
    char arr[27];
    int i;
    char *p = arr;
    for(i=0;i<26;i++)
    {
        *p = 'A'+ i;
        p++;
    }
    p =arr;
    for(i=0;i<26;i++)
    {
        printf("%c \t",*p);
        p++;
    }
    return 0;
}*/
//or another code
int main()
{
    char arr[27]={  'A', 'B', 'C', 'D', 'E',
                    'F', 'G', 'H', 'I', 'J', 'K',
                    'L', 'M', 'N', 'O', 'P', 'Q',
                    'R', 'S', 'T', 'U', 'V', 'W',
                    'X', 'Y', 'Z'};
    int i;
    char *p = arr;
    for(i=0;i<26;i++)
    {
        printf("%c \t",*p);
        p++;
    }

    return 0;
}
