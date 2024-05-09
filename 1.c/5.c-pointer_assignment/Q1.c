#include <stdio.h>
#include <stdlib.h>

int main()
{
    int m = 29;
    printf("Address of m : %x\n", &m);
    printf("Value of m : %d\n", m);
    int* ab = &m;
    printf("\n");
    printf("Now ab is assigned with the address of m.\n");
    printf("Address of pointer ab : %x\n", ab);
    printf("Content of pointer ab : %d\n", *ab);
    printf("\n");
    *ab = 34;
    printf("The value of m assigned to %d now\n", m);
    printf("Address of pointer ab : %x\n", ab);
    printf("Content of pointer ab : %d\n", *ab);
    printf("\n");
    *ab = 7;
    printf("The pointer variable ab is assigned with the %d value now.\n", m);
    printf("Address of m  : %x\n", &m);
    printf("Value of m : %d\n", m);
    return 0;
}
