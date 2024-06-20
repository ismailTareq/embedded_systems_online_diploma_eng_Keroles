#include <stdio.h>
#include "string.h"
#include <stdlib.h>
int main()
{
  int a[10],num,rem,i=0;
  printf("enter num:");
  scanf("%d",&num);
  while(num!=0)
  {
      rem=num%10;
      a[i]=rem;
      num/=10;
      i++;
  }
  printf("first digit is %d\nlast digit is %d\n",a[i-1],a[0]);
    return 0;
}
