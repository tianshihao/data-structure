/************************
 * @file  : sqqueue.h
 * @brief : 循环队列
 * @author: 田世豪
 * @date  : 2020-1-30
 * *********************/

#pragma once

#include "predefconst.h"

typedef struct SqQueue
{
    // 初始化的动态分配存储空间
    QElemType *base;

    // 头指针, 若队列不空, 指向队头元素
    int front;

    // 尾指针, 若队列不空, 指向队尾元素的下一位置
    int rear;
} SqQueue;

// 构造一个空队列.
Status InitSqQueue(SqQueue *Q)
{
    Q->base = (QElemType *)malloc(sizeof(MAXQSIZE * sizeof(QElemType)));

    if (!Q->base)
        exit(OVERFLOW);

    Q->front = Q->rear = 0;

    return OK;
} // InitSqQueue

// 返回 Q 的元素个数, 即队列的长度.
int SqQueueLength(SqQueue Q)
{
    return (Q.rear - Q.front + MAXQSIZE) % MAXQSIZE;
} // SqQueueLength

// 插入元素 e 为 Q 的新的队尾元素
Status EnSqQueue(SqQueue *Q, QElemType e)
{
    // 队列满
    if ((Q->rear + 1) % MAXQSIZE == Q->front)
        return ERROR;

    Q->base[Q->rear] = e;

    Q->rear = (Q->rear + 1) % MAXQSIZE;

    return OK;
} // EnQueue

// 若队列不空, 则删除 Q 的队头元素, 用 e 返回其值, 并返回 OK;
// 否则返回 ERROR.
Status DeSqQueue(SqQueue *Q, QElemType *e)
{
    if (Q->front == Q->rear)
        return ERROR;

    *e = Q->base[Q->front];

    Q->front = (Q->front + 1) % MAXQSIZE;

    return OK;
} // DeSqQueue

// 打印循环队列元素.
void PrintSqQueue(SqQueue Q)
{
    if (Q.front == Q.rear)
    {
        printf("queue is empty\n");
        return;
    }
    
    QElemType ptr = Q.front;

    while (ptr != Q.rear)
    {
        printf(" %d ", Q.base[ptr]);

        ptr = (ptr + 1) % MAXQSIZE;
    } // while
    printf("\n");

    return;
} // PrintSqQueue