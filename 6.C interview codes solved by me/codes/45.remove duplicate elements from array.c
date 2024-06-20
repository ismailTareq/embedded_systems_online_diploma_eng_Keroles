#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "math.h"
#include <ctype.h>



int main()
{
    int n, i,j, sum;
    printf("Enter number of Elements in an array \n");
    scanf("%d", &n);
    int arr[n],array[100]={0};

    printf("Enter elements to array \n");
    for(i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    for(i=0;i<n;i++)
    {
        array[arr[i]]++;
        if(array[arr[i]]==1)
        {
            printf("after removing %d \n",arr[i]);
        }
    }
    return 0;
}
