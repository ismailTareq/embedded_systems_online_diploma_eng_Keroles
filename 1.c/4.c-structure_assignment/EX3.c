#include <stdio.h>
#include <stdlib.h>
struct complex{
    float real;
    float imag;
}num1,num2,res;
struct complex Addcomplex(struct complex n1,struct complex n2)
{
    struct complex result;
    result.real = n1.real+n2.real;
    result.imag = n1.imag+n2.imag;
    return result;
}
int main()
{
    printf("for 1st complex number:\n");
    printf("enter real: ");
    fflush(stdin);fflush(stdout);
    scanf("%f",&num1.real);
    printf("enter imaginary: ");
    fflush(stdin);fflush(stdout);
    scanf("%f",&num1.imag);
    printf("for 2nd complex number:\n");
    printf("enter real: ");
    fflush(stdin);fflush(stdout);
    scanf("%f",&num2.real);
    printf("enter imaginary: ");
    fflush(stdin);fflush(stdout);
    scanf("%f",&num2.imag);

    res = Addcomplex(num1,num2);

    printf("Sum=%.1f+%.1fi",res.real,res.imag);
    return 0;
}
