#include <stdio.h>
#include "string.h"
#include <stdlib.h>
void lower_to_upper(char *s1)
{
   int i;
   for(i=0; s1[i]!='\0'; i++)
   {
       if(s1[i]>='a' && s1[i]<='z')    
      s1[i]=s1[i]-32;          
   }
}
int main()
{
    char s1[30];
    printf("enter s1:");
    gets(s1);
   printf("str before converting is %s\n",s1);
   lower_to_upper(s1);
      printf("str after converting is %s\n",s1);

	return 0;
}

