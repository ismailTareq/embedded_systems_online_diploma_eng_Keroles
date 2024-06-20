#include <stdio.h>
#include <stdlib.h>
#include "math.h"
int main()
{
    int num,i,result,first =0,second =1;
    printf("enter the number:");
	scanf("%d",&num);
	for(i=0;i<num;i++)
    {
        if(i<=1)
        {
            result = i;
        }
        else
        {
            result = first + second;
            first = second;
            second = result;
        }
        printf("%d \n",result);
    }
    return 0;
}
