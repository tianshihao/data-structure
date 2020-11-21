/**
 * @file program.c
 * @author tianshihao4944@126.com
 * @brief 测试栈.
 * @version 0.1
 * @date 2020-01-27
 * @copyright Copyright (c) 2020
 */

#include <stack/sqstack/sqstack.h>

void UseSqstack();

int main()
{
    UseSqstack();

    system("pause");

    return 0;
}

void UseSqstack()
{
    if (MatchBrackets())
    {
        printf("match\n");
    }
    else
    {
        printf("not match\n");
    }

    Conversion();

    SqStack S;
    InitStack_Sq(&S);
    Push_Sq(&S, 2);
    Push_Sq(&S, 6);
    Push_Sq(&S, 10);
    Push_Sq(&S, 7);

    StackElemType e;
    printf("%d\n", e);

    Pop_Sq(&S, &e);
    printf("%d\n", e);

    return;
}