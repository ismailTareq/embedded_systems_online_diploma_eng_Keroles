#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "math.h"
#include <ctype.h>



int main()
{
    int size1,size2,size, i,j, temp;
    printf("Enter number of Elements in an first array \n");
    scanf("%d", &size1);
    int arr1[size1];
    printf("Enter number of Elements in an second array \n");
    scanf("%d", &size2);
    int arr2[size2];
    size = size1+size2;
    int mergedArray[size];
    printf("Enter elements to first array \n");
    for(i = 0; i < size1; i++)
        scanf("%d", &arr1[i]);
    printf("Enter elements to second array \n");
    for(i = 0; i < size2; i++)
        scanf("%d", &arr2[i]);
    for(i=0;i<size1;i++)
    {
        mergedArray[i]=arr1[i];
    }
    for(i=0,j=size1;i<size2&&j<size;i++,j++)
    {
        mergedArray[j]=arr2[i];
    }
    printf("merged\n");
    for(i = 0; i < size; i++)
        printf("%d\t",mergedArray[i]);
    return 0;
}
