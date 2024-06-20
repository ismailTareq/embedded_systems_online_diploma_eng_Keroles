#include <stdio.h>
#include <stdlib.h>
#include "math.h"
int sumOfDigits(int num)
{
    static int sum =0;
    int reminder,rest;
    reminder = num%10;
    sum = sum + reminder;
    rest = num/10;
    if(rest>0)
    {
        sumOfDigits(rest);
    }
    return sum;
}
int main()
{
    int num;
    printf("Please enter a number :");
    scanf("%d",&num);
    printf("sum of digits of the number = %d ", sumOfDigits(num));
    return 0;
}
