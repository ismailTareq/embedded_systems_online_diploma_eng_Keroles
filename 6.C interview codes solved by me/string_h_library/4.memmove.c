#include <stdio.h>
#include <stdlib.h>

void *memmove(void *dest,const void *src,int n)
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
    const char src[50] = "newstring";
    char dest[50] = "oldstring";
    printf("before memcpy dest = %s src = %s\n", dest,src);
    memmove(dest, src, sizeof(src));
    printf("After memcpy dest = %s src = %s\n", dest,src);
    return 0;
}
