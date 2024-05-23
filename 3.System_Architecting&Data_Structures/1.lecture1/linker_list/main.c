#include "linked_list.h"

int main()
{
    char Temp_Text[40];
	struct student_t* selected_student=NULL;

	while(1)
	{
		DPRINTF("\n ======================");
		DPRINTF("\n\t Choose on of the follwing options \n");
		DPRINTF("\n 1: Add_Student ");
		DPRINTF("\n 2: Delete_Student ");
		DPRINTF("\n 3: View_Students ");
		DPRINTF("\n 4: Delete_AllStudents ");
		DPRINTF("\n 5: GetNth ");
		DPRINTF("\n 6: Find_Length ");
		DPRINTF("\n 7: GetN_FronEnd ");
		DPRINTF("\n 8: Find_MiddleNode ");
		DPRINTF("\n 9: Rev_Node ");
		DPRINTF("\n Enter Option Number:  ");

		gets(Temp_Text);
		DPRINTF("\n =====================\n");
		switch(atoi(Temp_Text))
		{
		case 1:
			add_student();
			break;
		case 2:
			delete_student();
			break;
		case 3:
			view_students();
			break;
		case 4:
			delete_all();
			break;
        case 5:
		    selected_student = GET_NTH_node(0);
			DPRINTF("\n%s\n%d\n%0.2f",selected_student->student_data.name,selected_student->student_data.ID,selected_student->student_data.height);
			break;
        case 6:
			DPRINTF("the list length is :%d",list_length());
			break;
        case 7:
			selected_student = GET_NTH_node_from_end_2ndmethod(3);
            DPRINTF("\n%s\n%d\n%0.2f",selected_student->student_data.name,selected_student->student_data.ID,selected_student->student_data.height);
            break;
        case 8:
			selected_student = Middle_linked_list_1STmethod();
            DPRINTF("\n%s\n%d\n%0.2f",selected_student->student_data.name,selected_student->student_data.ID,selected_student->student_data.height);
			break;
        case 9:
			reverse_list();
			break;
		default:
			DPRINTF("\n Wrong Option ");
			break;
		}
	}

	return 0;
}

