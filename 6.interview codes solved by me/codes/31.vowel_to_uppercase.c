#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "math.h"

int main()
{
    char str[100];
    int i = 0;
    printf("Please enter a string: ");
    fgets(str, 100, stdin);
    printf("String before converting vowel into upper case : \n%s", str);
    while( str[i] != '\0' )
    {
        if(str[i]=='a' ||str[i]=='e' ||str[i]=='i' ||str[i]=='o' ||str[i]=='u')
        {
            str[i] = str[i] - 32;
        }
        i++;
    }
    printf("String after converting vowel into upper case : \n%s", str);
    return 0;
}
