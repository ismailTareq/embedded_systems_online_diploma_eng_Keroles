#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    int size,i;
    char arr [100] ;
    printf("Input a string: ");
    scanf("%s", arr);
    size = strlen(arr);
    char* ptr = arr;

    for (i = size; i >= 0; i--)
    {
        printf("%c", *(ptr + i));
    }
    return 0;
}


