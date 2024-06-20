#include <stdio.h>
#include <stdlib.h>

char *strcpy(const char *src,char *dest)
{

    while(*src != '\0')
    {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
    return dest;
}


int main()
{
   char src[40] = "This is tutorialspoint.com";
   char dest[100];

   strcpy(src, dest);

   printf("Final copied string : %s\n", dest);
    return 0;
}
