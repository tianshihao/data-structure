﻿#include <stack/sqstack/sqstack.h>

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

    return;
}