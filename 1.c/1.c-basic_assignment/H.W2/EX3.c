#include <stdio.h>
#include <stdlib.h>

int main()
{
    float num1,num2,num3;
    printf("enter 3 numbers: ");
    scanf("%f%f%f",&num1,&num2,&num3);
    if((num1>num2)&&(num1>num3))
        printf("biggest number is %.3f",num1);
    else if((num2>num1)&&(num2>num3))
        printf("biggest number is %.3f",num2);
    else if((num3>num1)&&(num3>num2))
        printf("biggest number is %.3f",num3);
    return 0;
}
