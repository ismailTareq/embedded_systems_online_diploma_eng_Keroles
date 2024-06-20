#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "math.h"

int main()
{
    char ch;
    printf("Please enter a character: ");
    scanf("%c",&ch);
    if((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z'))
    {
        if(ch=='a' || ch=='A' || ch=='e' || ch=='E' || ch=='i' || ch=='I' || ch=='o' || ch=='O' || ch== 'u' || ch=='U')
            printf("Given Character %c is a vowel.\n", ch);
        else
            printf("Given Character %c is a consonant.\n", ch);
    }
    else
        printf("Given Character %c is neither a vowel nor a consonant.\n", ch);
    return 0;
}
