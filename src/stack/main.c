/**
 * @file main.c
 * @author tianshihao4944@126.com
 * @brief 测试栈.
 * @version 0.2
 * @date 2020-01-27
 * @copyright Copyright (c) 2020
 */

#include <linkstack.h>
#include <sqstack.h>

void UseSqstack();

int main()
{
    UseSqstack();

    system("pause");

    return 0;
}

void UseSqstack()
{
    printf("Input 1 to ");
    printf("determine whether a bracket sequence matches.\n");
    printf("Enter 2 to ");
    printf("conver a decimal to an octal number.\n");
    printf("Or input q to quit.\n");

    char ch = getchar();

    while (ch = getchar() != 'q')
    {

        if (ch == '1')
        {
            if (MatchBrackets())
            {
                printf("Match.\n");
            }
            else
            {
                printf("Not match.\n");
            }
        }
        else if ('2' == ch)
        {
            Conversion();
        }
        else
        {
            printf("Input is invalid!\n");
        }

        while (getchar() != '\n')
        {
            continue;
        }
        // SqStack S;
        // InitStackSq(&S);
        // PushSq(&S, 2);
        // PushSq(&S, 6);
        // PushSq(&S, 10);
        // PushSq(&S, 7);

        // StackElemType e;
        // printf("%d\n", e);

        // PopSq(&S, &e);
        // printf("%d\n", e);
    }

    printf("Bye!\n");

    return;
}
