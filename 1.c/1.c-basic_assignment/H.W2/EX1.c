#include <stdio.h>
#include <stdlib.h>

int main()
{
    int num;
    printf("enter a no: ");
    scanf("%d",&num);
    if((num%2)==0)
        printf("even");
    else
        printf("odd");
    return 0;
}
