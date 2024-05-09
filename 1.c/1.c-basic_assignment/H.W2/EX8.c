#include <stdio.h>
#include <stdlib.h>

int main()
{
    char c;
    float num1,num2;
    printf("enter the operation: \n");
    scanf("%c",&c);
    printf("enter the two numbers: \n");
    scanf("%f %f",&num1,&num2);
    switch(c)
    {
        case '+':
        printf("%.2f + %.2f = %.2f",num1,num2,num1+num2);
        break;
        case '-':
        printf("%.2f - %.2f = %.2f",num1,num2,num1-num2);
        break;
        case '*':
        printf("%.2f * %.2f = %.2f",num1,num2,num1*num2);
        break;
        case '/':
        printf("%.2f + %.2f = %.2f",num1,num2,num1/num2);
        break;
        default:printf("not correct operation");break;
    }
    return 0;
}
