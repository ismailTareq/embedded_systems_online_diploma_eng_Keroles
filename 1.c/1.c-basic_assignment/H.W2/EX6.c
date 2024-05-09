#include <stdio.h>
#include <stdlib.h>

int main()
{
    int num,i=1,sum=0;
    printf("enter a integer: ");
    scanf("%d",&num);
    while(i<=num)
    {
        sum+=i;
        i++;
    }
    printf("sum = %d",sum);
    return 0;
}
