#include <stdio.h>
#include <stdlib.h>
#include "math.h"

int main()
{
    int num1,i;
    float average,num2,sum=0;
    printf("Please enter a value :");
    scanf("%d",&num1);
    for(i=1;i<=num1;i++)
    {
        printf("Enter the %d number: ", i);
        scanf("%f", & num2);
        sum = sum + num2;
    }
    average = sum/num1;
    printf("average number is %.2f: ", average);

    return 0;
}
