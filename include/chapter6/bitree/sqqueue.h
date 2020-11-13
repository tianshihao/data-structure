/**
 * @file sqqueue.h
 * @author tianshihao4944@126.com
 * @brief 二叉树用到的队列.
 * @version 0.2
 * @date 2020-11-11
 * @copyright Copyright (c) 2020
 */

#ifndef SQQUEUE_H
#define SQQUEUE_H

#include <chapter1/status.h>
#include <chapter6/bitree/bitree.h>
#include <stdio.h>
#include <stdlib.h>

/* 队列最大尺寸为 100. */
#define MAX_SIZE 100

/* 存储元素基本类型是二叉树结点. */
typedef BiTNode QElemType;

typedef struct SqQueue
{
    /* 初始化的动态分配存储空间. */
    QElemType *base;

    /* 头指针, 若队列不空, 指向队头元素. */
    int front;

    /* 尾指针, 若队列不空, 指向队尾元素的下一位置. */
    int rear;
} SqQueue;

/**
 * @brief 删除队列, 释放其内存空间.
 * @param Q 队列.
 * @return OK 操作成功返回 OK.
 * @return ERROR 操作失败返回 ERROR. 
 */
Status InitQueue_Sq(SqQueue *Q);

/**
 * @brief 删除队列, 释放其内存空间.
 * @param Q 队列.
 * @return OK 操作成功返回 OK.
 * @return ERROR 操作失败返回 ERROR. 
 */
Status DestoryQueue_Sq(SqQueue *Q);

/**
 * @brief 判队列空, 若循环队列 Q 为空返回 TRUE, 否则返回 FALSE.
 * @param Q 循环队列.
 */
Status QueueEmpty_Sq(SqQueue Q);

/**
 * @brief 入队, 若循环队列 Q 未满, 将 x 加入, 使之成为新的队尾.
 * @param Q 指向循环队列的指针.
 * @param e 入队的数据元素. 不是指针, 是值传递, 相当于复制了一份新的元素, 将其
 * 存储在队列中, 不影响原来的元素.
 */
Status EnQueue_Sq(SqQueue *Q, QElemType e);

/**
 * @brief 出队, 若循环队列 Q 非空, 删除队头元素, 并用 e 返回.
 * @param Q 指向循环队列的指针,
 * @param e 用以返回队头元素.
 */
Status DeQueue_Sq(SqQueue *Q, QElemType **e);

/**
 * @brief 若队列不空, 则用 e 返回 Q 的队头元素, 并返回 OK; 否则返回 ERROR.
 * @param Q 循环队列.
 * @param e 存储队头元素.
 */
Status GetHead_Sq(SqQueue Q, QElemType *e);

/**
 * @brief 返回循环队列数据元素个数.
 * @param Q 循环队列.
 */
int QueueLength_Sq(SqQueue Q);

/**
 * @brief 打印循环队列.
 * @param Q 循环队列.
 */
void PrintQueue_Sq(SqQueue Q);

#endif /* SQQUEUE_H */
