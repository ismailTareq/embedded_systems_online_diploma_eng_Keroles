#include "LIFO.h"

unsigned int buffer1[5];
int main()
{
    int i,temp=0;
    LIFO_buf_t uart_lifo, i2c_lifo;
    //static allocation
    LIFO_Init(&uart_lifo,buffer1,5);
    //dynamic allocation
    unsigned int* buffer2 =(unsigned int*)malloc(5*sizeof(unsigned int));
    LIFO_Init(&i2c_lifo,buffer2,5);

    for(i=0;i<5;i++)
    {
        if(LIFO_add_item(&uart_lifo,i)==LIFO_no_error)
        {
            printf("UART LIFO add:%d\n",i);
        }
    }
    for(i=0;i<5;i++)
    {
        if(LIFO_get_item(&uart_lifo,&temp)==LIFO_no_error)
        {
            printf("UART LIFO get:%d\n",temp);
        }
    }
    printf("==============================================\n");
    for(i=0;i<5;i++)
    {
        if(LIFO_add_item(&i2c_lifo,i)==LIFO_no_error)
        {
            printf("I2C LIFO add:%d\n",i);
        }
    }
    for(i=0;i<5;i++)
    {
        if(LIFO_get_item(&i2c_lifo,&temp)==LIFO_no_error)
        {
            printf("I2C LIFO get:%d\n",temp);
        }
    }
    return 0;
}
