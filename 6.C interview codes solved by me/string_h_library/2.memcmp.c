#include <stdio.h>
#include <stdlib.h>

void *memcmp(const void *str1,const void *str2,int n)
{
    const unsigned char *s1 = str1;
    const unsigned char *s2 = str2;
    int result;
    for(int i =0;i<n;i++)
    {
        if(*s1==*s2)
        {
            return 0;
        }
        else
        {
            result = (int)(*s1-*s2);
            if(result>0)
                return 1;
            else
                return -1;
        }
        s1++;
        s2++;
    }
}


int main()
{
    char str1[] = "apple";
    char str2[] = "banana";

int result = memcmp(str1, str2, sizeof(str1) - 1);  // Exclude null terminator

if (result == -1) {
  printf("str1 is less than str2\n");
} else if (result == 1) {
  printf("str1 is greater than str2\n");
} else {
  printf("str1 and str2 are equal\n");
}
    return 0;
}
