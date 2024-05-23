#ifndef FIFO_H_
#define FIFO_H_
#include <stdio.h>
#include <stdlib.h>
#include "stdint.h"
#include "stdlib.h"
#define element_type uint8_t



typedef struct{
    unsigned int length;
    unsigned int counter;
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

FIFO_status FIFO_Init(FIFO_buf_t* fifo,element_type* buf,unsigned int length);
FIFO_status enqueue(FIFO_buf_t* fifo,element_type item);
FIFO_status dequeue(FIFO_buf_t* fifo,element_type* item);
void FIFO_print(FIFO_buf_t* fifo);
#endif // FIFO_H_
