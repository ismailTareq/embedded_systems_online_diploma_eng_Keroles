#include <stdio.h>
#include <stdlib.h>
struct distance{
    unsigned int feet;
    float inch;
};
struct distance num1,num2,sum;
int main()
{
    printf("enter Information of 1st distance:\n");
    printf("enter feet: ");
    fflush(stdin);fflush(stdout);
    scanf("%d",&num1.feet);
    printf("enter Inch: ");
    fflush(stdin);fflush(stdout);
    scanf("%.1f",&num1.inch);
    printf("enter Information of 2nd distance:\n");
    printf("enter feet: ");
    fflush(stdin);fflush(stdout);
    scanf("%d",&num2.feet);
    printf("enter Inch: ");
    fflush(stdin);fflush(stdout);
    scanf("%.1f",&num2.inch);

    sum.feet = num1.feet+num2.feet;
    sum.inch = num1.inch+num2.inch;

    if(sum.inch>12)
    {
        sum.inch=sum.inch-12.0;
        ++sum.feet;
    }

    printf("\nSum of distances = %d\'-%.1f\"",sum.feet,sum.inch);
    return 0;
}
