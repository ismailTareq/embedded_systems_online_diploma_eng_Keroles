#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "math.h"
#include <ctype.h>



int main()
{
    int n, i,j, largest,smallest;
    printf("Enter number of Elements in an array \n");
    scanf("%d", &n);
    int arr1[n];
    printf("Enter elements to first array \n");
    for(i = 0; i < n; i++)
        scanf("%d", &arr1[i]);
    largest = arr1[0];
    smallest = arr1[0];
    for(i=1;i<n;i++)
    {
        if(arr1[i]>largest)
            largest = arr1[i];
        else if(arr1[i]<smallest)
            smallest = arr1[i];
    }
    printf("%d is largest and %d is smallest",largest,smallest);
    return 0;
}
