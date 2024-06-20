#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "math.h"
#include <ctype.h>



int main()
{
    int n, i,j, first_index,last_index;
    printf("Enter number of Elements in an array \n");
    scanf("%d", &n);
    int arr1[n],reverse[n];
    first_index = 0;
    last_index = n-1;
    printf("Enter elements to first array \n");
    for(i = 0; i < n; i++)
        scanf("%d", &arr1[i]);
    while(last_index!=0)
    {
        reverse[first_index] = arr1[last_index];
        first_index++;
        last_index--;
    }
    printf("Array After Reversing : \n");
    for(i = 0; i < n; i++)
        printf("%d\t",reverse[i]);
    return 0;
}
