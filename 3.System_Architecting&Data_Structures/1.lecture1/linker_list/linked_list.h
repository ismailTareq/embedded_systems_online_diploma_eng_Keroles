#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_
#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "conio.h"
#define DPRINTF(...)      {fflush(stdout);\
	                       fflush(stdin);\
	                       printf(__VA_ARGS__);\
	                       fflush(stdout);\
                           fflush(stdin);}

struct data_t{
    int ID;
    char name[40];
    float height;
};

struct student_t{
    struct data_t student_data;
    struct student_t* next_student;
};
void add_student();
int delete_student();
void view_students();
void delete_all();
struct student_t* GET_NTH_node(int index);
int list_length();
int list_length_recursive();
struct student_t* GET_NTH_node_from_end(int index);
struct student_t* GET_NTH_node_from_end_2ndmethod(int index);
struct student_t* Middle_linked_list_1STmethod();
struct student_t* Middle_linked_list_2NDmethod();
void reverse_list();
#endif // LINKED_LIST_H_
