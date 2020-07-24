/**
 * @file  : linkqueue.h
 * @brief : 单链队列, 是先进先出的线性表
 * @author: 田世豪
 * @date  : 2020-1-29
 */

#pragma once

#include <chapter1/status.h>
#include <stdio.h>
#include <stdlib.h>

typedef int QElemType;

typedef struct QNode
{
    QElemType data;
    struct QNode *next;
} QNode, *QueuePtr;

typedef struct LinkQueue
{
    // 队头指针
    QueuePtr front;

    // 队尾指针
    QueuePtr rear;
} LinkQueue;

/**
 * 构造一个空队列.
 */
Status InitQueue_L(LinkQueue *Q)
{
    Q->front = Q->rear = malloc(sizeof(QNode));

    if (!Q->front)
    {
        exit(OVERFLOW);
    }
    Q->front->next = NULL;

    return OK;
} // InitQueue_L

/**
 * 销毁队列 Q, Q 不再存在.
 */
Status DestoryQueue_L(LinkQueue *Q)
{
    // 过河拆桥?
    while (Q->front)
    {
        Q->rear = Q->front->next;
        free(Q->front);
        Q->front = Q->rear;
    } // while

    return OK;
} // DestoryQueue_L

/**
 * 把 Q 置为空队列.
 */
Status ClearQueue(LinkQueue *Q)
{
    QueuePtr ptr = Q->front->next;

    while (ptr)
    {
        Q->front->next = ptr->next;
        free(ptr);
        ptr = Q->front->next;
    } // while

    Q->rear = Q->front;

    return OK;
} // ClearQueue

/**
 * 若队列 Q 为空队列, 则返回 TRUE, 否则返回 FALSE.
 */
Status QueueEmpty(LinkQueue Q)
{ // 队列为空的判断条件是头指针和尾指针均指向头结点
    if (Q.front == Q.rear)
        return TRUE;
    return FALSE;
} // QueueEmpty

/**
 * 返回 Q 的元素个数, 即队列的长度.
 */
int QueueLength(LinkQueue Q)
{
    int len = 0;
    QueuePtr ptr = Q.front->next;

    while (ptr)
    {
        ptr = ptr->next;
        ++len;
    }

    return len;
} // QueueLength

/**
 * 若队列不空, 则用 e 返回 Q 的队头元素, 并返回 OK; 否则返回 ERROR.
 */
Status GetHead(LinkQueue Q, QElemType *e)
{
    if (Q.front != Q.rear)
    {
        (*e) = Q.front->next->data;
        return OK;
    }
    else
        return ERROR;
} // GetHead

/**
 * 插入元素 e 为新的队尾元素.
 */
Status EnQueue(LinkQueue *Q, QElemType e)
{
    QueuePtr ptr = malloc(sizeof(QNode));

    if (!ptr)
        exit(OVERFLOW);

    ptr->data = e;
    ptr->next = NULL;

    Q->rear->next = ptr;
    Q->rear = ptr;

    return OK;
} // EnQueue

/**
 * 若队列不空, 则删除 Q 的队头元素, 用 e 返回其值, 并返回 OK; 否则返回ERROR.
 */
Status DeQueue(LinkQueue *Q, QElemType *e)
{
    if (Q->front == Q->rear)
        return ERROR;

    QueuePtr ptr = Q->front->next;
    (*e) = ptr->data;

    Q->front->next = ptr->next;

    // 之后队列将为空, 顺便重置尾指针
    if (Q->rear == ptr)
        Q->rear = Q->front;

    free(ptr);

    return OK;
} // DeQueue

//从队列底到队列顶依次对队列中的每个元素调用函数 visit(). 一旦 visit() 失败, 则操作失败.
Status QueueTraverse(LinkQueue Q, Status (*visit)())
{
    return OK;
} // QueueTraverse

/**
 * 打印队列数据.
 */
void PrintQueue_L(LinkQueue Q)
{
    if (Q.front == Q.rear)
    {
        printf("queue is empty\n");
        return;
    }

    for (QueuePtr ptr = Q.front->next; ptr != NULL; ptr = ptr->next)
        printf(" %d ", ptr->data);
    printf("\n");

    return;
} // PrintQueue_L