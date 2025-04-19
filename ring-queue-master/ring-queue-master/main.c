#include <stdio.h>
#include <stdint.h>
#include "ringQueue.h"



int main()
{
    RQ aobject;
    RQ *a = &aobject;
    uint8_t arr[256];
    int t;

    RQ_init(a,arr,8);

    /*入队之前一定要判断满*/
    while(!RQ_isFull(a))
    {
        printf("input:");
        scanf("%d",&t);
        RQ_enQueue(a,(uint8_t)t);
    }

    /*出队之前要判断空*/
    while(!RQ_isEmpty(a))
    {
        printf("%d\n",RQ_deQueue(a));
    }

    return 0;
}