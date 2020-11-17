/**
 * @file  : linkqueue.h
 * @brief : 单链队列, 是先进先出的线性表
 * @author: 田世豪
 * @date  : 2020-1-29
 */

#ifndef LINKQUEUE_H
#define LINKQUEUE_H

#include <status.h>

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
Status InitQueue_L(LinkQueue *Q);

/**
 * 销毁队列 Q, Q 不再存在.
 */
Status DestoryQueue_L(LinkQueue *Q);

/**
 * 把 Q 置为空队列.
 */
Status ClearQueue(LinkQueue *Q);

/**
 * 若队列 Q 为空队列, 则返回 TRUE, 否则返回 FALSE.
 */
Status QueueEmpty(LinkQueue Q);

/**
 * 返回 Q 的元素个数, 即队列的长度.
 */
int QueueLength(LinkQueue Q);

/**
 * 若队列不空, 则用 e 返回 Q 的队头元素, 并返回 OK; 否则返回 ERROR.
 */
Status GetHead(LinkQueue Q, QElemType *e);

/**
 * 插入元素 e 为新的队尾元素.
 */
Status EnQueue(LinkQueue *Q, QElemType e);

/**
 * 若队列不空, 则删除 Q 的队头元素, 用 e 返回其值, 并返回 OK; 否则返回ERROR.
 */
Status DeQueue(LinkQueue *Q, QElemType *e);

//从队列底到队列顶依次对队列中的每个元素调用函数 visit(). 一旦 visit() 失败, 则操作失败.
Status QueueTraverse(LinkQueue Q, Status (*visit)());

/**
 * 打印队列数据.
 */
void PrintQueue_L(LinkQueue Q);

#endif /* LINKQUEUE_H */
