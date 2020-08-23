/**
 * @file  : sqstack.h
 * @brief : 顺序栈
 * @author: 田世豪
 * @date  : 2020-1-27
 */

#ifndef SQSTACK_H
#define SQSTACK_H

#include <chapter1/status.h>
#include <stdio.h>
#include <stdlib.h>

#define STACK_INIT_SIZE 100
#define STACK_INCREMENT 20

typedef int SElemType;

typedef struct SqStack
{
    // 在栈构造之前和销毁之后, base 的值为 NULL
    SElemType *base;

    // 栈顶指针
    SElemType *top;

    // 当前已分配的存储空间, 以元素为单位
    int stackSize;
} SqStack;

/**
 * @brief 构造一个空顺序栈.
 * @param S 指向顺序栈的指针.
 */
Status InitStack(SqStack *S);

/**
 * @brief 若顺序栈 S 为空, 则返回 TRUE, 否则返回 FALSE.
 * @param S 顺序栈.
 */
Status StackEmpty(SqStack S);

/**
 * @brief 插入元素 e 为新的栈顶元素.
 * @param S 指向顺序栈的指针.
 * @param e 压入栈中的元素.
 */
Status Push(SqStack *S, SElemType e);

/**
 * @brief 若顺序栈 S 不空, 则删除 S 的栈顶元素, 用 e 返回其值, 并返回 OK; 否则返回ERROR.
 * @param S 指向顺序栈的指针.
 * @param e 用 e 保存出栈元素.
 */
Status Pop(SqStack *S, SElemType *e);

/**
 * @brief 若顺序栈 S 不空, 则用 e 返回 S 的栈顶元素, 并返回 OK; 否则返回 ERROR.
 * @param S 顺序栈.
 * @param e 保存栈顶元素.
 */
Status GetTop(SqStack S, SElemType *e);

/**
 * @brief 返回顺序栈 S 的元素个数, 即栈的长度.
 * @param S 顺序栈.
 */
int StackLength(SqStack S);

/**
 * @brief 把顺序栈 S 置为空栈.
 * @param S 指向顺序栈的指针.
 */
Status ClearStack(SqStack *S);

/**
 * @brief 销毁顺序栈 S, S 不再存在.
 * @param S 指向顺序栈的指针.
 */
Status DestoryStack(SqStack *S);

//从栈底到栈顶依次对栈中的每个元素调用函数 visit(). 一旦 visit() 失败, 则操作失败.
Status StackTraverse(SqStack S, Status (*visit)());

// 栈的应用

// 数制转换
void conversion();

// 括号匹配
Status MatchBrackets();

#endif // SQSTACK_H
