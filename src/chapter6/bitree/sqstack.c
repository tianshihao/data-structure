/**
 * @file sqstack.c
 * @author tianshihao
 * @brief 顺序栈的实现.
 * @version 0.1
 * @date 2020-08-08
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include <chapter6/bitree/sqstack.h>

Status InitStack(SqStack *S)
{
    // 栈顶指针指向分配的内存空间的起始地址
    S->base = malloc(STACK_INIT_SIZE * sizeof(StackElemType));

    // 存储分配失败
    if (!S->base)
    {
        exit(OVERFLOW);
    }

    S->top = S->base;

    S->stackSize = STACK_INIT_SIZE;

    return OK;
} // InitStack

Status StackEmpty(SqStack S)
{
    if (S.top == S.base)
    {
        return TRUE;
    }

    return FALSE;
} // StackEmpty

Status Push(SqStack *S, StackElemType e)
{
    // 栈满, 追加存储空间
    if ((S->top - S->base) >= S->stackSize)
    {
        S->base = realloc(S->base, (S->stackSize + STACK_INCREMENT) * sizeof(StackElemType));

        // 内存分配失败.
        if (!S->base)
        {
            exit(OVERFLOW);
        }

        // 重置栈顶指针
        S->top = S->base + S->stackSize;

        // 更新栈大小
        S->stackSize += STACK_INCREMENT;
    }

    // 更新栈顶指针, top 始终指向栈顶元素的下一位.
    *(S->top)++ = e;

    return OK;
} // Push

Status Pop(SqStack *S, StackElemType **e)
{
    // 若栈为空.
    if (S->top == S->base)
    {
        return ERROR;
    }

    /**
     * 这里将指向 BiTNode 指针的地址作为参数, 所以 *e 是指向 BiTNode 的指针.
     */
    *e = (--(S->top));

    return OK;
} // Pop

Status GetTop(SqStack S, StackElemType **e)
{
    // 空栈
    if (S.top == S.base)
    {
        return ERROR;
    }

    *e = (S.top - 1);

    return OK;
} // GetTop

int StackLength(SqStack S)
{
    return (S.top - S.base);
} // StackLength

Status ClearStack(SqStack *S)
{
    S->top = S->base;

    return OK;
} // ClearStack

Status DestoryStack(SqStack *S)
{
    // 释放顺序栈内容空间.
    free(S->base);

    // 置栈顶栈顶指针为空.
    S->base = NULL;
    S->top = NULL;

    // 更新栈大小.
    S->stackSize = 0;

    return OK;
} // DestoryStack

Status StackTraverse(SqStack S, Status (*visit)())
{
    return OK;
} // StackTraverse
