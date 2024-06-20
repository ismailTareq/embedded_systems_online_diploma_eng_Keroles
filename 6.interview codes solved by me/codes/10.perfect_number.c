#include <stdio.h>
#include <stdlib.h>
#include "math.h"

int main()
{
    int num1,i,reminder,sum=0;
    printf("Please enter a number :");
    scanf("%d",&num1);
    for(i=1;i<=num1/2;i++)
    {
        reminder = num1%i;
        if(reminder == 0)
        {
            sum = sum+i;
        }
    }
    if(sum == num1)
    {
        printf("number is perfect");
    }
    else
    {
        printf("number is not perfect");
    }

    return 0;
}
