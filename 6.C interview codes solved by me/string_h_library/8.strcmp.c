#include <stdio.h>
#include <stdlib.h>

int strcmp(const char *str1,const char *str2)
{
    int result;
    while(*str1 != '\0' && *str2 != '\0')
    {
        if(*str1 == *str2)
        {
            return 0;
        }
        else
        {
            result = (int)(*str1 - *str2);
            if(result > 0)
                return 1;
            else
                return -1;
        }
        str1++;
        str2++;
    }
}


int main()
{
    char str1[] = "abcdef";
    char str2[] = "ABCDEF";

int result = strcmp(str1, str2);  // Exclude null terminator

if (result == -1) {
  printf("str1 is less than str2\n");
} else if (result == 1) {
  printf("str1 is greater than str2\n");
} else {
  printf("str1 and str2 are equal\n");
}
    return 0;
}
