/**
 * @file sqstack.h
 * @author tianshihao4944@126.com
 * @brief 顺序栈头文件. 
 * @version 0.1
 * @date 2020-01-27
 * @copyright Copyright (c) 2020
 */

#ifndef SQSTACK_H
#define SQSTACK_H

#include <status.h>

/* 栈初始大小*/
#define STACK_INIT_SIZE 100
/* 栈大小增量 */
#define STACK_INCREMENT 20

/* 栈存储类型为 int */
typedef int StackElemType;

/* 顺序栈的存储类型. */
typedef struct SqStack
{
    /* 在栈构造之前和销毁之后, base 的值为 NULL. */
    StackElemType *base;

    /* 栈顶指针. */
    StackElemType *top;

    /* 当前已分配的存储空间, 以元素为单位. */
    int allocatedSize;
} SqStack;

/**
 * @brief 构造一个空顺序栈.
 * @param S 指向顺序栈的指针.
 */
Status InitStack_Sq(SqStack *S);

/**
 * @brief 若顺序栈 S 为空, 则返回 TRUE, 否则返回 FALSE.
 * @param S 顺序栈.
 */
Status StackEmpty_Sq(SqStack S);

/**
 * @brief 插入元素 e 为新的栈顶元素.
 * @param S 指向顺序栈的指针.
 * @param e 压入栈中的元素.
 */
Status Push_Sq(SqStack *S, StackElemType e);

/**
 * @brief 若顺序栈 S 不空, 则删除 S 的栈顶元素, 用 e 返回其值, 并返回 OK; 否则返回ERROR.
 * @param S 指向顺序栈的指针.
 * @param e 用 e 保存出栈元素.
 */
Status Pop_Sq(SqStack *S, StackElemType *e);

/**
 * @brief 若顺序栈 S 不空, 则用 e 返回 S 的栈顶元素, 并返回 OK; 否则返回 ERROR.
 * @param S 顺序栈.
 * @param e 保存栈顶元素.
 */
Status GetTop_Sq(SqStack S, StackElemType *e);

/**
 * @brief 销毁顺序栈 S, S 不再存在.V
 * @param S 指向顺序栈的指针.
 */
Status DestoryStack(SqStack *S);

/**
 * @brief 进制转换.
 */
void Conversion();

/**
 * @brief 检查给定的括号序列是否匹配.
 * @return Status 匹配返回 TRUE, 否则返回 FALSE.
 */
Status MatchBrackets();

#endif /* SQSTACK_H */
