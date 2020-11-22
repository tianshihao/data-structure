/**
 * @file linkqueue.h
 * @author tianshihao4944@126.com
 * @brief 链式队列. 
 * @version 0.2
 * @date 2020-11-22
 * @copyright Copyright (c) 2020
 */

#ifndef LINKQUEUE_H
#define LINKQUEUE_H

#include <status.h>
#include <stdio.h>
#include <stdlib.h>

/* 队列存储类型为 int. */
typedef int QueueElemType;

/* 链式队列的存储结点. */
typedef struct LinkQNode
{
    /* 数据域. */
    QueueElemType data;
    /* 指针域. */
    struct LinkQNode *next;
} LinkQNode;

/* 链式队列的存储类型. */
/**
 * @brief 链式队列的优点:
 * 1. 特别适合于数据元素变动比较大的情形;
 * 2. 不存在队列满产生溢出的问题;
 * 3. 使用多个队列时, 不会出现存储分配不合理和 "溢出" 的问题.
 */
typedef struct LinkQueue
{
    /***
     * 队头指针.
     * @note 注意, 在带有头结点的链式队列中, 队头指针 front 指向的不是队头元素,
     * 指向的是头结点. 
     */
    LinkQNode *front;

    /* 队尾指针. */
    LinkQNode *rear;
} LinkQueue;

/**
 * @brief 初始化链式队列.
 * @param Q 指向链式队列的指针.
 * @return Status 构造成功返回 OK.
 */
Status InitQueue_Link(LinkQueue *Q);

/**
 * @brief 判断链式队列是否为空.
 * @param Q 链式队列.
 * @return Status 若链式队列为空, 则返回 TURE, 非空返回 FALSE.
 */
Status QueueEmpty_Link(LinkQueue Q);

/**
 * @brief 元素入队.
 * @param Q 指向链式队列的指针.
 * @param e 入队的数据元素.
 * @return Status 
 */
Status EnQueue_Link(LinkQueue *Q, QueueElemType e);

/**
 * @brief 元素出队.
 * @param Q 指向链式队列的指针.
 * @param e 用以返回队头元素.
 * @return Status 
 */
Status DeQueue_Link(LinkQueue *Q, QueueElemType *e);

/**
 * @brief 读队头元素. 若队列不空, 则用 e 返回 Q 的队头元素, 并返回 OK;
 * 否则返回 ERROR.
 * @param Q 链式队列.
 * @param e 存储队头元素.
 * @return Status 
 */
Status GetHead_Link(LinkQueue Q, QueueElemType *e);

/**
 * @brief 返回链式队列数据元素个数
 * @param Q 链式队列
 * @return int 队列中元素个数.
 */
int QueueLength_Link(LinkQueue Q);

/**
 * @brief 销毁链式队列.
 * @param Q 指向链式队列的指针.
 * @return Status 销毁成功返回 OK.
 */
Status DestoryQueue_Link(LinkQueue *Q);

/**
 * @brief 打印队列数据.
 * @param Q 指向链式队列的指针.
 */
void PrintQueue_Link(LinkQueue Q);

#endif /* LINKQUEUE_H */
