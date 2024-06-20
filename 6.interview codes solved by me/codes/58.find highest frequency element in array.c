#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "math.h"
#include <ctype.h>



int main()
{
    int size, i,j, count=0,maxelement,maxcount=0;
    printf("Enter number of Elements array \n");
    scanf("%d", &size);
    int arr1[size];
    printf("Enter elements to first array \n");
    for(i = 0; i < size; i++)
        scanf("%d", &arr1[i]);
    for(i=0;i<size;i++)
    {
        count=1;
        for(j=i+1;j<size;j++)
        {
            if(arr1[i]==arr1[j])
            {
                count++;
                if(count>maxcount)
                {
                    maxelement = arr1[j];
                    maxcount = count;
                }
            }
        }
    }
        printf("Maximum Frequency Element : %d, Occurrence= %d times",maxelement,maxcount);
    return 0;
}
