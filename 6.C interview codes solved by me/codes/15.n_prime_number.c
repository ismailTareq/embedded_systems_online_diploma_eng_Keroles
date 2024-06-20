#include <stdio.h>
#include <stdlib.h>
#include "math.h"



int main()
{
    int num,i,temp=1,flag;
    printf("Please give input a number: ");
    scanf("%d",&num);
    printf("Prime numbers Upto %d are \n",num);

    while(temp<=num)
    {
        flag = 0;
        for(i=2;i<=(temp/2);i++)
        {
            if(temp%i==0)
            {
                flag =1;
                break;
            }
        }
        if(flag == 0)
            printf("%d\n",temp);
        temp++;
    }
    return 0;
}
