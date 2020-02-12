/***************************
 * @file  : uselinkedqueue.c
 * @brief : 测试循环队列
 * @author: 田世豪
 * @date  : 2020-1-30
 * ************************/

#include "sqqueue.h"

int main()
{
    SqQueue Q;
    InitSqQueue(&Q);

    PrintSqQueue(Q);

    EnSqQueue(&Q, 1);
    EnSqQueue(&Q, 2);
    EnSqQueue(&Q, 3);
    EnSqQueue(&Q, 4);
    EnSqQueue(&Q, 5);

    PrintSqQueue(Q);

    QElemType e;

    DeSqQueue(&Q, &e);
    PrintSqQueue(Q);
    printf("front of queue is %d\n", e);
    printf("length = %d\n", SqQueueLength(Q));
    DeSqQueue(&Q, &e);
    PrintSqQueue(Q);
    printf("front of queue is %d\n", e);
    printf("length = %d\n", SqQueueLength(Q));
    DeSqQueue(&Q, &e);
    PrintSqQueue(Q);
    printf("front of queue is %d\n", e);
    printf("length = %d\n", SqQueueLength(Q));
    DeSqQueue(&Q, &e);
    PrintSqQueue(Q);
    printf("front of queue is %d\n", e);
    printf("length = %d\n", SqQueueLength(Q));
    DeSqQueue(&Q, &e);
    PrintSqQueue(Q);
    printf("front of queue is %d\n", e);
    printf("length = %d\n", SqQueueLength(Q));
    DeSqQueue(&Q, &e);
    PrintSqQueue(Q);
    printf("front of queue is %d\n", e);
    printf("length = %d\n", SqQueueLength(Q));

    return 0;
}