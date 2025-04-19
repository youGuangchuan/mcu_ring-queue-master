/**
  * @file     	ringQueue.h
  * @author   	YangHaifeng(阳海峰)
  * @email   	2995339193@qq.com
  * @version	V0.0
  * @license  	GNU General Public License (GPL)  
  * @detail		please follow the license!!!
  * @attention
  *  this file is aim to do something with ringQueue,it just fou usart and 
  * other communication part of MCU such as IIC,SPI,CAN,MODMOS etc.
  * in some MCU such as STM32,MSP432,MSP430,ESP32,ch32,gd32 etc.									
  * (本程序为了提高速度和简化，删减了一些不需要用到的功能)  																	
  * @htmlonly 
  * <span style="font-weight: bold">History</span> 
  * @endhtmlonly 
  * Version|Auther|Describe
  * ------|----|-------- 
  * V0.0|YangHaifeng|Create File
  * <h2><center>&copy;COPYRIGHT YangHaifeng All Rights Reserved.</center></h2>
  */ 

#ifndef __RINGQUEUE_H
#define __RINGQUEUE_H

#include <stdint.h>

/*使用宏加速(用函数会有调用开销)*/
#define USE_INLINE_SPEED_UP  0

/**
 * @brief 环形队列结构体
 * @note 此结构体主要用于数据传输的
 * 环形缓冲,解决单片机处理数据时卡死的现象
*/
typedef struct ringQueue
{
	uint32_t front;
    uint32_t rear;
	uint32_t size;
    uint8_t *base; 
}RQ;


#if !USE_INLINE_SPEED_UP

void RQ_init(RQ *queue,uint8_t *base,uint32_t size);
uint8_t RQ_isEmpty(RQ *queue);
uint8_t RQ_isFull(RQ *queue);
void RQ_enQueue(RQ *queue,uint8_t item);
uint8_t RQ_deQueue(RQ *queue);

#else

/**
 * @brief 队列初始化
 * @param queue 队列指针
 * @param size 数据存储区大小
 * @param base 数据存储区首地址
 * @retval None
 * @note 一定要为队列结构体分配内存
*/
static inline void RQ_init(RQ *queue,uint8_t *base,uint32_t size)
{
    queue->front = 0;
    queue->rear = 0;
    queue->size = size;
    queue->base = base;
}

/**
 * @brief 判断队列是否为空
 * @param queue 队列结构体指针
 * @retval 空返回1,非空返回0
*/
static inline uint8_t RQ_isEmpty(RQ *queue)
{
    if(queue->front == queue->rear)
    {
        return 1;
    }
    else 
    {
        return 0;
    }
}

/**
 * @brief 判断队列是否为空
 * @param queue 队列结构体指针
 * @retval 空返回1,非空返回0
*/
static inline uint8_t RQ_isFull(RQ *queue)
{
    if(queue->front == (queue->rear + 1) % queue->size)
    {
        return 1;
    }
    else 
    {
        return 0;
    }
}

/**
 * @brief 数据入队
 * @param queue 队列结构体指针
 * @param item  数据
 * @retval None
 * @note 入队前一定要判断是否满(防止满溢)
*/
static inline void RQ_enQueue(RQ *queue,uint8_t item)
{
    queue->rear = (queue->rear + 1) % queue->size;
    queue->base[queue->rear] = item;
}

/**
 * @brief 数据出队
 * @param queue 队列结构体指针
 * @retval 返回出队的数据
 * @note 出队前一定要判断是否空(防止空溢)
*/
static inline uint8_t RQ_deQueue(RQ *queue)
{
    queue->front = (queue->front + 1) % queue->size;
    return queue->base[queue->front];
}

#endif	//!USE_INLINE_SPEED_UP

#endif //__RINGQUEUE_H

