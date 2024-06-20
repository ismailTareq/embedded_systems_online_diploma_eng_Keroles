#include <stdio.h>
#include "string.h"
#include <stdlib.h>
 int max_zeros(unsigned int num)
{
int max=0,zeros=0;
unsigned int mask=1;
while(num)
{
    if((num&mask)==0)
        zeros++;
    else
    {
        if(zeros>max)
        {
            max=zeros;
            zeros=0;
        }
    }
    num>>=1;
}
return max;
}
int main()
{
    printf("%d",max_zeros(22));
    return 0;
}
