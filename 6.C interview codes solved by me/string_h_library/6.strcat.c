#include <stdio.h>
#include <stdlib.h>

char *strcat(char *dest,const char *src)
{
    unsigned char *d = dest;
    while(*d!='\0')
    {
        d++;
    }
    while(*src!='\0')
    {
        *d = *src;
        d++;
        src++;
    }
    *d = '\0';
    return dest;
}


int main()
{
    char destination[20] = "This is destination "; // Enough space for "Hello, world!" + null terminator
    const char source[20] = "This is source!";
    strcat(destination,source);
    printf("Combined string: %s\n", destination);
    return 0;
}
