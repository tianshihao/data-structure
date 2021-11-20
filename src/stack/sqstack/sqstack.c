﻿/**
 * @file sqstack.c
 * @author tianshihao4944@126.com
 * @brief 顺序栈函数实现.
 * @version 0.1
 * @date 2020-01-27
 * @copyright Copyright (c) 2020
 */

#include <sqstack.h>

Status InitStackSq(SqStack *S)
{
    /* 栈顶指针指向分配的内存空间的起始地址. */
    S->base = malloc(STACK_INIT_SIZE * sizeof(StackElemType));

    /* 存储分配失败. */
    if (!S->base)
    {
        exit(OVERFLOW);
    }

    /* 初始化栈顶指针. */
    S->top = S->base;

    /* 初始化已分配空间大小. */
    S->allocated_size = STACK_INIT_SIZE;

    return OK;
}

Status StackEmptySq(SqStack S)
{
    if (S.top == S.base)
    {
        return TRUE;
    }

    return FALSE;
}

Status PushSq(SqStack *S, StackElemType e)
{
    /* 栈满, 追加存储空间. */
    if ((S->top - S->base) >= S->allocated_size)
    {
        S->base = realloc(S->base, (S->allocated_size + STACK_INCREMENT) * sizeof(StackElemType));

        /* 内存分配失败. */
        if (!S->base)
        {
            exit(OVERFLOW);
        }

        /* 重置栈顶指针. */
        S->top = S->base + S->allocated_size;

        /* 更新栈大小. */
        S->allocated_size += STACK_INCREMENT;
    }

    /* 更新栈顶指针, top 始终指向栈顶元素的下一位. */
    *(S->top)++ = e;

    return OK;
}

Status PopSq(SqStack *S, StackElemType *e)
{
    /* 若栈为空. */
    if (S->top == S->base)
    {
        return ERROR;
    }

    /* 弹出元素. */
    (*e) = *(--(S->top));

    return OK;
}

Status GetTopSq(SqStack S, StackElemType *e)
{
    /* 空栈. */
    if (S.top == S.base)
    {
        return ERROR;
    }

    /* 获取栈顶元素. */
    *e = *(S.top - 1);

    return OK;
}

Status DestoryStack(SqStack *S)
{
    /* 释放顺序栈内容空间. */
    free(S->base);

    /* 置栈顶栈顶指针为空. */
    S->base = NULL;
    S->top = NULL;

    return OK;
}

void Conversion()
{
    SqStack S;
    InitStackSq(&S);

    printf("Enter a decimal number: ");

    int N = 0;
    scanf("%d", &N);

    while (N)
    {
        PushSq(&S, N % 8);
        N = N / 8;
    }

    printf("Octal of this number is: ");

    StackElemType e;
    while (!StackEmptySq(S))
    {
        PopSq(&S, &e);
        printf("%d", e);
    }

    printf("\n");

    return;
}

Status MatchBrackets()
{
    printf("Enter a bracket sequence, length does not exceed 20.\n");

    SqStack S;
    InitStackSq(&S);

    char bracketSequence[20] = "\0";
    gets(bracketSequence);

    int len = sizeof(bracketSequence) / sizeof(bracketSequence[0]);
    for (int i = 0; (i < len) && (bracketSequence[i] != '\0'); ++i)
    {
        /* 左括号压栈. */
        if ((bracketSequence[i] == '(') || (bracketSequence[i] == '[') || (bracketSequence[i] == '{') || (bracketSequence[i] == '<'))
        {
            PushSq(&S, bracketSequence[i]);
        }
        else
        {
            StackElemType leftBracket;

            /* 栈中有括号. */
            if ((!StackEmptySq(S)) && (PopSq(&S, &leftBracket)))
            {
                /* 匹配. */
                /* 每对括号的 ASCII 相差 2, 除了 () 相差 1. */
                if ((leftBracket == (bracketSequence[i] - 1)) || leftBracket == (bracketSequence[i] - 2))
                {
                    continue;
                }
                /* 不匹配. */
                else
                {
                    return FALSE;
                }
            }
            /* stack have no bracket to match. */
            else
            {
                return FALSE;
            }
        }
    }

    /* 若存在未消解的括号, 则说明匹配失败. */
    if (StackEmptySq(S))
    {
        return TRUE;
    }

    return FALSE;
}
