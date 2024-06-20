#include <stdio.h>
#include <stdlib.h>
#include "math.h"

int main()
{
    int num1,num2;
    printf("Please enter a number :");
    scanf("%d %d",&num1,&num2);
    printf("before swapping num1 = %d and num2 = %d",num1,num2);
    num1 = num1 - num2;
    num2 = num1 + num2;
    num1 = num2 - num1;
    printf("\nafter swapping num1 = %d and num2 = %d",num1,num2);
    return 0;
}
