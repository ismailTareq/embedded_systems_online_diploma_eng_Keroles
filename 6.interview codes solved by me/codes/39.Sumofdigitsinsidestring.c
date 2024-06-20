#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "math.h"
#include <ctype.h>
int main() {
   char str[100];
   int i,sum=0;
   printf("Please Enter a String :  ");
   gets(str);
   int len = strlen(str);
   for (i = 0;i<len ;i++)
   {
       if(isdigit(str[i]))
       {
           sum = sum +str[i]-'0';
       }
   }
   printf("Sum of digits inside string is = %d",sum);
   return 0;
}
