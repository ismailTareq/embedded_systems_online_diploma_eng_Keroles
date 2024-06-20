#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "math.h"

int main()
{
    char str[100];
    int len=0,i,j;
    printf("Please enter a string: ");
    gets(str);
    len = strlen(str);
    printf("String before deleting the vowels string is : %s\n", str);
    for(i=0;i<len;i++)
    {
        if(str[i]=='a'||str[i]=='e'||str[i]=='i'||str[i]=='o'||str[i]=='u'||str[i]=='A'||str[i]=='E'||str[i]=='I'||str[i]=='O'||str[i]=='U')
        {
            for(j=i; j<len; j++)
            {
                str[j]=str[j+1];
            }
            i--;
            len--;
        }
    }
    printf("After deleting the vowels string is : %s", str);
    return 0;
}
