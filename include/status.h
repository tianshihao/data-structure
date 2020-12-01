/**
 * @file status.h
 * @author 田世豪 (tianshihao@4944@126.com)
 * @brief 宏定义与共用头文件.
 * @version 0.2
 * @date 2020-11-30
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef STATUS_H
#define STATUS_H

#include <stdio.h>
#include <stdlib.h>

/* 函数结果状态代码. */
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define UNDERFLOW -3

/* Status 是函数的类型, 其值是函数结果状态代码. */
typedef int Status;

#endif /* STATUS_H */
