#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "math.h"
#include <ctype.h>



int main()
{
    int n, i,j, value,location;
    printf("Enter number of Elements in an array \n");
    scanf("%d", &n);
    int arr1[n];
    printf("Enter elements to first array \n");
    for(i = 0; i < n; i++)
        scanf("%d", &arr1[i]);
    printf("Please give a number to insert \n");
    scanf("%d",&value);
    printf("Please enter the location to insert an new element\n");
    scanf("%d",&location);
    for(i=n-1;i>=location-1;i--)
    {
        arr1[i+1]=arr1[i];
    }
    arr1[location-1] = value;
    n++;
    printf("after inseting\n");
    for(i = 0; i < n; i++)
        printf("%d\t",arr1[i]);
    return 0;
}
