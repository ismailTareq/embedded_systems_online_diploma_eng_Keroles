#ifndef DLL_H_
#define DLL_H_
#include <stdio.h>
#include <stdlib.h>
typedef unsigned int uint32;
struct Node{
    uint32 Data;
    struct Node *Left;
    struct Node *Right;
};

void Add_Node_Beginning(struct Node **head, uint32 Data);
void Add_Node(struct Node *head, uint32 Data);
void Add_After_Node(struct Node *head, uint32 Data, uint32 position);
void Add_before_Node(struct Node **head, uint32 Data, uint32 position);
void Delete_Node_Beginning(struct Node **head);
void Delete_Node(struct Node *head);
void Delete_Selected_node(struct Node *head, uint32 position);
void Display_Nodes(struct Node *head);
void Display_Nodes_Reverse(struct Node *head);
#endif // DLL_H_
