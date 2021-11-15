/**
 * @file linkqueue.c
 * @author tianshihao4944@126.com   
 * @brief 链式队列方法实现.
 * @version 0.2
 * @date 2020-11-22
 * @copyright Copyright (c) 2020
 */

#include <linkqueue.h>

Status InitQueue_Link(LinkQueue *Q)
{
    /* 建立头结点. */
    Q->front = Q->rear = (LinkQNode *)malloc(sizeof(LinkQNode));
    /* 如果内存分配失败. */
    if (!Q->front)
    {
        exit(OVERFLOW);
    }

    /* 初始为空. */
    Q->front->next = NULL;

    return OK;
}

Status QueueEmpty_Link(LinkQueue Q)
{
    /* 队列为空的判断条件是头指针和尾指针均指向头结点. */
    if (Q.front == Q.rear)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

Status EnQueue_Link(LinkQueue *Q, QueueElemType e)
{
    /* 工作指针, 指向新入队的结点. */
    LinkQNode *p = (LinkQNode *)malloc(sizeof(LinkQNode));
    /* 如果内存分配失败. */
    if (!p)
    {
        exit(OVERFLOW);
    }

    /* 为新结点赋值. */
    p->data = e;
    p->next = NULL;

    /* 插入新结点. 此时 Q->rear 指向队尾结点. */
    /* 将新结点连接到队尾结点之后. */
    Q->rear->next = p;
    /* 更新队尾结点. */
    Q->rear = p;

    return OK;
}

Status DeQueue_Link(LinkQueue *Q, QueueElemType *e)
{
    /* 空队列. */
    if (Q->front == Q->rear)
    {
        return ERROR;
    }

    /* 工作指针. 初始指向队头结点 (第一个结点). Q->front 指向的是头结点. */
    LinkQNode *p = Q->front->next;

    /* 获取队头结点数据. */
    (*e) = p->data;

    /* 逻辑上跳过队头结点. */
    Q->front->next = p->next;

    /* 若原队列中只有一个结点, 删除后变空队列. */
    if (Q->rear == p)
    {
        Q->rear = Q->front;
    }

    /* 释放队头结点内存空间, 物理上删除了队头元素. */
    free(p);

    return OK;
}

Status GetHead_Link(LinkQueue Q, QueueElemType *e)
{
    if (Q.front != Q.rear)
    {
        (*e) = Q.front->next->data;
        return OK;
    }
    else
        return ERROR;
}

int QueueLength_Link(LinkQueue Q)
{
    /* 计数器, 记录结点数目, 即队列长度. */
    int length = 0;
    /* 工作指针. 初始指向队头结点. */
    LinkQNode *p = Q.front->next;

    /* 循环. */
    while (p)
    {
        /* 指针向后指. */
        p = p->next;
        /* 计数器加 1. */
        ++length;
    }

    return length;
}

Status DestoryQueue_Link(LinkQueue *Q)
{
    /* 从头结点开始释放内存. */
    while (Q->front)
    {
        /* 把队尾指针当作辅助指针, 记录要释放内存结点的下一个结点. */
        Q->rear = Q->front->next;
        /* 把队头指针当作工作指针, 释放其指向的结点. */
        free(Q->front);
        /* 指向下一个结点. */
        Q->front = Q->rear;
    }

    return OK;
}

void PrintQueue_Link(LinkQueue Q)
{
    /* 空队列. */
    if (Q.front == Q.rear)
    {
        printf("Queue is empty\n");
        return;
    }

    for (LinkQNode *p = Q.front->next; p != NULL; p = p->next)
    {
        printf(" %d ", p->data);
    }
    printf("\n");

    return;
}
