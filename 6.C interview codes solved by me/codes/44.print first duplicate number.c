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
    int arr[n];
    printf("Enter elements to array \n");
    for(i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    for(i=0;i<n;i++)
    {
        for(j=i+1;j<n;j++)
        {
            if(arr[i]==arr[j])
            {
                printf("first duplicate number is = %d",arr[i]);
                break;
            }
        }
        break;
    }
    return 0;
}
