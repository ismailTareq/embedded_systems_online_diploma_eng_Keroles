#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {

    char *s,*token;
    //int i,len;
    s = (char *)malloc(1024 * sizeof(char));
    scanf("%[^\n]", s);

    s = (char *)realloc(s, strlen(s) + 1);
   //len = strlen(s);
    token = strtok(s," ");
    while(token != NULL)
    {
        printf("%s\n",token);
        token = strtok(NULL, " ");
    }
    /*for(i=0;i<len;i++)
    {
        if(s[i] == ' ')
        {
            printf("\n");
        }
        else {
        printf("%c",s[i]);
        }
    }*/
    return 0;
}
