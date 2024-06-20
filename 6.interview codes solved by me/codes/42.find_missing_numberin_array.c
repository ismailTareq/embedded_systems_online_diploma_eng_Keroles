#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "math.h"
#include <ctype.h>



int main()
{
    int i,n,sum=0,missing;
    printf("enter the size of an array : ");
    scanf("%d",&n);
    int arr[n-1];
    printf("please give value to insert in array: ");
    for(i=0;i<n-1;i++){
        scanf("%d",&arr[i]);
        sum=sum+arr[i];
    }
    missing = (n*(n+1))/2-sum;
    printf("missing number is = %d", missing);
  return 0;
}
