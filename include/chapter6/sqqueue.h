/**
 * @file sqqueue.h
 * @author tianshihao
 * @brief 二叉树用到的队列.
 * @version 0.1
 * @date 2020-08-09
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#pragma once

#include <chapter1/status.h>
#include <chapter6/bitree.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

typedef BiTNode QElemType;

typedef struct SqQueue
{
    // 初始化的动态分配存储空间
    QElemType *base;

    // 头指针, 若队列不空, 指向队头元素
    int front;

    // 尾指针, 若队列不空, 指向队尾元素的下一位置
    int rear;
} SqQueue;

/**
 * @brief 初始化循环队列, 构造一个空队列.
 * @param Q 指向空循环的指针.
 * */
Status InitQueue_Sq(SqQueue *Q);

/**
 * @brief 删除队列, 释放其内存空间.
 * @param Q 队列.
 * @return OK 操作成功返回 OK.
 * @return ERROR 操作失败返回 ERROR. 
 */
Status DeleteQueue_Sq(SqQueue *Q);

/**
 * @brief 判队列空, 若循环队列 Q 为空返回 TRUE, 否则返回 FALSE.
 * @param Q 循环队列.
 * */
Status QueueEmpty_Sq(SqQueue Q);

/**
 * @brief 入队, 若循环队列 Q 未满, 将 x 加入, 使之成为新的队尾.
 * @param Q 指向循环队列的指针.
 * @param e 入队的数据元素.
 * */
Status EnQueue_Sq(SqQueue *Q, QElemType e);

/**
 * @brief 出队, 若循环队列 Q 非空, 删除队头元素, 并用 e 返回.
 * @param Q 指向循环队列的指针,
 * @param e 用以返回队头元素.
 * */
Status DeQueue_Sq(SqQueue *Q, QElemType **e);

/**
 * @brief 若队列不空, 则用 e 返回 Q 的队头元素, 并返回 OK; 否则返回 ERROR.
 * @param Q 循环队列.
 * @param e 存储队头元素.
 * */
Status GetHead_Sq(SqQueue Q, QElemType *e);

/**
 * @brief 返回循环队列数据元素个数.
 * @param Q 循环队列.
 * */
int QueueLength_Sq(SqQueue Q);

/**
 * @brief 打印循环队列.
 * @param Q 循环队列.
 * */
void PrintQueue_Sq(SqQueue Q);
