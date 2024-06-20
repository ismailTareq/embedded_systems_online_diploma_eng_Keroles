#include <stdio.h>
#include <stdlib.h>
#include "math.h"



int main()
{
    int num1,num2,temp;
    printf("Enter the first number: ");
    scanf("%d", &num1);
    printf("Enter the second number: ");
    scanf("%d", &num2);
    while(num2!=0)
    {
        temp = num2;
        num2 = num1%num2;
        num1 = temp;
    }
    printf("the GCD/HCF for the two numbers is %d",num1);
    return 0;
}
