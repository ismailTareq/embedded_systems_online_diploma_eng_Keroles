#include<stdio.h>

void main()
{
    int number;

    float temp, sqrt;

    printf("Enter an integer number: \n");
    fflush (stdout);
    scanf("%d", &number);

    sqrt = number / 2;
    temp = 0;

    while(sqrt != temp){

        temp = sqrt;

        sqrt = ( number/temp + temp) / 2;
    }

    printf("The square root of '%d' is '%0.3f'", number, sqrt);
}
