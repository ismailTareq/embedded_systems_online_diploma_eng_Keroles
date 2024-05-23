#include "FIFO.h"
static FIFO_status FIFO_is_full(FIFO_buf_t* fifo);
FIFO_status FIFO_Init(FIFO_buf_t* fifo,element_type* buf,unsigned int length)
{
    if((NULL==buf)||(NULL==fifo))
    {
        return FIFO_null;
    }
    else
    {
        fifo->base=buf;
        fifo->head=buf;
        fifo->tail=buf;
        fifo->counter=0;
        fifo->length=length;
        return FIFO_no_error;
    }
}
FIFO_status enqueue(FIFO_buf_t* fifo,element_type item)
{
    if(NULL==fifo)
    {
        return FIFO_null;
    }
    else
    {
        if(FIFO_is_full(fifo)==FIFO_full)
            return FIFO_full;

        *(fifo->head)=item;
        fifo->counter++;
        if(fifo->head==fifo->base + (fifo->length * sizeof(element_type)))
        {
            fifo->head=fifo->base;
        }
        else
        {
            fifo->head++;
        }
        return FIFO_no_error;
    }
}
FIFO_status dequeue(FIFO_buf_t* fifo,element_type* item)
{
    if(NULL==fifo)
    {
        return FIFO_null;
    }
    else
    {
        if(fifo->counter==0)
            return FIFO_empty;

        *item =*(fifo->tail);
        fifo->counter--;
        if(fifo->tail==fifo->base + (fifo->length * sizeof(element_type)))
        {
            fifo->tail=fifo->base;
        }
        else
        {
            fifo->tail++;
        }
        return FIFO_no_error;
    }
}
void FIFO_print(FIFO_buf_t* fifo)
{
    element_type *temp;
    int i;
    if(fifo->counter==0)
        printf("fifo is empty\n");
    else
    {
        temp = fifo->tail;
        for(i=0;i<fifo->counter;i++)
        {
            printf("%d \n",*temp);
            temp++;
        }
    }
}
static FIFO_status FIFO_is_full(FIFO_buf_t* fifo)
{
    if(fifo->counter==fifo->length)
        return FIFO_full;
    return FIFO_no_error;
}
