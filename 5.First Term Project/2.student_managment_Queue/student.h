/*
 * Student.h
 *
 *  Created on: june 1, 2024
 *  Author: ismail tarek
 */
#ifndef STUDENT_H_
#define STUDENT_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stdint.h"
#include "conio.h"

#define STUDENT_BUFFER_LENGTH 50
#define element_type student_t

#define DPRINTF(...)      {fflush(stdout);\
		fflush(stdin);\
		printf(__VA_ARGS__);\
		fflush(stdout);\
		fflush(stdin);}

typedef struct {
    int RollNumber;
    char First_name[20];
    char Last_name[20];
    float GPA;
    int Course_ID[5];
}student_t;

typedef struct{
    int length;
    int counter;
    element_type* base;
    element_type* tail;
    element_type* head;
}FIFO_buf_t;

typedef enum{
    FIFO_no_error,
    FIFO_full,
    FIFO_empty,
    FIFO_null
}FIFO_status;

FIFO_status FIFO_Init(FIFO_buf_t* fifo,element_type* buf, int length);

void add_student_from_file(FIFO_buf_t* FIFO_Buffer);
void add_student_Manually(FIFO_buf_t* FIFO_Buffer);
void find_roll_number(FIFO_buf_t* FIFO_Buffer);
void find_first_name(FIFO_buf_t* FIFO_Buffer);
void find_course_ID(FIFO_buf_t* FIFO_Buffer);
void total_student(FIFO_buf_t* FIFO_Buffer);
void delete_student(FIFO_buf_t* FIFO_Buffer);
void update_student(FIFO_buf_t* FIFO_Buffer);
void show_student(FIFO_buf_t* FIFO_Buffer);
#endif // STUDENT_H_
