#include <stdio.h>
#include <stdlib.h>

int main()
{
    char c;
    printf("enter a character: ");
    scanf("%c",&c);
    (c=='a'||c=='A'||c=='e'||c=='E'||c=='i'||c=='I'||c=='o'||c=='O'||c=='u'||c=='U')?printf("vowel"):printf("consonant");
    return 0;
}
