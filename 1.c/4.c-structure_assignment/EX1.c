#include <stdio.h>
#include <stdlib.h>
struct student_t{
    char name[30];
    unsigned int roll;
    float marks;
}student;
int main()
{
    printf("enter Information of student:\n");
    printf("enter name: ");
    gets(student.name);
    printf("enter roll number: ");
    scanf("%d",&student.roll);
    printf("enter roll number: ");
    scanf("%.2f",&student.marks);
    printf("Displaying Information\n");
    printf("Name: %s\n Roll:%d\n Marks:%.2f",student.name,student.roll,student.marks);
    return 0;
}
