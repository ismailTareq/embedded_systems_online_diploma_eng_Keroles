#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "math.h"
#include <ctype.h>
int main() {
   char str[100];
   int i;
   printf("Please Enter a String :  ");
   gets(str);
   int len = strlen(str);
   for(i=0; i<len; i++)
   {
       printf("%c \n",str[i]);
   }
   return 0;
}
