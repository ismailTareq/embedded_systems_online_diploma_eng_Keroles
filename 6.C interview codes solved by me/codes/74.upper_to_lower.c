#include <stdio.h>
#include "string.h"
#include <stdlib.h>
void upper_to_lower(char *s1)
{
   int i;
   for(i=0; s1[i]!='\0'; i++)
   {
       if(s1[i]>='A' && s1[i]<='Z')
            s1[i]=s1[i]+32;
   }
}
int main()
{
    char s1[30];
    printf("enter s1:");
    gets(s1);
   printf("str before converting is %s\n",s1);
   upper_to_lower(s1);
      printf("str after converting is %s\n",s1);

	return 0;
}

