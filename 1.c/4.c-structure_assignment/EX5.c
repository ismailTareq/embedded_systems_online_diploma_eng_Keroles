#include <stdio.h>
#include <stdlib.h>
#define PI 3.1415
#define AREA(r)  (PI*r*r)
int main()
{
    int radius;
    float area;
    scanf("%d",&radius);
    area = AREA(radius);
    printf("area=%.2f",area);
    return 0;
}
