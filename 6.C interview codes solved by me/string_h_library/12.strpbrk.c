#include <stdio.h>
#include <stdlib.h>

char *strpbrk(const char *str1,const char *str2)
{
    while(*str1 != '\0')
    {
        const char *temp = str2;
        while(*temp != '\0')
        {
            if(*str1 == *temp)
            {
                return (char *)str1;
            }
            temp++;
        }

        str1++;
    }
    return NULL;
}


int main()
{
   char str1[] = "Hello, world!";
  char str2[] = "aeiou";

  char *found = strpbrk(str1, str2);

  if (found != NULL) {
    printf("The first vowel in the string is '%c' at position %ld\n", *found, (long int)(found - str1));
  } else {
    printf("No vowels found in the string.\n");
  }
    return 0;
}
