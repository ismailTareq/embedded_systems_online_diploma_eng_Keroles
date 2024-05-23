#include "LIFO.h"
LIFO_status LIFO_Init(LIFO_buf_t* lifo_buf,unsigned int buf,unsigned int length)
{
    if(NULL==lifo_buf)
    {
        return LIFO_null;
    }
    else
    {
        lifo_buf->base=(unsigned int*)buf;
        lifo_buf->head=(unsigned int*)buf;
        lifo_buf->counter =0;
        lifo_buf->length = length;

        return LIFO_no_error;
    }
}
LIFO_status LIFO_add_item(LIFO_buf_t* lifo_buf,unsigned int item)
{
    if((NULL==lifo_buf))
    {
        return LIFO_null;
    }
    else
    {
        if(lifo_buf->head >= (lifo_buf->base + (lifo_buf->length *4)))
            return LIFO_full;

        *(lifo_buf->head)=item;
        lifo_buf->head++;
        lifo_buf->counter++;
        return LIFO_no_error;
    }
}
LIFO_status LIFO_get_item(LIFO_buf_t* lifo_buf,unsigned int* item)
{
    if((NULL==lifo_buf)||(NULL==item))
    {
        return LIFO_null;
    }
    else
    {
        if(lifo_buf->counter==0)
        {
            return LIFO_empty;
        }
        lifo_buf->head--;
        *item = *(lifo_buf->head);
        lifo_buf->counter--;
        return LIFO_no_error;
    }
}
