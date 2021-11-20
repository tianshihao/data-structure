/**
 * @file sqqueue.c
 * @author tianshihao4944@126.com
 * @brief 二叉树使用的队列.
 * @version 0.2
 * @date 2020-11-11
 * @copyright Copyright (c) 2020
 */

#include <sqqueue.h>

Status InitQueueSq(SqQueue *q)
{
    /* 为顺序队列申请内存空间. */
    q->base = (QueueElemType *)malloc(MAX_SIZE * sizeof(QueueElemType));

    /* 如果内存申请失败. */
    if (!q->base)
    {
        exit(OVERFLOW);
    }

    /* 初始化指针. */
    q->front = q->rear = 0;

    return OK;
}

Status QueueEmptySq(SqQueue q)
{
    return q.front == q.rear;
}

Status EnQueueSq(SqQueue *q, QueueElemType e)
{
    /**
     * 为了区分队空还是队满的情况, 牺牲一个单元来区分队空和队满, 入队时少用一个
     * 队列单元, 约定以队头指针在队尾指针的下一位置作为队满的标志.
     */
    /* 如果队列已满. */
    if ((q->rear + 1) % MAX_SIZE == q->front)
    {
        return ERROR;
    }

    /* 新元素入队尾. */
    *(q->base + q->rear) = e;

    /* 队尾指针进一. */
    q->rear = (q->rear + 1) % MAX_SIZE;

    return OK;
}

Status DeQueueSq(SqQueue *q, QueueElemType *e)
{
    /* 如果队列为空. */
    if (q->front == q->rear)
    {
        return ERROR;
    }

    /* 队头元素出队. */
    /**
     * 这么做的理由同 
     * @see PostOrderTraverseBinaryNonRecur
     */
    *e = *(q->base + q->front);

    /* 队头进一. */
    q->front = (q->front + 1) % MAX_SIZE;

    return OK;
}

Status GetHead_Sq(SqQueue q, QueueElemType *e)
{
    /* 如果队列为空. */
    if (q.front == q.rear)
    {
        return ERROR;
    }

    /* 读取队头元素. */
    *e = q.base[q.front];

    return OK;
}

int QueueLength_Sq(SqQueue q)
{
    return (q.rear - q.front + MAX_SIZE) % MAX_SIZE;
}

Status DestoryQueueSq(SqQueue *q)
{
    /* 如果为队列分配了内存空间. */
    if (q->base)
    {
        /* 释放内存. */
        free(q->base);
        /* 重置指向内存空间的指针. */
        q->base = NULL;
        /* 重置队头队尾指针. */
        q->front = q->rear = 0;

        return OK;
    }
    else
    {
        exit(ERROR);
    }
}

void PrintQueue_Sq(SqQueue q)
{
    if (q.front == q.rear)
    {
        return;
    }

    int p = q.front;

    while (p != q.rear)
    {
        printf(" %d ", q.base[p]);

        /* 队列指针进一. */
        p = (p + 1) % MAX_SIZE;
    }
    printf("\n");

    return;
}
