#include <stdio.h>
#include <stdlib.h>
#include "math.h"
int main()
{
    int num,i=0,temp=0;
    printf("enter the number:");
	scanf("%d",&num);
	for(i=2;i<=(num/2);i++)
    {
        if(num % i == 0)
        {
            temp =1;
            break;
        }
    }
    if(temp==1)
    {
        printf(" number not prime");
    }

    else
    {
        printf("number is prime ");
    }

    return 0;
}
