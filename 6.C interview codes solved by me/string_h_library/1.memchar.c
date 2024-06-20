#include <stdio.h>
#include <stdlib.h>

void *memchar(const void *str,char c,int n)
{
    const unsigned char *s = str;
    for(int i =0;i<n;i++)
    {
        if(*s==c)
        {
            return (unsigned char *)s;
        }
        s++;
    }
    return NULL;
}


int main()
{
    char str[] = "https://www.tutorialspoint.com";
    char* found = memchar(str, 'o', sizeof(str));

    printf("String after |%c| is - |%s|\n",'.',found);
    return 0;
}
