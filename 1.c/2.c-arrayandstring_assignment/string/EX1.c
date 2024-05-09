#include <stdio.h>
#include <stdlib.h>

int main()
{
    char ch[50],c;
    int i,counter=0;
    printf("enter a string: ");
    gets(ch);

    printf("enter the character to find freq: ");
    scanf("%c",&c);

    for(i=0;ch[i]!='\0';i++)
    {
        if(c == ch[i])
        {
            counter++;
        }
    }
    printf("the freq of %c is %d",c,counter);
    return 0;
}
