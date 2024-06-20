#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "math.h"
#include <ctype.h>
int main() {
   char str[100];
   int i,j;
   printf("Please Enter a String :  ");
   gets(str);
   int len = strlen(str);
   for(i=j=0; str[i]!=0; i++)
   {
       if (str[i] != ' ')
        {
            str[++j] = str[i];
        }
   }
   str[j] = '\0';
   printf("%s",str);
   return 0;
}
