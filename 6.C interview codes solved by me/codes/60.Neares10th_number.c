#include <stdio.h>
#include "string.h"
#include <stdlib.h>
int Neares10th_number(int number)
{
    int reminder;
    reminder = number%10;
    if(reminder>=5)
        return number+(10-reminder);
    return number - reminder;

}
int main()
{
   int num;
   printf("enter your num:");
   scanf("%d",&num);
   printf("nearst 10th number is %d",Neares10th_number(num));
   return 0;
}
