#include <stdio.h>
#include <stdlib.h>
#include "math.h"



int main()
{
    int num1,num2,reminder,binary=0,f=1;
    printf("Enter the DEC number: ");
    scanf("%d", &num1);
    while(num1!=0)
    {
        reminder = num1%2;
        binary = binary + reminder*f;
        f=f*10;
        num1 = num1 /2;
    }
    printf("%d",binary);
    return 0;
}
