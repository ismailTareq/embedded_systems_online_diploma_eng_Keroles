#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    int count,i;
    char arr [100] ;
    printf("Input the number of elements: ");
    scanf("%d", &count);
    char *ptr = arr;

    for (i = 0; i < count; i++)
    {
        printf("element %d: ",i+1);
        scanf("%d",(ptr+i));
    }
    printf("\n");
    printf("The elements of array in reverse");
    for (i=count-1; i>=0; i--)
    {
        printf("elements are : %d \n",*(ptr+i));
    }
    return 0;
}


