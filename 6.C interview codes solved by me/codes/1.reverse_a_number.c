#include <stdio.h>
#include <stdlib.h>

int main()
{
    unsigned int num = 12345,reminder,reverse = 0;
    printf("before reversing : %d",num);
    while(num!=0)
    {
        reminder = num%10;
        reverse = reverse*10 + reminder;
        num = num/10;
    }
    printf("\nAfter reversing :  %d",reverse);
    return 0;
}
