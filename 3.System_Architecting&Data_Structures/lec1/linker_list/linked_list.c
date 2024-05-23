#include "linked_list.h"
struct student_t* first_student;
void add_student()
{
    struct student_t* new_student=NULL; //for adding new student
    struct student_t* last_student=NULL; //for finding the last student
    char temp[40];
    //check if list is empty
    if(first_student==NULL)
    {
        new_student =(struct student_t*)malloc(sizeof(struct student_t));
        first_student=new_student;
    }
    else
    {
        last_student = first_student;//initialize it to increment it
        new_student =(struct student_t*)malloc(sizeof(struct student_t));
        while(last_student->next_student)//it it's NULL then it will break
        {
            last_student=last_student->next_student;
        }
        last_student->next_student = new_student;
    }
    //fill the record
    printf("enter the student NAME: ");
    gets(new_student->student_data.name);

    printf("enter the student ID: ");
    gets(temp);
    new_student->student_data.ID=atoi(temp);

    printf("enter the student HEIGHT: ");
    gets(temp);
    new_student->student_data.height=atof(temp);

    //set the next pointer to NULL
    new_student->next_student=NULL;
}
int delete_student()
{
    char Temp_Text[40];
	int Selected_ID;

	// Get the Selected ID from user
	DPRINTF("\n Enter the ID Selected: ");
	gets(Temp_Text);
	Selected_ID = atoi(Temp_Text);
	if(first_student!=NULL)//if the list is not empty
    {
        struct student_t* selected_student=first_student; //for the one student i want to delete
        struct student_t* previous_student=NULL; // so when i delete it i can get the next one

        while(selected_student!=NULL)
        {
            if(selected_student->student_data.ID==Selected_ID)
            {
                if(previous_student!=NULL)//selected id not first student
                {
                    previous_student->next_student=selected_student->next_student;
                }
                else//selected id first student
                {
                    first_student=selected_student->next_student;
                }
                free(selected_student);
                return 1;
            }
            previous_student = selected_student;//Store previous record pointer
            selected_student= selected_student->next_student;//incr the selected student
        }
    }
    DPRINTF("\n cannot find the Student ID. ");
	return 0;
}
void view_students()
{
    struct student_t* view_student=first_student;//pointer to go through all of them
    int counter=0;
    if(first_student==NULL)
    {
        DPRINTF("\n the list is empty");
    }
    else
    {
        while(view_student)
        {
            DPRINTF("\n record number %d",counter+1);
            DPRINTF("\n name: %s",view_student->student_data.name);
            DPRINTF("\n ID: %d",view_student->student_data.ID);
            DPRINTF("\n Height: %.2f",view_student->student_data.height);
            view_student=view_student->next_student;
            counter++;
        }
    }

}
void delete_all()
{
    struct student_t* delete_student=first_student;//pointer to go through all of them
    if(first_student==NULL)
    {
        DPRINTF("\n the list is empty");
    }
    else
    {
        while(delete_student)
        {
            struct student_t* temp_student=delete_student;
            delete_student=delete_student->next_student;
            free(temp_student);
        }
        first_student = NULL;
    }
}
struct student_t* GET_NTH_node(int index)
{
    int counter=0;
    struct student_t* selected_student=first_student;
    while(selected_student)
    {
        if(counter == index)
            return selected_student;
        counter++;
        selected_student=selected_student->next_student;
    }
    return 0;
}
int list_length()
{
    int counter=0;
    struct student_t* current_student=first_student;
    while(current_student)
    {
        current_student=current_student->next_student;
        counter++;
    }
    return counter;
}
int list_length_recursive()
{
    struct student_t* current_student=first_student;
    if(current_student==NULL)
        return 0;
    current_student=current_student->next_student;
    return 1+list_length_recursive();
}
struct student_t* GET_NTH_node_from_end(int index)
{
    int length = list_length();
    int counter=0;
    struct student_t* selected_student=first_student;
    while(selected_student)
    {
        if(counter == (length-index))
            return selected_student;
        counter++;
        selected_student=selected_student->next_student;
    }
    return 0;
}
struct student_t* GET_NTH_node_from_end_2ndmethod(int index)
{
    int counter=0;
    struct student_t* main_ptr=first_student;
    struct student_t* ref_ptr=first_student;// move until reach to the Null
    while(ref_ptr)
    {
        if(counter==index)
        {
            main_ptr=main_ptr->next_student;
            return main_ptr;
        }
        counter++;
        ref_ptr=ref_ptr->next_student;
    }

}
struct student_t* Middle_linked_list_1STmethod()
{
    int counter=0;
    struct student_t* middle_student=first_student;
    int length = list_length();
    while(middle_student)
    {
        if(counter==(length/2))
            return middle_student;
        counter++;
        middle_student=middle_student->next_student;
    }
}
struct student_t* Middle_linked_list_2NDmethod()
{
    struct student_t* fast_ptr=first_student;
    struct student_t* slow_ptr=first_student;
    while(fast_ptr)
    {
        slow_ptr=slow_ptr->next_student;
        fast_ptr=fast_ptr->next_student->next_student;
    }
    return slow_ptr;
}
void reverse_list()
{
    struct student_t* current_student = first_student->next_student;
    struct student_t* previous_student = first_student;
    struct student_t* next_sstudent = current_student;
    while(current_student!=NULL)
    {
        next_sstudent=current_student->next_student;
        current_student->next_student=previous_student;
        previous_student=current_student;
        current_student = next_sstudent;

    }
    first_student=previous_student;
}
