#include <stdio.h>
#include <stdlib.h>
#include "math.h"



int main()
{
    int num;
    printf("Enter a number to check even or odd = ");
    scanf("%d", & num);
    if (num % 2 == 0) {
        printf("Given number %d is even", num);
    } else {
        printf("Given number %d is odd", num);
    }
}
