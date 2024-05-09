#include <stdio.h>
#include <stdlib.h>

int main()
{
    float num1,num2;
    float temp;
    printf("enter two no: ");
    scanf("%f %f",&num1,&num2);
    printf("num1 = %f\t num2 = %f\n",num1,num2);
    num1 = num1-num2;
    num2 = num1+num2;
    num1 = num2-num1;
    printf("num1 = %f\t num2 = %f",num1,num2);
    return 0;
}
