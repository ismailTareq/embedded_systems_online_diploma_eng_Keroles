#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "math.h"
#include <ctype.h>



int main()
{
    int n, i,j, temp;
    printf("Enter number of Elements in an array \n");
    scanf("%d", &n);
    int arr1[n];
    printf("Enter elements to first array \n");
    for(i = 0; i < n; i++)
        scanf("%d", &arr1[i]);
    for(j=0;j<2;j++)
    {
        temp = arr1[n-1];
        for(i = n-1; i >=0; i--)
        {
            arr1[i]=arr1[i-1];
        }
        arr1[0]=temp;
    }
    printf("two rotation\n");
    for(i = 0; i < n; i++)
        printf("%d\t",arr1[i]);
    return 0;
}