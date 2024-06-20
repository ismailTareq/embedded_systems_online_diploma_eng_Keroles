#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#define SIZE 10
// we could use int directly
typedef int uint8;
uint8 value, counter;

//prototypes of the project
bool SDB_IsFull(void);
uint8 SDB_GetUsedSize(void);
bool SDB_AddEntry(uint8 , uint8 , uint8* , uint8* );
bool addstudent();
void deletestudent();
bool readstudent();
void SDB_GetIdlist();
bool SDB_IsIdExist();


 struct simpleDb {
     int student_ID;
     int student_year;
     struct subjects {
         int course_1_ID;
         int course_2_ID;
         int course_3_ID;
         }subject;
         struct Grades {
             int course_1_Grade;
             int course_2_Grade;
             int course_3_Grade;
             }grade;
};


int main ()
{
    remove("information.txt");
    SDB_GetUsedSize();//checking if the entered number less than 10
    int x;

    while(1)
    {
        printf("\t\t\t\t=======1. Add an Entry=======\t\t\t\t\n");
        printf("\t\t\t\t=======2. Delete an Entry=======\t\t\t\t\n");
        printf("\t\t\t\t=======3. Search an Entry=======\t\t\t\t\n");
        printf("\t\t\t\t=======4. Get IDs List=======\t\t\t\t\n");
        printf("\t\t\t\t=======5. Check the ID exist:=======\t\t\t\t \n");
        printf("\t\t\t\t=======6. Exit=======\t\t\t\t\n");
        printf("\t\t\t\t_____________________________________________\t\t\t\t\n");
        printf("\t\t\t\t******what would u like to do sir :******\n");
        scanf("%d",&x);
        switch (x)
        {
        case 1:
               //instead of bool SDB_AddEntry( student.student_ID, .....)
             if (counter <= value)
             {
                addstudent();

            break;
             }
             else
             {
                printf("\nThe Entry is Full\n");
                break;
             }

        case 2:
            deletestudent();

            break;

        case 3:

            readstudent();

            break;

        case 4:

            SDB_GetIdlist();

            break;

        case 5:
            SDB_IsIdExist();
            break;
        case 6:
	          printf("\n\t\t\t\t*********thank u so much for using me have a lovely day.*********\n\n");
	          exit(0);
        }
    }
}


//this is the size of the entries
uint8 SDB_GetUsedSize()
{
    int i;

    for (;;)
    {
        printf("\t\t\t\t*******how many entries u would like to enter:*******\t\t\t\t\t ");
        scanf("%d",&value);
        if (value<=SIZE)
            return value;
        else
        {
            printf("\t\t\t\t*******sorry mate the u can't exceed 10 try smaller number,please t\t\n");
            printf("\n\t\t\t__________________________________________\n");
            continue;
        }

    }
}

//here checking if it's full or not to proceed the project
bool SDB_IsFull(void)
{
    if (counter == value)
        return 1; //or true
    else
        return 0; //or false
}

// adding the new entries

bool addstudent()
{
     char another;
     FILE *fp;
     int n;
     int i;
     struct simpleDb student;
     for (;;)
        {
            if (counter < value)
            {
                printf("\t\t\t\t=======Add Students Info=======\n\n\n");
                fp=fopen("information.txt","a"); // creating an new full
                printf("\n\t\t\tEnter Student ID    : ");
                scanf("%d",&student.student_ID);
                printf("\n\t\t\tEnter Year          : ");
                scanf("%d",&student.student_year);
                printf("\n\t\t\tEnter Course1       : ");
                scanf("%d",&student.subject.course_1_ID);
                printf("\n\t\t\tEnter Course1 Grade : ");
                scanf("%d",&student.grade.course_1_Grade);
                printf("\n\t\t\tEnter Course2       : ");
                scanf("%d",&student.subject.course_2_ID);
                printf("\n\t\t\tEnter Course2 Grade : ");
                scanf("%d",&student.grade.course_2_Grade);
                printf("\n\t\t\tEnter Course3       : ");
                scanf("%d",&student.subject.course_3_ID);
                printf("\n\t\t\tEnter Course3 Grade : ");             // we can use the for loop instead of all of this but i didn't know how to do it
                scanf("%d",&student.grade.course_3_Grade);
                printf("\n\t\t\t_________________________________\n");

                if(fp==NULL)
                    {
                        fprintf(stderr,"\n\t\t\treally sorry mate we can't find it.\n");
                    }
                else
                {
                    printf("\t\t\t your Record has been stored successfully\n");
                    ++counter;
                }
fwrite(&student, sizeof(struct simpleDb), 1, fp);
fclose(fp);
return counter;
}
else
{

printf("\n/t/t/t/t*********The Entry is Full*********/t/t/t/t/t\n");
break;}
   }
}

//removing an unwanted entry
void deletestudent()
{

    int student_ID;
    struct simpleDb student;
    FILE *fp, *fp1;
    int found;
    found = 0;
    printf("\t\t\t\t=========DELETE STUDENTS RECORD=========\n\n");
    fp=fopen("information.txt","r");// used "r" instead of "a" in order just to red the file
    fp1=fopen("temp.txt","w");
    printf("\t\t\t\tEnter the student ID : ");
    scanf("%d",&student_ID);
    if(fp==NULL)
        {
	         fprintf(stderr,"can't open file\n");
	         return;
        }
        while(fread(&student,sizeof(struct simpleDb),1,fp))
            {
                if(student.student_ID == student_ID){

	            found=1; // that is an update
            }
	            else
	            {
	                fwrite(&student,sizeof(struct simpleDb),1,fp1);
	            }

	        }
	    fclose(fp);
	    fclose(fp1);

	    if(!found)
            {
	          printf("\n\t\t\treally sorry mate we can't find it.\n");
	        }
	      if(found)
	      {
	          remove("information.txt");
	          rename("temp.txt","information.txt");
	          printf("\n\t\t\t\tRecord has been deleted sucssesfully \n");
	          --counter;
          }
return counter;
getch();
}
//searching for a student
bool readstudent()
{
    FILE *fp;
    struct simpleDb student;
    int student_ID,found=0;
    fp=fopen("information.txt","r");
    printf("\t\t\t\t=========SEARCH FOR STUDENT RECORD=========\n\n");
    printf("\t\t\tEnter the student ID,please : ");

    scanf("%d",&student_ID);

    while(fread(&student,sizeof(struct simpleDb),1,fp)>0)
        {

	        if(student.student_ID==student_ID)
                {
                    found=1;
            printf("\n\t\t\tStudent_ID        : %d",student.student_ID);
            printf("\n\t\t\tEnter Year          : %d ",student.student_year);
            printf("\n\t\t\tEnter Course1       : %d",student.subject.course_1_ID);
            printf("\n\t\t\tEnter Course1 Grade : %d",student.grade.course_1_Grade);
            printf("\n\t\t\tEnter Course2       : %d",student.subject.course_2_ID);
            printf("\n\t\t\tEnter Course2 Grade : %d",student.grade.course_2_Grade);
            printf("\n\t\t\tEnter Course3       : %d",student.subject.course_3_ID);
            printf("\n\t\t\tEnter Course3 Grade : %d",student.grade.course_3_Grade);
            printf("\n\t\t\t_________________________________________\n");
            return 1;
                }
	    }
	    if(!found)
            {
	       printf("\n\t\t\treally sorry mate we can't find it.\n");
	    return 0;
            }

fclose(fp);
getch();

}
//to get all the info of all students or entries
void SDB_GetIdlist()
{
    FILE *fp;
    struct simpleDb student;
    fp=fopen("information.txt","r");
    printf("\t\t\t\t=========STUDENTS RECORD=========\n\n");
    printf("No.of Entries: %d \n",counter);
    if(fp==NULL)
        {
            fprintf(stderr,"\n\t\t\treally sorry mate we can't find it.\n\n");
	        return;
	    }
	    else
	    {
	        printf("\t\t\t\tRECORDS :\n");
	        printf("\t\t\t\t________________________\n\n");
	    }
	    while(fread(&student,sizeof(struct simpleDb),1,fp)){
            printf("\n\t\t\t\t Student_ID  : %d",student.student_ID);
            printf("\n\t\t\tEnter Year          : %d ",student.student_year);
            printf("\n\t\t\tEnter Course1       : %d",student.subject.course_1_ID);
            printf("\n\t\t\tEnter Course1 Grade : %d",student.grade.course_1_Grade);
            printf("\n\t\t\tEnter Course2       : %d",student.subject.course_2_ID);
            printf("\n\t\t\tEnter Course2 Grade : %d",student.grade.course_2_Grade);
            printf("\n\t\t\tEnter Course3       : %d",student.subject.course_3_ID);
            printf("\n\t\t\tEnter Course3 Grade : %d",student.grade.course_3_Grade);
	        printf("\n\t\t\t\t ______________________________________\n");

	         }
fclose(fp);
getch();

}
//checking of this student exist so close to search for ID but it just telling if he exist or not
bool SDB_IsIdExist()
{
    FILE *fp;
    int student_ID,found=0;
    struct simpleDb student;
    fp=fopen("information.txt","r");
    printf("\t\t\t\t=========CHECK ID=========\n\n");
    printf("\t\t\t\tEnter the student ID : ");
    scanf("%d",&student_ID);
    while(fread(&student,sizeof(struct simpleDb),1,fp)>0)
        {

	        if(student.student_ID==student_ID)
	        {
                    found=1;
	        printf("STUDENT_ID %d EXIST",student_ID);
         printf("\n\t\t\t____________________________________________\n");

            return 1;
            }
	    }
	    if(!found)
            {
	       printf("\n\t\t\treally sorry mate we can't find it.\n");
	    return 0;
            }

fclose(fp);
getch();

}
