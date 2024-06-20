#include <stdio.h>
#include <stdlib.h>

void *memcpy(void *dest,const void *src,int n)
{
    const unsigned char *s = src;
    unsigned char *d = dest;
    for(int i =0;i<n;i++)
    {
        d[i] = s[i];
    }
    return (void *)dest;
}


int main()
{
    const char src[50] = "https://www.tutorialspoint.com";
    char dest[50];
    memcpy(dest, src, sizeof(src));
    printf("After memcpy dest = %s\n", dest);
    return 0;
}
