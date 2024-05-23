#ifndef LIFO_h_
#define LIFO_h_
#include <stdio.h>
#include <stdlib.h>
#include "stdlib.h"
typedef struct{
    unsigned int length;
    unsigned int counter;
    unsigned int* base;
    unsigned int* head;
}LIFO_buf_t;

typedef enum{
    LIFO_no_error,
    LIFO_full,
    LIFO_empty,
    LIFO_null
}LIFO_status;

LIFO_status LIFO_Init(LIFO_buf_t* lifo_buf,unsigned int buf,unsigned int length);
LIFO_status LIFO_add_item(LIFO_buf_t* lifo_buf,unsigned int item);
LIFO_status LIFO_get_item(LIFO_buf_t* lifo_buf,unsigned int* item);

#endif // LIFO_h_
