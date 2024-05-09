#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct employer{
    char name[20];
    int id
};
int main()
{
    struct employer emp1 ={"alex",12};
    struct employer emp2 ={"aya",13};
    struct employer emp3 ={"mina",14};

    struct employer *arr[3] = {&emp1,&emp2,&emp3};
    struct employer (*(*ptr)[3]) = arr;
    printf("the first Employee name : %s\n",(**ptr)->name);
	printf("the first Employee ID : %d\n",(**ptr)->id);
	printf("the second Employee name : %s\n",(*(*ptr+1))->name);
	printf("the second Employee ID : %d\n",(*(*ptr+1))->id);
	printf("the third Employee name : %s\n",(*(*ptr+2))->name);
	printf("the third Employee ID : %d\n",(*(*ptr+2))->id);
    return 0;
}


