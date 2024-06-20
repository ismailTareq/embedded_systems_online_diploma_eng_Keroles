#include <stdio.h>
#include <stdlib.h>

char *strchr(char *str,int ch)
{
    char c = (char)ch;

    while(*str !='\0')
    {
        if(*str == c)
        {
            return (char *)str;
        }
        str++;
    }
    return NULL;
}


int main()
{
    char str[] = "https://www.tutorialspoint.com";
    char *found = strchr(str,'.');
    printf("%s\n", found);
    return 0;
}
