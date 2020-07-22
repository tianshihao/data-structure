/***************************
 * @file  : uselinkedqueue.c
 * @brief : 测试单链队列
 * @author: 田世豪
 * @date  : 2020-1-29
 * ************************/

#include "linkedqueue.h"

int main()
{
    LinkedQueue Q;
    InitQueue(&Q);
    QElemType e;

    printf("length = %d\n", QueueLength(Q));

    EnQueue(&Q, 1);
    EnQueue(&Q, 2);
    EnQueue(&Q, 3);
    EnQueue(&Q, 4);

    printf("length = %d\n", QueueLength(Q));

    DeQueue(&Q, &e);
    printf("e = %d\n", e);
    printf("length = %d\n", QueueLength(Q));

    PrintQueue(Q);

    GetHead(Q, &e);
    printf("e = %d\n", e);
    printf("length = %d\n", QueueLength(Q));

    printf("length = %d\n", QueueLength(Q));

    ClearQueue(&Q);

    PrintQueue(Q);

    if (DeQueue(&Q, &e))
        printf("wrong\n");
    else
        printf("bingo\n");

    DestoryQueue(&Q);

    return 0;
}