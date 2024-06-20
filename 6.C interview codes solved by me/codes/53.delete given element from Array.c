#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "math.h"
#include <ctype.h>



int main()
{
    int n, i,j, value;
    printf("Enter number of Elements in an array \n");
    scanf("%d", &n);
    int arr1[n];
    printf("Enter elements to first array \n");
    for(i = 0; i < n; i++)
        scanf("%d", &arr1[i]);
    printf("Enter elements to delete\n");
    scanf("%d",&value);
    for(i = 0; i < n; i++)
    {
        if(arr1[i]==value)
        {
            for(j=i;j<n-1;j++)
            {
                arr1[j]==arr1[j+1];
            }
            n--;
            i--;
        }
    }
    printf("after deleting");
    for(i = 0; i < n; i++)
        printf("%d\t",arr1[i]);
    return 0;
}
