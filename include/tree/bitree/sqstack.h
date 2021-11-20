/**
 * @file sqstack.h
 * @author tianshihao
 * @brief 非递归遍历树时用到的顺序栈.
 * @version 0.1
 * @date 2020-08-08
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef SQSTACK_H
#define SQSTACK_H

#include <bitree.h>
#include <status.h>

/* 栈初始大小*/
#define STACK_INIT_SIZE 100
/* 栈大小增量 */
#define STACK_INCREMENT 20

/* 栈存储类型为 BiTNode */
typedef BiTNode StackElemType;

/* 顺序栈的存储类型. */
typedef struct SqStack
{
    /* 在栈构造之前和销毁之后, base 的值为 NULL. */
    StackElemType *base;

    /* 栈顶指针. */
    StackElemType *top;

    /* 当前已分配的存储空间, 以元素为单位. */
    int allocated_size;
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
 * @brief 若顺序栈 S 不空, 则删除 S 的栈顶元素, 用 e 返回其值.
 * @param S 指向顺序栈的指针.
 * @param e 用 e 保存出栈元素. 注意, 在子函数中修改的时候 BiTNode 的地址, 所以
 * e 的类型是 BiTNode **. 
 */
Status Pop_Sq(SqStack *S, StackElemType **e);

/**
 * @brief 若顺序栈 S 不空, 则用 e 返回 S 的栈顶元素, 并返回 OK; 否则返回 ERROR.
 * @param S 顺序栈.
 * @param e 保存栈顶元素.
 */
Status GetTop_Sq(SqStack S, StackElemType **e);

/**
 * @brief 销毁顺序栈 S, S 不再存在.
 * @param S 指向顺序栈的指针.
 */
Status DestoryStack(SqStack *S);

#endif /* SQSTACK_H */
