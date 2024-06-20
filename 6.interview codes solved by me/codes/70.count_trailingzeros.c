#include <stdio.h>
#include "string.h"
#include <stdlib.h>
int count_trailingzeros(int num)
{
int i,count=0;
for(i=0; i<32; i++)
{
    if((num>>i) &1)
    {
        break;
    }
    else
        count++;
}
return count;

}
int main()
{
int num;
printf("enter num:");
scanf("%d",&num);
int ret=count_trailingzeros(num);
printf("number of trailing zeros is %d",ret);
    return 0;
}
