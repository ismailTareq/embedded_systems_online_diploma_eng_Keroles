#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "math.h"
#include <ctype.h>



int main()
{
    int i,n;
    int occur[100]={0};
    printf("enter the size of an array : ");
    scanf("%d",&n);
    int arr[n];
    printf("please give value to insert in array:");
    for(i=0;i<n;i++){
        scanf("%d",&arr[i]);
        occur[arr[i]]++;
    }
    for(i=0;i<n;i++){
        printf("%d is repeated %d times \n",i,occur[i]);
    }
    return 0;
}
