/**
 * @file  : sqqueue.h
 * @brief : 循环队列
 * @author: 田世豪
 * @date  : 2020-1-30
 */

#pragma once

#include <chapter1/status.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXQSIZE 100

typedef int QElemType;

typedef struct SqQueue
{
    // 初始化的动态分配存储空间
    QElemType *base;

    // 头指针, 若队列不空, 指向队头元素
    int front;

    // 尾指针, 若队列不空, 指向队尾元素的下一位置
    int rear;
} SqQueue;

Status InitQueue_Sq(SqQueue *Q);

int QueueLength_Sq(SqQueue Q);

Status EnQueue_Sq(SqQueue *Q, QElemType e);

Status DeQueue_Sq(SqQueue *Q, QElemType *e);

Status QueueEmpty_Sq(SqQueue Q);

void PrintQueue_Sq(SqQueue Q);
