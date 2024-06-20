#include <stdio.h>
#include <stdlib.h>
#include "math.h"



int main()
{
    int num,num1,i,flag;
    printf("Please give first number: ");
    scanf("%d",&num);
    printf("Please give second number: ");
    scanf("%d",&num1);
    while(num<=num1)
    {
        flag = 0;
        for(i=2;i<=(num/2);i++)
        {
            if(num%i==0)
            {
                flag =1;
                break;
            }
        }
        if(flag == 0)
            printf("%d\n",num);
        num++;
    }
    return 0;
}
