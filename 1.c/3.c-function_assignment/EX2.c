#include <stdio.h>
#include <stdlib.h>

int fact(int num)
{
    if(num!=1)
    {
        return num*fact(num-1);
    }
}

int main()
{
    int num1;
    printf("Enter the numbers: ");
    scanf("%d", &num1);
    printf("the factorial of %d is %d",num1,fact(num1));
    return 0;
}


