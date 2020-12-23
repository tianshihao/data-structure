/**
 * @file clinklist.c
 * @author 田世豪 (tianshihao@4944@126.com)
 * @brief 单向循环链表方法实现.
 * @version 0.3
 * @date 2020-12-16
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <linearlist/linklist/clinklist.h>

Status InitList_C(CLinklist *L)
{
    /* 为头结点分配内存空间. */
    (*L) = malloc(sizeof(CNode));
    /* 内存分配失败. */
    if (!(*L))
    {
        exit(OVERFLOW);
    }

    /* 以存储数据为 -1 作为头结点的标志. */
    (*L)->data = -1;
    /* 循环链表, 头结点的后继指向自己. */
    (*L)->next = (*L);

    return OK;
}

Status HeadInsert_C(CLinklist L, ElemType e)
{
    /* 创建新结点. */
    CNode *s = malloc(sizeof(CNode));

    /* 为新结点赋值. */
    s->data = e;

    /* 1. 新结点指向后继结点. */
    s->next = L->next;

    /* 2. 前驱结点指向新结点. */
    L->next = s;

    return OK;
}

Status TailInsert_C(CLinklist L, ElemType e)
{
    CNode *p = L->next;

    /* 找到到合适的位置. */
    while (p->next->data != -1)
    {
        p = p->next;
    }

    /* 这是新结点. */
    CNode *s = malloc(sizeof(CNode));
    s->data = e;

    /* 1. 新结点指向后继结点. */
    s->next = p->next;

    /* 2. 前驱结点指向新结点. */
    p->next = s;

    return OK;
}

CNode *GetElem_C(CLinklist L, int i)
{
    if (i < 0 || i > ListLength_C(L))
    {
        printf("Index out of range.\n");
        return NULL;
    }

    int counter = 0;
    CNode *p = L;

    while (counter < i)
    {
        p = p->next;
        ++counter;
    }

    return p;
}

CNode *LocateElem_C(CLinklist L, ElemType e)
{
    CNode *p = L->next;

    while (p->data != e)
    {
        p = p->next;
    }

    return p;
}

Status ListInsert_C(CLinklist L, int i, ElemType e)
{
    if (i < 1 || i > ListLength_C(L) + 1)
    {
        printf("Illegal insertion position.\n");
        return ERROR;
    }

    /* 新结点的前驱结点. */
    CNode *p = GetElem_C(L, i - 1);

    /* 这是要插入的结点. */
    CNode *s = malloc(sizeof(CNode));
    s->data = e;

    /* 1. 新结点指向后继结点. */
    s->next = p->next;

    /* 2. 前驱结点指向新结点. */
    p->next = s;

    return OK;
}

Status ListDelete_C(CLinklist L, int i)
{
    if (i < 1 || i > ListLength_C(L))
    {
        printf("Illegal deletion position.\n");
        return ERROR;
    }

    /* 被删除结点的前驱结点. */
    CNode *p = GetElem_C(L, i);

    /* 这是要删除的结点. */
    CNode *q = p->next;

    /* 跳过被删除结点. */
    p->next = q->next;

    /* 删除结点 q. */
    free(q);
    q = NULL;

    return OK;
}

int ListLength_C(CLinklist L)
{
    int length = 0;
    CNode *p = L->next;

    while (p->data != -1)
    {
        ++length;
        p = p->next;
    }

    return length;
}

void PrintList_C(CLinklist L)
{
    CNode *p = L->next;

    while (p != L)
    {
        printf("%d", p->data);

        if (p->next->data == -1)
        {
            printf("\n");
        }
        else
        {
            printf("->");
        }

        p = p->next;
    }

    return;
}

Status DelAll(CLinklist *L)
{
    CNode *p, *pre;
    CNode *minP, *minPre;

    /* 当链表不为空时, 是 != (*L) 不是 != NULL. */
    while ((*L)->next != (*L))
    {
        /* p 为工作指针, pre 指向 p 的前驱. */
        p = (*L)->next, pre = (*L);

        /* minP 指向数据元素最小的结点, minPre 记录其前驱. */
        minP = p, minPre = pre;

        /* 循环一趟. */
        while (p != (*L))
        {
            /* 找到更小的结点, 更新 minP 和 minPre. */
            if (p->data < minP->data)
            {
                minP = p;
                minPre = pre;
            }

            /* 工作指针前进一. */
            pre = p;
            p = p->next;
        }

        /* 输出找到的最小值. */
        printf("%d", minP->data);

        /* 并且删除最小值结点. */
        minPre->next = minP->next;
        free(minP);
        minP = NULL;

        if ((*L)->next != (*L))
        {
            printf(",");
        }
        else
        {
            printf("\n");
        }
    }

    /* 最后删除头结点. */
    free((*L));
    (*L) = NULL;

    return OK;
}
