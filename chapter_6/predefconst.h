/*************************
 * @file  : predefconst.h
 * @brief : 预定义常量
 * @author: 田世豪
 * @date  : 2020-1-25
 * **********************/

#pragma once

#include <stdio.h>
#include <stdlib.h>

// 函数结果状态代码
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define UNDERFLOW -3

// Status 是函数的类型, 其值是函数结果状态代码
typedef int Status;

// 数据元素类型
typedef int ElemType;
typedef int SElemType;
typedef void QElemType;
typedef char TElemType;

// 顺序栈存储空间初始分配量
#define STACK_INIT_SIZE 100

// 存储空间分配增量
#define STACK_INCREMENT 10

// 最大队列长度
#define MAXQSIZE 100

// 数组最大维数为 8
#define MAX_ARRAY_DIM 8
