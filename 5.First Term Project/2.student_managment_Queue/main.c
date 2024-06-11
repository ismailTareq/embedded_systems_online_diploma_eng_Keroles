/*
 * main.c
 *
 *  Created on: june 1, 2024
 *  Author: ismail tarek
 */
#include "student.h"
student_t student[50];
int main()
{
    int Choice;
	FIFO_buf_t FIFOStudent;

	FIFO_Init(&FIFOStudent ,student , 50);
    DPRINTF("\t \t \t \t \t*********************************************\n");
	DPRINTF("\t \t \t \t \t   welcome to the student Mangement System\n");
    DPRINTF("\t \t \t \t \t*********************************************\n");

	while(1)
    {
        DPRINTF("\n\t \t \t \t \tChoose The Task that you want to perform\n");
        DPRINTF("\n");
		DPRINTF("\t \t \t \t \t1. Add the student Details Manually\n");
		DPRINTF("\t \t \t \t \t2. Add the student Details From Text File\n");
		DPRINTF("\t \t \t \t \t3. Find the Student Details by Roll Number\n");
		DPRINTF("\t \t \t \t \t4. Find the Student Details by First Name\n");
		DPRINTF("\t \t \t \t \t5. Find the student Details by Course ID\n");
		DPRINTF("\t \t \t \t \t6. Find the Total number of Students\n");
		DPRINTF("\t \t \t \t \t7. Delete the Students Details by Roll Number\n");
		DPRINTF("\t \t \t \t \t8. Update the Students Details by Roll Number\n");
		DPRINTF("\t \t \t \t \t9. Show all information\n");
		DPRINTF("\t \t \t \t \t10.Exit\n");
		DPRINTF("\n");
		DPRINTF("\t \t \t \t \tSo What Can I Do For You Today Sir: ");
		scanf("%d",&Choice);
		switch(Choice)
		{
		case 1:

			add_student_Manually(&FIFOStudent);
			DPRINTF("\t \t \t \t \t------------------------------\n");
			break;
        case 2:
			DPRINTF("\t \t \t \t \t------------------------------\n");
			add_student_from_file(&FIFOStudent);
			DPRINTF("\t \t \t \t \t------------------------------\n");
			break;
		case 3:
			DPRINTF("\t \t \t \t \t------------------------------\n");
			find_roll_number(&FIFOStudent);
			DPRINTF("\t \t \t \t \t------------------------------\n");
			break;
		case 4:
			DPRINTF("\t \t \t \t \t------------------------------\n");
			find_first_name(&FIFOStudent);
			DPRINTF("\t \t \t \t \t------------------------------\n");
			break;
		case 5:
			DPRINTF("\t \t \t \t \t------------------------------\n");
			find_course_ID(&FIFOStudent);
			DPRINTF("\t \t \t \t \t------------------------------\n");
			break;
		case 6:
			DPRINTF("\t \t \t \t \t------------------------------\n");
			total_student(&FIFOStudent);
			DPRINTF("\t \t \t \t \t------------------------------\n");
			break;
        case 7:
			DPRINTF("\t \t \t \t \t------------------------------\n");
			delete_student(&FIFOStudent);
			DPRINTF("\t \t \t \t \t------------------------------\n");
			break;
        case 8:
			DPRINTF("\t \t \t \t \t------------------------------\n");
			update_student(&FIFOStudent);
			DPRINTF("\t \t \t \t \t------------------------------\n");
			break;
        case 9:
			DPRINTF("\t \t \t \t \t------------------------------\n");
			show_student(&FIFOStudent);
			DPRINTF("\t \t \t \t \t------------------------------\n");
			break;
		case 10:
			exit(1);
		}
    }
    return 0;
}
