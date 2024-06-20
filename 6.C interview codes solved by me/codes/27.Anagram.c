#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "math.h"

int main()
{
    char str1[30],str2[30],temp,ch;
    int i,len1,len2,j;
    printf("enter the first string: ");
    gets(str1);
    printf("enter the first string: ");
    gets(str2);
    len1 = strlen(str1);
    len2 = strlen(str2);
    if(len1!=len2)
    {
        printf("given strings are not anagram");
        return 0;
    }
    else
    {
        for(i=0;i<len1-1;i++)
        {
            for(j=i+1;j<len1;j++)
            {
                if(str1[i]>str1[j])
                {
                    temp  = str1[i];
                    str1[i] = str1[j];
                    str1[j] = temp;
                    //printf("\n%c %c",str1[i],str1[j]);
                }
                if(str2[i]>str2[j])
                {
                    temp  = str2[i];
                    str2[i] = str2[j];
                    str2[j] = temp;
                    //printf("\n%c %c",str2[i],str2[j]);
                }
            }
        }
    }
    for(i = 0; i<len1; i++) {
        if(str1[i] != str2[i]) {
            printf("Strings are not anagram");
            return 0;
        }
    }
    printf("Given Strings are anagram");
    return 0;
}
