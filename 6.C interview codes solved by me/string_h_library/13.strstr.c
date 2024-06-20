#include <stdio.h>
#include <stdlib.h>

char *strstr(const char *str1,const char *str2)
{
    while(*str1 != '\0')
    {
        if(*str1 == *str2)
        {
            const char *temp1 = str1+1;
            const char *temp2 = str2+1;

            while(*temp2 != '\0' && *temp1 == *temp2)
            {
                temp1++;
                temp2++;
            }
            if(*temp2 == '\0')
                return (char *)str2;
        }
        str1++;
    }
    return NULL;
}


int main()
{
    char haystack[] = "TutorialsPoint";
  char needle[] = "Point";

  char *ret;

   ret = strstr(haystack, needle);

   printf("The substring is: %s\n", ret);
   return 0;
}
