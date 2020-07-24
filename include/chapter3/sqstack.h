/************************
 * @file  : sqstack.h
 * @brief : 顺序栈
 * @author: 田世豪
 * @date  : 2020-1-27
 * *********************/

#pragma once

#include "predefconst.h"

typedef struct SqStack
{
    // 在栈构造之前和销毁之后, base 的值为 NULL
    SElemType *base;

    // 栈顶指针
    SElemType *top;

    // 当前已分配的存储空间, 以元素为单位
    int stack_size;
} SqStack;

// 构造一个空栈
Status InitStack(SqStack *S)
{
    // 栈顶指针指向分配的内存空间的起始地址
    S->base = malloc(STACK_INIT_SIZE * sizeof(SElemType));

    // 存储分配失败
    if (!S->base)
        exit(OVERFLOW);

    S->top = S->base;

    S->stack_size = STACK_INIT_SIZE;

    return OK;
} // InitStack

// 销毁栈 S, S 不再存在.
Status DestoryStack(SqStack *S)
{
    free(S->base);
    S->base = NULL;
    S->top = NULL;
    S->stack_size = 0;

    return OK;
} // DestoryStack

// 把 S 置为空栈.
Status ClearStack(SqStack *S)
{
    S->top = S->base;

    return OK;
} // ClearStack

// 若栈 S 为空, 则返回 TRUE, 否则返回 FALSE.
Status StackEmpty(SqStack S)
{
    if (S.top == S.base)
        return TRUE;
    return FALSE;
} // StackEmpty

// 返回 S 的元素个数, 即栈的长度.
int StackLength(SqStack S)
{
    return (S.top - S.base);
} // StackLength

// 若栈不空, 则用 e 返回 S 的栈顶元素, 并返回 OK; 否则返回 ERROR.
Status GetTop(SqStack S, SElemType *e)
{
    // 空栈
    if (S.top == S.base)
        return ERROR;

    *e = *(S.top - 1);

    return OK;
} // GetTop

// 插入元素 e 为新的栈顶元素.
Status Push(SqStack *S, SElemType e)
{
    // 栈满, 追加存储空间
    if ((S->top - S->base) >= S->stack_size)
    {
        S->base = realloc(S->base, (S->stack_size + STACK_INCREMENT) * sizeof(SElemType));

        if (!S->base)
            exit(OVERFLOW);

        // 重置栈顶指针
        S->top = S->base + S->stack_size;

        // 更新栈大小
        S->stack_size += STACK_INCREMENT;
    }

    *(S->top)++ = e;

    return OK;
} // Push

// 若栈不空, 则删除 S 的栈顶元素, 用 e 返回其值, 并返回 OK; 否则返回ERROR.
Status Pop(SqStack *S, SElemType *e)
{
    if (S->top == S->base)
        return ERROR;

    (*e) = *(--(S->top));

    return OK;
} // Pop

//从栈底到栈顶依次对栈中的每个元素调用函数 visit(). 一旦 visit() 失败, 则操作失败.
Status StackTraverse(SqStack S, Status (*visit)())
{
    return OK;
} // StackTraverse

// 栈的应用

// 数制转换
void conversion()
{
    SqStack S;
    InitStack(&S);

    printf("enter a decimal number: ");

    int N = 0;
    scanf("%d", &N);

    while (N)
    {
        Push(&S, N % 8);
        N = N / 8;
    }

    printf("octal of this number is: ");

    SElemType e;
    while (!StackEmpty(S))
    {
        Pop(&S, &e);
        printf("%d", e);
    }

    printf("\n");

    return;
} // conversion

// 括号匹配
Status MatchBrackets()
{
    printf("please enter a bracket sequence: ");

    SqStack S;
    InitStack(&S);

    char bracket_sequence[20] = "\0";
    gets(bracket_sequence);

    int len = sizeof(bracket_sequence) / sizeof(bracket_sequence[0]);
    for (int i = 0; (i < len) && (bracket_sequence[i] != '\0'); ++i)
    {
        // 左括号压栈
        if ((bracket_sequence[i] == '(') || (bracket_sequence[i] == '[') || (bracket_sequence[i] == '{') || (bracket_sequence[i] == '<'))
            Push(&S, bracket_sequence[i]);
        else
        {
            SElemType left_bracket;

            // stack have bracket
            if ((!StackEmpty(S)) && (Pop(&S, &left_bracket)))
            {
                // match
                // the ASCII of brackets differs by 2, except () differ by 1
                // 若匹配则出栈
                if ((left_bracket == (bracket_sequence[i] - 1)) || left_bracket == (bracket_sequence[i] - 2))
                    continue;
                // not match
                else
                    return FALSE;
            }
            // stack have no bracket to match
            else
                return FALSE;
        }
    }

    // 若存在未消解的括号, 则说明匹配失败
    if (StackEmpty(S))
        return TRUE;

    return FALSE;
}