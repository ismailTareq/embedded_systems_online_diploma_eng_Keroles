#include <stdio.h>
#include <stdlib.h>

int strlen(const char *str)
{
    int count=0;
    while(*str != '\0')
    {
        count++;
        str++;
    }
    return count;
}


int main()
{
   int len;
   const char str1[] = "This is tutorialspoint.com";

   len = strlen(str1);

   printf("First matched character is at %d\n", len);
    return 0;
}
