/**
 * @file sqqueue.c
 * @author tianshihao4944@126.com
 * @brief 二叉树使用的队列.
 * @version 0.2
 * @date 2020-11-11
 * @copyright Copyright (c) 2020
 */

#include <tree/bitree/sqqueue.h>

Status InitQueue_Sq(SqQueue *Q)
{
    /* 为顺序队列申请内存空间. */
    Q->base = (QueueElemType *)malloc(MAX_SIZE * sizeof(QueueElemType));

    /* 如果内存申请失败. */
    if (!Q->base)
    {
        exit(OVERFLOW);
    }

    /* 初始化指针. */
    Q->front = Q->rear = 0;

    return OK;
}

Status QueueEmpty_Sq(SqQueue Q)
{
    return Q.front == Q.rear;
}

Status EnQueue_Sq(SqQueue *Q, QueueElemType e)
{
    /**
     * 为了区分队空还是队满的情况, 牺牲一个单元来区分队空和队满, 入队时少用一个
     * 队列单元, 约定以队头指针在队尾指针的下一位置作为队满的标志.
     */
    /* 如果队列已满. */
    if ((Q->rear + 1) % MAX_SIZE == Q->front)
    {
        return ERROR;
    }

    /* 新元素入队尾. */
    *(Q->base + Q->rear) = e;

    /* 队尾指针进一. */
    Q->rear = (Q->rear + 1) % MAX_SIZE;

    return OK;
}

Status DeQueue_Sq(SqQueue *Q, QueueElemType *e)
{
    /* 如果队列为空. */
    if (Q->front == Q->rear)
    {
        return ERROR;
    }

    /* 队头元素出队. */
    /**
     * 这么做的理由同 
     * @see PostOrderTraverse_Binary2
     */
    *e = *(Q->base + Q->front);

    /* 队头进一. */
    Q->front = (Q->front + 1) % MAX_SIZE;

    return OK;
}

Status GetHead_Sq(SqQueue Q, QueueElemType *e)
{
    /* 如果队列为空. */
    if (Q.front == Q.rear)
    {
        return ERROR;
    }

    /* 读取队头元素. */
    *e = Q.base[Q.front];

    return OK;
}

int QueueLength_Sq(SqQueue Q)
{
    return (Q.rear - Q.front + MAX_SIZE) % MAX_SIZE;
}

Status DestoryQueue_Sq(SqQueue *Q)
{
    /* 如果为队列分配了内存空间. */
    if (Q->base)
    {
        /* 释放内存. */
        free(Q->base);
        /* 重置指向内存空间的指针. */
        Q->base = NULL;
        /* 重置队头队尾指针. */
        Q->front = Q->rear = 0;

        return OK;
    }
    else
    {
        exit(ERROR);
    }
}

void PrintQueue_Sq(SqQueue Q)
{
    if (Q.front == Q.rear)
    {
        return;
    }

    int p = Q.front;

    while (p != Q.rear)
    {
        printf(" %d ", Q.base[p]);

        /* 队列指针进一. */
        p = (p + 1) % MAX_SIZE;
    }
    printf("\n");

    return;
}
