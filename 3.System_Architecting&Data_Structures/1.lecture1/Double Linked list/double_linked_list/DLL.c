#include "DLL.h"

void Add_Node_Beginning(struct Node **head, uint32 Data)
{
    struct Node *new_node = NULL;
    new_node = (struct Node *)malloc(sizeof(struct Node));
    new_node->Data = Data;
    //the list is empty
    if(*head == NULL)
    {
        new_node->Left = NULL;
        new_node->Right = NULL;
        *head = new_node;//Make the Head pointer points to address of new node
    }
    //the list is not empty
    else
    {
        new_node->Left = NULL;
        new_node->Right = *head;
        (*head)->Left = new_node;
        *head = new_node;
    }
}
void Add_Node(struct Node *head, uint32 Data)
{
    struct Node *new_node = NULL;
    struct Node *node_counter = head;
    new_node = (struct Node *)malloc(sizeof(struct Node));
    while(node_counter->Right != NULL)
    {
        node_counter=node_counter->Right;
    }
    new_node->Left = node_counter;
    new_node->Right = NULL;
    new_node->Data = Data;
    node_counter->Right = new_node;

}
void Add_After_Node(struct Node *head, uint32 Data, uint32 position)
{
    struct Node *new_node = NULL;
    struct Node *previous = head;
    struct Node *next = NULL;
    new_node = (struct Node *)malloc(sizeof(struct Node));
    new_node->Data = Data;
    while(position!=1)
    {
        previous = previous->Right;
        position--;
    }
    if(previous->Right==NULL)
    {
        new_node->Right=NULL;
        previous->Right = new_node;
        new_node->Left = previous;
    }
    else
    {
        next = previous->Right;
        new_node->Left = previous;
        new_node->Right = next;
        previous->Right = new_node;
        next->Left = new_node;
    }
}
void Add_before_Node(struct Node **head, uint32 Data, uint32 position)
{
    struct Node *new_node = NULL;
    struct Node *previous = *head;
    struct Node *next = NULL;
    uint32 node_pos = position;
    new_node = (struct Node *)malloc(sizeof(struct Node));
    new_node->Data = Data;
    while(node_pos>position-1)
    {
        previous = previous->Right;
        node_pos--;
    }
    if(position==1)
    {
        new_node->Left = NULL;
        new_node->Right = *head;
        (*head)->Left=new_node;
        *head = new_node;
    }
    else
    {
        next = previous->Right;
        new_node->Right = next;
        new_node->Left = previous;
        previous->Right = new_node;
        next->Left = new_node;
    }
}
void Delete_Node_Beginning(struct Node **head)
{
    *head = (*head)->Right;
    free((*head)->Left);
    (*head)->Left = NULL;
}
void Delete_Node(struct Node *head)
{
    struct Node *previous = head;
    struct Node *next = NULL;
    while(previous->Right!=NULL)
        previous=previous->Right;
    next = previous->Left;
    next->Right = NULL;
    free(previous);
    previous = NULL;
}
void Delete_Selected_node(struct Node *head, uint32 position)
{
    struct Node *previous = NULL;
    struct Node *next = NULL;
    uint32 node_pos = position;
    if(1 == node_pos){
        printf("Please use the Delete_Node_Beginning !! \n");
    }
    else
    {
        previous = head;
        while(node_pos>1)
        {
            previous=previous->Right;
            node_pos--;
        }
        next = previous->Left;
        next->Right = previous->Right;
        previous->Right->Left = next;
        free(previous);
        previous = NULL;
    }
}
void Display_Nodes(struct Node *head)
{
    struct Node *node = head;
    printf("\nprinting in forward direction ==> ");
    printf("Data : ");
    printf("%d -> ", node->Data);
    while(node->Right!=NULL)
    {
        node=node->Right;
        printf("%d -> ", node->Data);
    }
    if(NULL == node->Right){
        printf("NULL");
    }
    printf("\n");
}
void Display_Nodes_Reverse(struct Node *head)
{

}
