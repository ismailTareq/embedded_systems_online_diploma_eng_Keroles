#include <stdio.h>
#include <stdlib.h>
struct information{
    char name[30];
    unsigned int roll;
    float marks;
}student[10];
int main()
{
    int i ;
	printf("Enter information of students: ");
	for(i=0;i<10;i++)
	{
		printf("\nFor roll number %d ",i+1);
		printf("\nEnter name: ");
		fflush(stdin);fflush(stdout);
		scanf("%s",student[i].name);
		printf("Enter marks: ");
		fflush(stdin);fflush(stdout);
		scanf("%g",&student[i].marks);
	}
	printf("\nDisplaying information of students: ");
	for(i=0;i<10;i++)
	{
		printf("\nInformationFor roll number %d ",i+1);
		printf("\nname: %s",student[i].name);
		printf("\nMarks: %.2f",student[i].marks);
	}
    return 0;
}
