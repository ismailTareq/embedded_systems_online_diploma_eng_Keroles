#include <stdio.h>
#include <stdlib.h>

void rev(void)
{
    char c;
    scanf("%c",&c);
    if(c!='\n')
    {
        rev();
        printf("%c",c);
    }
}
int main()
{
    printf("Enter the sentence: ");
    rev();
    return 0;
}


