#include "DLL.h"
struct Node *head=NULL;
int main()
{
    Add_Node_Beginning(&head, 11);
    Display_Nodes(head);
    Add_Node_Beginning(&head, 22);
    Display_Nodes(head);
    Add_Node_Beginning(&head, 33);
    Display_Nodes(head);
    printf("----------------------\n");
    Add_Node(head, 99);
    Display_Nodes(head);
    Add_Node(head, 100);
    Display_Nodes(head);
    printf("----------------------\n");
    Add_After_Node(head, 44, 2);
    Display_Nodes(head);
    Add_After_Node(head, 55, 3);
    Display_Nodes(head);
    Add_After_Node(head, 66, 5);
    Display_Nodes(head);
    printf("----------------------\n");
    Add_before_Node(&head, 77, 3);
    Display_Nodes(head);
    Add_before_Node(&head, 88, 1);
    Display_Nodes(head);
    printf("----------------------\n");
    Delete_Node_Beginning(&head);
    Display_Nodes(head);
    Delete_Node_Beginning(&head);
    Display_Nodes(head);
    printf("----------------------\n");
    Delete_Node(head);
    Display_Nodes(head);
    Delete_Node(head);
    Display_Nodes(head);
    printf("----------------------\n");
    Delete_Selected_node(head, 2);
    Display_Nodes(head);
    Delete_Selected_node(head, 3);
    Display_Nodes(head);
    return 0;
}
