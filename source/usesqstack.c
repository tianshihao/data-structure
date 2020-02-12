/***************************
 * @file  : usesqstack.c
 * @brief : 测试顺序栈
 * @author: 田世豪
 * @date  : 2020-1-27
 * ************************/

#include "sqstack.h"

int main()
{
    if (MatchBrackets())
    {
        printf("match\n");
    }
    else
    {
        printf("not match\n");
    }

    return 0;
}