/*
 * Student.c
 *
 *  Created on: june 1, 2024
 *  Author: ismail tarek
 */
#include "student.h"
static FIFO_status FIFO_is_full(FIFO_buf_t* fifo);
static int check_Rollnum(FIFO_buf_t* students,int Roll_number);
static FIFO_status FIFO_is_empty(FIFO_buf_t* fifo);
FIFO_status FIFO_Init(FIFO_buf_t* fifo,element_type* buf,int length)
{
    if((NULL==buf)||(NULL==fifo))
    {
        return FIFO_null;
    }
    else
    {
        fifo->base=buf;
        fifo->head=buf;
        fifo->tail=buf;
        fifo->counter=0;
        fifo->length=length;
        return FIFO_no_error;
    }
}
static FIFO_status FIFO_is_full(FIFO_buf_t* fifo)
{
    if(fifo->counter==fifo->length)
        return FIFO_full;
    return FIFO_no_error;
}
static FIFO_status FIFO_is_empty(FIFO_buf_t* fifo)
{
    if(fifo->counter==0)
        return FIFO_empty;
    return FIFO_no_error;
}
static int check_Rollnum(FIFO_buf_t* FIFO_Buffer,int Roll_number)
{
    student_t *student_ptr= FIFO_Buffer->base;//forgot to initialize it gave me an error
    int i;
    for(i=0;i<FIFO_Buffer->counter;++i)
    {
        if(student_ptr->RollNumber == Roll_number)
        {
            return 0;
        }
        student_ptr++;
    }
    return 1;
}
void add_student_from_file(FIFO_buf_t* FIFO_Buffer)
{
    char firstName[50], lastName[50];
	int roll_num, course_id[5],line=0,i;
	float GPA;
    FILE* file_ptr = fopen("student.txt","r");
    if(FIFO_is_full(FIFO_Buffer)== FIFO_full)
    {
        DPRINTF("\t \t \t \t \tStudent List Is Full\n");
    }
    if(file_ptr == NULL)
    {
        DPRINTF("File Not Found\n");
    }
    while(fscanf(file_ptr,"%d %s %s %f %d %d %d %d %d",&roll_num,firstName, lastName,&GPA, &course_id[0], &course_id[1], &course_id[2], &course_id[3], &course_id[4] ) != EOF)
    {
        if(FIFO_is_full(FIFO_Buffer)== FIFO_full)
        {
            DPRINTF("\t \t \t \t \tStudent List Is Full\n");
        }
        if (check_Rollnum(FIFO_Buffer, roll_num) == 0)
        {
            DPRINTF("\n\t \t \t \t \t[ERROR] : In Line %d Roll_Number Is Already Taken\n",line);
            line++;
            continue;
        }
        strcpy(FIFO_Buffer->head->First_name,firstName);
        strcpy(FIFO_Buffer->head->Last_name,lastName);
        for(i=0;i<5;i++)
		{
			FIFO_Buffer->head->Course_ID[i] = course_id[i];
		}
		FIFO_Buffer->head->GPA = GPA;
		FIFO_Buffer->head->RollNumber = roll_num;
		FIFO_Buffer->counter++;
		if(FIFO_Buffer->head==FIFO_Buffer->base+(FIFO_Buffer->length * sizeof(element_type)))
        {
            FIFO_Buffer->head=FIFO_Buffer->base;
        }
        else
        {
            FIFO_Buffer->head++;
        }
		line++;
		DPRINTF("\n\t \t \t \t \t[INFO] Students Details Is Added Successfully\n");
    }
    fclose(file_ptr);
}
void add_student_Manually(FIFO_buf_t* FIFO_Buffer)
{
    DPRINTF("\t \t \t \t \t======================================\n");
    DPRINTF("\t \t \t \t \t \tAdd the student Details\n");
    DPRINTF("\t \t \t \t \t======================================\n");
    int roll_num,i;
    char temp_text[40];
    /* check if the buffer created or not */
    if((FIFO_Buffer->base == NULL)||(FIFO_Buffer->head == NULL)||(FIFO_Buffer->tail == NULL))
    {
        DPRINTF("FIFO Not Found\n");
    }
    if(FIFO_is_full(FIFO_Buffer)== FIFO_full)
    {
        DPRINTF("\t \t \t \t \tStudent List Is Full\n");
    }
    /* Check if it is already taken from another student or not */
    do {
        DPRINTF("\t \t \t \t \tAdd Roll Number: ");
        gets(temp_text);
        roll_num=atoi(temp_text);
        if (check_Rollnum(FIFO_Buffer, roll_num) == 0) {
            DPRINTF("\t \t \t \t \tRoll Number %d already exists.\n", roll_num);
            DPRINTF("\t \t \t \t \tPlease enter a unique roll number.\n");
        }
    } while (check_Rollnum(FIFO_Buffer, roll_num) == 0);
    /*store roll in struct*/
    FIFO_Buffer->head->RollNumber = atoi(temp_text);
    DPRINTF("\t \t \t \t \tEnter the first Name of Student: ");
    gets(FIFO_Buffer->head->First_name);
    DPRINTF("\t \t \t \t \tEnter the last Name of Student: ");
    gets(FIFO_Buffer->head->Last_name);
    DPRINTF("\t \t \t \t \tEnter the GPA of Student: ");
    gets(temp_text);
    FIFO_Buffer->head->GPA = atof(temp_text);
    DPRINTF("\t \t \t \t \tEnter the course ID of each course: \n");
    for(i=0;i<5;++i)
    {
        DPRINTF("\t \t \t \t \tCourse %d ID: ",i+1);
		gets(temp_text);
		FIFO_Buffer->head->Course_ID[i] = atoi(temp_text);
    }
    FIFO_Buffer->counter++;
    if(FIFO_Buffer->head==FIFO_Buffer->base+(FIFO_Buffer->length * sizeof(element_type)))
    {
        FIFO_Buffer->head=FIFO_Buffer->base;
    }
    else
    {
        FIFO_Buffer->head++;
    }
    DPRINTF("\t \t \t \t \t*************************************************\n");
    DPRINTF("\n\t \t \t \t \t[INFO] Students Details Is Added Successfully");
	DPRINTF("\n\t \t \t \t \t--------------------------------");
	DPRINTF("\n\t \t \t \t \t[INFO] The Total Number Of Students Is %d ",FIFO_Buffer->counter);
	DPRINTF("\n\t \t \t \t \t[INFO] You Can Add Up To 50 Students");
	DPRINTF("\n\t \t \t \t \t[INFO] You Still Can Add %d More Students If You Want \n",FIFO_Buffer->length-FIFO_Buffer->counter);
}
void find_roll_number(FIFO_buf_t* FIFO_Buffer)
{
    student_t *student_ptr= FIFO_Buffer->tail;
    int roll_num,i,j,flag;
    char temp_text[5];
    DPRINTF("\t \t \t \t \tEnter the roll number of the student: ");
    gets(temp_text);
    roll_num = atoi(temp_text);

    /* try to find Roll_Num through whole struct*/
    for(i=0;i<FIFO_Buffer->counter;i++)
    {
        if(student_ptr->RollNumber == roll_num)
        {
            DPRINTF("\t \t \t \t \tThe students Details are\n");
            DPRINTF("\t \t \t \t \tStudent first name  : %s\n",student_ptr->First_name);
            DPRINTF("\t \t \t \t \tStudent last  name  : %s\n",student_ptr->Last_name);
            DPRINTF("\t \t \t \t \tStudent roll  number: %d\n",student_ptr->RollNumber);
            DPRINTF("\t \t \t \t \tStudent GPA         : %0.2f\n",student_ptr->GPA);
            for(j=0;j<5;j++)
            {
                DPRINTF("\t \t \t \t \tThe course ID are: %d\n",student_ptr->Course_ID[j]);
            }
            flag = 0;
            break;//so he don't continue iterating
        }
        else
        {
            flag = 1;
        }
        student_ptr++;
    }
    if(flag == 1)
    {
        DPRINTF("\t \t \t \t \tRoll Number %d not found\n",roll_num);
    }
}
void find_first_name(FIFO_buf_t* FIFO_Buffer)
{
    student_t *student_ptr= FIFO_Buffer->tail;
    int i,j,flag;
    char temp_text[20];
    DPRINTF("\t \t \t \t \tEnter the student First Name: ");
    gets(temp_text);
    /* try to find name of the student through whole struct*/
    for(i=0;i<FIFO_Buffer->counter;i++)
    {
        if(strcmp(student_ptr->First_name,temp_text)==0)
        {
            DPRINTF("\t \t \t \t \tThe students Details are\n");
            DPRINTF("\t \t \t \t \tStudent first name  : %s\n",student_ptr->First_name);
            DPRINTF("\t \t \t \t \tStudent last  name  : %s\n",student_ptr->Last_name);
            DPRINTF("\t \t \t \t \tStudent roll  number: %d\n",student_ptr->RollNumber);
            DPRINTF("\t \t \t \t \tStudent GPA         : %0.2f\n",student_ptr->GPA);
            for(j=0;j<5;j++)
            {
                DPRINTF("\t \t \t \t \tThe course ID are: %d\n",student_ptr->Course_ID[j]);
            }
            flag = 0;
            break;//so he don't continue iterating
        }
        else
        {
            flag = 1;
        }
        student_ptr++;
    }
    if(flag == 1)
    {
        DPRINTF("\t \t \t \t \t[ERROR] No Such Student Name Starts By %s\n",temp_text);
    }
}
void find_course_ID(FIFO_buf_t* FIFO_Buffer)
{
    student_t *student_ptr= FIFO_Buffer->tail;
    int i,j,course_ID,count=0;//forgot to inti it with zero
    char temp_text[20];
    DPRINTF("\t \t \t \t \tEnter the course ID: ");
    gets(temp_text);
    course_ID = atoi(temp_text);
    /* try to find name of the student through whole struct*/
    for(i=0;i<FIFO_Buffer->counter;i++)
    {
            for(j=0;j<5;j++)
            {
                if(student_ptr->Course_ID[j] == course_ID)
                {
                    count++;
                    DPRINTF("\t \t \t \t \tThe students Enrolled in this course\n");
                    DPRINTF("\t \t \t \t \tStudent first name  : %s\n",student_ptr->First_name);
                    DPRINTF("\t \t \t \t \tStudent last  name  : %s\n",student_ptr->Last_name);
                    DPRINTF("\t \t \t \t \tStudent roll  number: %d\n",student_ptr->RollNumber);
                    DPRINTF("\t \t \t \t \tStudent GPA         : %0.2f\n",student_ptr->GPA);
                }
            }
        student_ptr++;
    }
    if(count == 0)
    {
        DPRINTF("\t \t \t \t \tCourse ID %d not found\n",course_ID);
    }
    DPRINTF("\t \t \t \t \t[INFO] Total Number of Students Enrolled: %d\n",count);
}
void total_student(FIFO_buf_t* FIFO_Buffer)
{
	DPRINTF("\n\t \t \t \t \t[INFO] The total number of students is %d ",FIFO_Buffer->counter);
	DPRINTF("\n\t \t \t \t \t[INFO] you still can add %d more students if you want\n ",FIFO_Buffer->length-FIFO_Buffer->counter);
}
void delete_student(FIFO_buf_t* FIFO_Buffer)
{
    student_t *student_ptr= FIFO_Buffer->tail;
    int roll_num,i,flag;
    char temp_text[5];
    if(FIFO_is_empty(FIFO_Buffer)==FIFO_empty)
    {
        printf("\t \t \t \t \t[ERROR] There Is No Student Info Being Entered (List Is Empty)\n");
    }
    else
    {
        DPRINTF("\t \t \t \t \tEnter The Roll Number Of The Student You Want To Delete: ");
        gets(temp_text);
        roll_num = atoi(temp_text);
        for(i=0;i<FIFO_Buffer->counter;i++)
        {
            if(student_ptr->RollNumber == roll_num)
            {
                *student_ptr = *(FIFO_Buffer->tail);
                FIFO_Buffer->counter--;
                if(FIFO_Buffer->tail==FIFO_Buffer->base+(FIFO_Buffer->length * sizeof(element_type)))
                {
                    FIFO_Buffer->tail=FIFO_Buffer->base;
                }
                else
                {
                    FIFO_Buffer->tail++;
                }
                flag = 0;
                break;
            }
            else
            {
                flag = 1;
            }
            student_ptr++;
        }
        if(flag == 1){DPRINTF("\t \t \t \t \t[ERROR] This Roll Number %d Doesn't Exist\n",roll_num);}
        else{DPRINTF("\t \t \t \t \t[INFO] The Student Whose Roll Number is %d is removed successfully\n",roll_num);}
    }
}
void update_student(FIFO_buf_t* FIFO_Buffer)
{
    student_t *student_ptr= FIFO_Buffer->tail;
    int roll_num,i,j,choice;
    char temp_text[5];
    if(FIFO_is_empty(FIFO_Buffer)==FIFO_empty)
    {
        printf("\t \t \t \t \t[ERROR] There Is No Student Info Being Entered (List Is Empty)\n");
    }
    else
    {
        DPRINTF("\t \t \t \t \tEnter The Roll Number Of The Student You Want To Update: ");
        gets(temp_text);
        roll_num = atoi(temp_text);
        for(i=0;i<FIFO_Buffer->counter;i++)
        {
            if(student_ptr->RollNumber == roll_num)
            {
                DPRINTF("\t \t \t \t \t1.first name\n");
                DPRINTF("\t \t \t \t \t2.last name\n");
                DPRINTF("\t \t \t \t \t3.roll no\n");
                DPRINTF("\t \t \t \t \t4. GPA\n");
                DPRINTF("\t \t \t \t \t5. courses\n");
                DPRINTF("\t \t \t \t \tEnter What You Want To Change: ");
                gets(temp_text);
                choice = atoi(temp_text);
                switch(choice)
                {
                    case 1:
                        DPRINTF("\t \t \t \t \tEnter The New First Name of Student: ");
                        gets(student_ptr->First_name);
                    break;
                    case 2:
                        DPRINTF("\t \t \t \t \tEnter The New Last Name of Student: ");
                        gets(student_ptr->Last_name);
                    break;
                    case 3:
                        DPRINTF("\t \t \t \t \tEnter The New Roll Number: ");
                        gets(temp_text);
                        student_ptr->RollNumber=atoi(temp_text);
                    break;
                    case 4:
                        DPRINTF("\t \t \t \t \tEnter The New GPA: ");
                        gets(temp_text);
                        student_ptr->GPA=atof(temp_text);
                    break;
                    case 5:
                        DPRINTF("\t \t \t \t \tEnter The New Course ID: ");
                        for(j=0;j<5;j++)
                        {
                            DPRINTF("Course %d ID: ",j+1);
                            gets(temp_text);
                            student_ptr->Course_ID[j]=atoi(temp_text);
                        }
                    break;
                }
                break;
            }
            student_ptr++;
        }
        DPRINTF("\t \t \t \t [INFO] The Student %s %s Whose Roll_Number is %d Has Been UPDATED SUCCESSFULLY.\n",student_ptr->First_name,student_ptr->Last_name,student_ptr->RollNumber);
    }
}
void show_student(FIFO_buf_t* FIFO_Buffer)
{
    student_t *student_ptr=FIFO_Buffer->tail;
    int i,j;
    if(FIFO_is_empty(FIFO_Buffer)==FIFO_empty)
        printf("\t \t \t \t \t[ERROR] There Is No Student Info Being Entered (List Is Empty)\n");

    for(i=0;i<FIFO_Buffer->counter;i++)
    {
        DPRINTF("\t \t \t \t \tStudent roll  number: %d\n",student_ptr->RollNumber);
        DPRINTF("\t \t \t \t \tStudent first name  : %s\n",student_ptr->First_name);
		DPRINTF("\t \t \t \t \tStudent last  name  : %s\n",student_ptr->Last_name);
		DPRINTF("\t \t \t \t \tStudent GPA         : %0.2f\n",student_ptr->GPA);
        for(j=0;j<5;j++)
        {
            DPRINTF("\t \t \t \t \tThe course ID are: %d\n",student_ptr->Course_ID[j]);
        }
        student_ptr++;
        DPRINTF("\t \t \t \t \t-------------------------\n");
    }
}
