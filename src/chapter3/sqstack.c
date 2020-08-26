#include <chapter3/sqstack.h>

Status InitStack(SqStack *S)
{
    // 栈顶指针指向分配的内存空间的起始地址
    S->base = malloc(STACK_INIT_SIZE * sizeof(SElemType));

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

Status Push(SqStack *S, SElemType e)
{
    // 栈满, 追加存储空间
    if ((S->top - S->base) >= S->stackSize)
    {
        S->base = realloc(S->base, (S->stackSize + STACK_INCREMENT) * sizeof(SElemType));

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

Status Pop(SqStack *S, SElemType *e)
{
    // 若栈为空.
    if (S->top == S->base)
    {
        return ERROR;
    }

    (*e) = *(--(S->top));

    return OK;
} // Pop

Status GetTop(SqStack S, SElemType *e)
{
    // 空栈
    if (S.top == S.base)
    {
        return ERROR;
    }

    *e = *(S.top - 1);

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
    // gets(bracket_sequence);

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