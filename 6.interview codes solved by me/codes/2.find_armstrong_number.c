#include <stdio.h>
#include <stdlib.h>
#include "math.h"
int main()
{
    unsigned int num,power=0,temp1,temp2,res=0,base;
    printf("enter the number:");
	scanf("%d",&num);
	temp1 = temp2 = num;
	while(num!=0)
    {
        num = num/10;
        power++;
    }
    while(temp1!=0)
    {
        base = temp1%10;
        res = res + pow(base,power);
        temp1 = temp1/10;
    }
    printf("%d\n",temp2);
    printf("%d\n",res);
    if(temp2==res)
        printf("armstrong babbbyyyyyyy");
    else
        printf("not armstrong ");
    return 0;
}
