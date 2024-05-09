#include <stdio.h>
#include <stdlib.h>

int main()
{
    int num1;
    printf("enter a numbers: ");
    scanf("%d",&num1);
    if(num1<=0)
    {
        if(num1==0)
            printf("u entered zero");
        else
            printf("%d is negative",num1);
    }
    else
        printf("%d is postive",num1);
    return 0;
}
