#include <stdio.h>
#include <stdlib.h>
#include "math.h"



int main()
{
    int num1,num2,temp,a,b,LCM;
    printf("Enter the first number: ");
    scanf("%d", &num1);
    a=num1;
    printf("Enter the second number: ");
    scanf("%d", &num2);
    b=num2;
    while(num2!=0)
    {
        temp = num2;
        num2 = num1%num2;
        num1 = temp;
    }
    LCM = (a*b)/num1;
    printf("the LCM for the two numbers is %d",LCM);
    return 0;
}
