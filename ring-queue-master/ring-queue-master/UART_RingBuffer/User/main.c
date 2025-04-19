#include "main.h"



/*主函数*/
int main(void)
{
    //初始化队列
    RQ_init(&uart1_que,uart1_buf,RING_BUF_SIZE);
    //打开串口
    usart_init(115200);
    
    while(1)
    {
        //出队
        if(!RQ_isEmpty(&uart1_que))
        {
            usart_sendByte(USART1,RQ_deQueue(&uart1_que));
        }
    }
}


