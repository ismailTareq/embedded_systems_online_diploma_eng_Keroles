#include <stdio.h>
#include <stdlib.h>

int main()
{
    int num,i=1,factorial=1;
    printf("enter a integer: ");
    scanf("%d",&num);
    while(i<=num)
    {
        factorial*=i;
        i++;
    }
    printf("factorial = %d",factorial);
    return 0;
}
