#include "FIFO.h"
element_type uart_buff[5];
FIFO_buf_t fifo_uart;
int main()
{
    int i,temp=0;
    if(FIFO_Init(&fifo_uart,uart_buff,5)==FIFO_no_error)
        printf("fifo init -------done\n");
    for(i=0;i<7;i++)
    {
        printf("fifo enqueue %d \n",i);
        if(enqueue(&fifo_uart,i)==FIFO_no_error)
            printf("fifo enqueue is done \n");
        else
            printf("fifo enqueue is failed \n");
    }
    FIFO_print(&fifo_uart);
    if(dequeue(&fifo_uart,&temp)==FIFO_no_error)
            printf("fifo dequeue %d is done \n",temp);
    if(dequeue(&fifo_uart,&temp)==FIFO_no_error)
            printf("fifo dequeue %d is done \n",temp);
    FIFO_print(&fifo_uart);
    return 0;
}
