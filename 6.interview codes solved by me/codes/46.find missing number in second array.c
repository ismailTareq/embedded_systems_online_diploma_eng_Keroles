#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "math.h"
#include <ctype.h>



int main()
{
    int n, i,j, sum=0;
    printf("Enter number of Elements in an array \n");
    scanf("%d", &n);
    int arr1[n],arr2[n];
    printf("Enter elements to first array \n");
    for(i = 0; i < n; i++)
        scanf("%d", &arr1[i]);
    printf("Enter elements to second array \n");
    for(j = 0; j < n; j++)
        scanf("%d", &arr2[j]);
    for(i = 0; i < n; i++)
    {
        sum = sum +arr1[i]-arr2[i];
    }
    printf("missing element is %d ",sum);
    return 0;
}
