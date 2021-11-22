﻿/**
 * @file sqqueue.h
 * @author tianshihao4944@126.com
 * @brief 顺序队列头文件.
 * @version 0.1
 * @date 2020-09-13
 * @copyright Copyright (c) 2020
 */

#ifndef SQQUEUE_H
#define SQQUEUE_H

#include <status.h>

/* 队列的最大尺寸为 100.  实际能存储的元素数量为QUEUE_MAX_SIZE-1*/
#define MAX_SIZE 100

/* 队列存储类型为 int. */
typedef int QueueElemType;
/* 顺序队列的存储类型. */
typedef struct SqQueue
{
    /* 初始化的动态分配存储空间. */
    QueueElemType *base;

    /* 头指针, 若队列不空, 指向队头元素. */
    int front;

    /* 尾指针, 若队列不空, 指向队尾元素的下一位置. */
    int rear;
} SqQueue;

/**
 * @brief 初始化顺序队列, 构造一个空队列.
 * @param Q 指向空循环的指针.
 */
Status InitQueue_Sq(SqQueue *Q);

/**
 * @brief 判队列空, 若顺序队列 Q 为空返回 TRUE, 否则返回 FALSE.
 * @param Q 顺序队列.
 * @return TRUE 队列为空返回 TRUE.
 * @return FALSE 队列不空返回 FALSE.
 */
Status QueueEmpty_Sq(SqQueue Q);

/**
 * @brief 入队, 若顺序队列 Q 未满, 将 x 加入, 使之成为新的队尾.
 * @param Q 指向顺序队列的指针.
 * @param e 入队的数据元素.
 */
Status EnQueue_Sq(SqQueue *Q, QueueElemType e);

/**
 * @brief 出队, 若顺序队列 Q 非空, 删除队头元素, 并用 e 返回.
 * @param Q 指向顺序队列的指针,
 * @param e 用以返回队头元素.
 */
Status DeQueue_Sq(SqQueue *Q, QueueElemType *e);

/**
 * @brief 若队列不空, 则用 e 返回 Q 的队头元素, 并返回 OK; 否则返回 ERROR.
 * @param Q 顺序队列.
 * @param e 存储队头元素.
 */
Status GetHeadSq(SqQueue Q, QueueElemType *e);

/**
 * @brief 返回顺序队列数据元素个数.
 * @param Q 顺序队列.
 */
int QueueLengthSq(SqQueue Q);

/**
 * @brief 删除队列, 释放其内存空间.
 * @param Q 队列.
 * @return OK 操作成功返回 OK.
 * @return ERROR 操作失败返回 ERROR. 
 */
Status DestoryQueue_Sq(SqQueue *Q);

/**
 * @brief 打印顺序队列.
 * @param Q 顺序队列.
 * @return OK 打印成功.
 * @return ERROR 打印失败.
 */
Status PrintQueue_Sq(SqQueue Q);

#endif /* SQQUEUE_H */
