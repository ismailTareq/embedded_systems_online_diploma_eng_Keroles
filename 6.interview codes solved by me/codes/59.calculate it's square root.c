#include <stdio.h>
#include "string.h"
#include <stdlib.h>
float SquareRoot(float number)
{
    float res=0;
    if(number==0 || number==1)
        return number;
    float temp, sqrt;
    sqrt = number / 2;
    temp = 0.0;
    while(sqrt != temp)
    {
        temp = sqrt;
        sqrt = ( number/temp + temp) / 2;
    }
    return sqrt;

}
int main()
{
   int number;
   printf("Provide the number: \n");
   scanf("%d", &number);
   printf("The square root of '%d' is '%.4f'", number, SquareRoot(number));
   return 0;
}
