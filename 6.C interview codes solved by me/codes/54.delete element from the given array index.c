#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "math.h"
#include <ctype.h>



int main()
{
    int n, i,j, index;
    printf("Enter number of Elements in an array \n");
    scanf("%d", &n);
    int arr1[n];
    printf("Enter elements to first array \n");
    for(i = 0; i < n; i++)
        scanf("%d", &arr1[i]);
    printf("Enter index to delete\n");
    scanf("%d",&index);
    for(i = index; i <n-1; i++)
    {
        arr1[i]=arr1[i+1];
    }
    n--;
    printf("after deleting\n");
    for(i = 0; i < n; i++)
        printf("%d\t",arr1[i]);
    return 0;
}
