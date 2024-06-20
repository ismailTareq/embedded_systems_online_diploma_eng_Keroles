#include <stdio.h>
#include <stdlib.h>
#include "math.h"

int main()
{
    int num1,num2,i;
    printf("Please enter a number :");
    scanf("%d %d",&num1,&num2);
    for(i=1;i<=num2;i++)
        num1++;
    printf("sum = %d",num1);
    return 0;
}
