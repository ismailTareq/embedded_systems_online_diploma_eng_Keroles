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
    n--;
    printf("after deleting\n");
    for(i = 0; i < n; i++)
        printf("%d\t",arr1[i]);
    return 0;
}
