#include <stdio.h>
#include <stdlib.h>

int power(int base , int pow)
{
    if(pow>0)
    {
        return (base*power(base,pow-1));
    }
    else
    {
        return 1;
    }
}
int main()
{
    int base,pow;
    printf("Enter base number: ");
    scanf("%d",&base);
    printf("Enter power number: ");
    scanf("%d",&pow);
    printf("%d ^ %d = %d",base,pow,power(base,pow));
    return 0;
}


