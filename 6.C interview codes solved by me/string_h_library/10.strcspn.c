#include <stdio.h>
#include <stdlib.h>

int strcspn(const char *str1,const char *str2)
{
    int count=0;
    while(*str1 != '\0')
    {
        if(*str1 == *str2)
        {
            return count;
        }
        count++;
        str1++;
    }
}


int main()
{
   int len;
   const char str1[] = "ABCDEF4960910";
   const char str2[] = "103";

   len = strcspn(str1, str2);

   printf("First matched character is at %d\n", len + 1);
    return 0;
}
