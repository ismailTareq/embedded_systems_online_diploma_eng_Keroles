#include <stdio.h>
#include <stdlib.h>

void *memset(void *str,int ch,int n)
{
    unsigned char *s = str;
    unsigned char *v = (unsigned char)ch;
    for(int i =0;i<n;i++)
    {
        s[i] = ch;
    }
    return (void *)str;
}


int main()
{
    char src[50] = "newstring";
    memset(src,'$',3);
    puts(src);
    return 0;
}
