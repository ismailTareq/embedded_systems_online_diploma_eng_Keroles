#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "math.h"
#include <ctype.h>
int main() {
   char str[100];
   int i,j,k;
   printf("Please Enter a String :  ");
   gets(str);
   int len = strlen(str);
   for (i = 0;i<len ;i++)
   {
       for(j=i+1;j<len;j++)
       {
           if(str[i]==str[j])
           {
               for(k=j;k<len;k++)
               {
                   str[k]=str[k+1];
               }
               len--;
               j--;
           }
       }
   }
   printf("String after removing duplicate values = %s",str);
   return 0;
}
