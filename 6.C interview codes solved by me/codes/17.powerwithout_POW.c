#include <stdio.h>
#include <stdlib.h>
#include "math.h"



int main()
{
    int base,exp,result=1;
    printf("base ");
    scanf("%d",&base);
    printf("exp ");
    scanf("%d",&exp);
    printf("%d ^ %d is equal",base,exp);
    while(exp!=0)
    {
        result = base * result;
        exp--;
    }
    printf("%d",result);
    return 0;
}
