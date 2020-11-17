/**
 * @file sqqueue.c
 * @author tianshihao4944@126.com
 * @brief 顺序循环队列.
 * @version 0.1
 * @date 2020-09-13
 * @copyright Copyright (c) 2020
 */

#include <graph/mgraph/sqqueue.h>

Status InitQueue_Sq(SqQueue *Q)
{
    /* 为顺序队列申请内存空间. */
    Q->base = (QElemType *)malloc(MAX_SIZE * sizeof(QElemType));
    if (!Q->base)
    {
        exit(OVERFLOW);
    }

    /* 初始化指针. */
    Q->front = Q->rear = 0;

    return OK;
}

Status DestoryQueue_Sq(SqQueue *Q)
{
    if (Q->base)
    {
        free(Q->base);
        Q->base = NULL;
        Q->front = Q->rear = 0;
        return OK;
    }
    else
    {
        return ERROR;
    }
}

Status QueueEmpty_Sq(SqQueue Q)
{
    return Q.front == Q.rear;
}

Status EnQueue_Sq(SqQueue *Q, QElemType e)
{
    /* 队头指针在队尾指针的下一位是队满的标志, 这样做会牺牲一位存储空间. */
    if ((Q->rear + 1) % MAX_SIZE == Q->front)
    {
        return ERROR;
    }

    /* 新元素入队尾. */
    /* Q->base[Q->rear] = e; */
    *(Q->base + Q->rear) = e;

    /* 队尾指针进一. */
    Q->rear = (Q->rear + 1) % MAX_SIZE;

    return OK;
}

Status DeQueue_Sq(SqQueue *Q, QElemType *e)
{
    /* 如果队列为空. */
    if (Q->front == Q->rear)
    {
        return ERROR;
    }

    /* 队头元素出队. */
    *e = Q->base[Q->front];

    /* 队头进一. */
    Q->front = (Q->front + 1) % MAX_SIZE;

    return OK;
}

Status GetHead_Sq(SqQueue Q, QElemType *e)
{
    if (Q.front == Q.rear)
    {
        return ERROR;
    }

    *e = Q.base[Q.front];

    return OK;
}

int QueueLength_Sq(SqQueue Q)
{
    return (Q.rear - Q.front + MAX_SIZE) % MAX_SIZE;
}

Status PrintQueue_Sq(SqQueue Q)
{
    if (QueueEmpty_Sq(Q))
    {
        exit(ERROR);
    }

    printf("        <-front ");

    int p = Q.front;

    while (p != Q.rear)
    {
        printf(" %d ", Q.base[p]);

        /* 队列指针进一. */
        p = (p + 1) % MAX_SIZE;
    }

    printf(" rear->\n");

    return OK;
}
