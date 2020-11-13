/**
 * @file sqqueue.c
 * @author tianshihao4944@126.com
 * @brief 二叉树使用的队列.
 * @version 0.2
 * @date 2020-11-11
 * @copyright Copyright (c) 2020
 */

#include <chapter6/bitree/sqqueue.h>

Status InitQueue_Sq(SqQueue *Q)
{
    /* 为顺序队列申请内存空间. */
    Q->base = (QElemType *)malloc(MAX_SIZE * sizeof(QElemType));

    /* 如果内存申请失败. */
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
    /* 若已为队列分配内存空间, */
    if (Q->base)
    {
        /* 则释放内存. */
        free(Q->base);

        /* 同时重置存储空间为 NULL, 指针为 0.*/
        Q->base = NULL;
        Q->front = Q->rear = 0;

        return OK;
    }
    else
    {
        /* 队列未被分配内存空间, 销毁失败. */
        exit(ERROR);
    }
}

Status QueueEmpty_Sq(SqQueue Q)
{
    return Q.front == Q.rear;
}

Status EnQueue_Sq(SqQueue *Q, QElemType e)
{
    /**
     * 队头指针在队尾指针的下一位是队满的标志, 这样做会牺牲一位存储空间, 所以
     * 该队列实际上的最大尺寸为 MAX_SIEZ-1.
     */
    /* 队满, 无法新入队元素. */
    if ((Q->rear + 1) % MAX_SIZE == Q->front)
    {
        return ERROR;
    }

    /* memcpy(Q->base + Q->rear, &e, sizeof(e)); */
    /* 新元素入队尾. */
    /* Q->base[Q->rear] = e; */
    *(Q->base + Q->rear) = e;

    /* 队尾指针进一. */
    Q->rear = (Q->rear + 1) % MAX_SIZE;

    return OK;
}

Status DeQueue_Sq(SqQueue *Q, QElemType **e)
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
    *e = Q->base + Q->front;

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
