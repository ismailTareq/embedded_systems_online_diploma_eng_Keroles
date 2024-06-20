#include <stdio.h>
#include <stdlib.h>
#include "math.h"
int main()
{
    int num,temp,reverse=0,reminder;
    printf("enter the number:");
	scanf("%d",&num);
	temp = num;
	while(temp!=0)
    {
        reminder = temp%10;
        reverse = reverse*10 +reminder;
        temp = temp/10;
    }
    if(num == reverse)
    {
        printf("The given number is a palindrome");
    }
    else{
        printf("The given number is not a palindrome");
    }

    return 0;
}
