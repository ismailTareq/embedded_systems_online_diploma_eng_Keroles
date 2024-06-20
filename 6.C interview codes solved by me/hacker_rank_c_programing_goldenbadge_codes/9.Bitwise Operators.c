#include <stdio.h>
//Complete the following function.
void bitwise(int n, int k)
{
    int i ,j;
    int and,or,xor;
    int max1 =0, max2 =0, max3 =0;
    for(i=1;i<=n;i++)
    {
        for(j=i+1;j<=n;j++)
        {
            and = i&j;
            if((and<k)&&(and>max1))
            {
                max1=and;
            }
            or=i|j;
            if((or<k)&&(or>max2))
            {
                max2=or;
            }
            xor=i^j;
            if((xor<k)&&(xor>max3))
            {
                max3=xor;
            }
        }
    }
    printf("%i \n",max1);
    printf("%i \n",max2);
    printf("%i \n",max3);
}
int main() {
    int n, k;

    scanf("%d %d", &n, &k);
    bitwise(n, k);

    return 0;
}
