﻿#include <chapter2/dlinklist.h>

Status InitList_DL(DLinklist *L)
{
    *L = malloc(sizeof(DNode));
    if (!(*L))
    {
        exit(OVERFLOW);
    }

    (*L)->data = 0;

    // 为了保证可是使用头插法建立链表, 还要加入尾结点.
    DNode *rear = malloc(sizeof(DNode));
    rear->data = -1; // 尾结点标记.
    rear->prior = (*L);
    rear->next = NULL;

    (*L)->next = rear;
    (*L)->prior = NULL;

    return OK;

} // InitList_DL

Status HeadInsert_DL(DLinklist *L, ElemType e)
{
    // 创建新结点.
    DNode *s = malloc(sizeof(DNode));

    // 为新结点赋值.
    s->data = e;

    // 1. 新结点指向后继结点.
    s->next = (*L)->next;

    // 2. 后继结点指向新结点.
    (*L)->next->prior = s;

    // 3. 新结点指向前驱结点.
    s->prior = (*L);

    // 4. 前驱结点指向新结点.
    (*L)->next = s;

    return OK;
} // HeadInsert_DL

Status TailInsert_DL(DLinklist *L, ElemType e)
{
    // 不能是 p = (*L)->next, 可能会令 p 指向尾结点.
    DNode *p = (*L);

    // 找到到合适的位置.
    while (p->next && p->next->data != -1)
    {
        p = p->next;
    }

    // 这是新结点.
    DNode *s = malloc(sizeof(DNode));
    s->data = e;

    // 这里和 HeadInsert_DL() 一样了.

    // 1. 新结点指向后继结点.
    s->next = p->next;

    // 2. 后继结点指向新结点.
    p->next->prior = s;

    // 3. 新结点指向前驱结点.
    s->prior = p;

    // 4. 前驱结点指向新结点.
    p->next = s;

    return OK;
} // TailInsert_DL

DNode *GetElem_DL(DLinklist L, int i)
{
    if (i < 0 || i > ListLength_DL(L))
    {
        printf("索引越界\n");
        return NULL;
    }

    DNode *p = L;

    int counter = 0;

    while (p && counter < i)
    {
        p = p->next;
        counter++;
    }

    return p;
} // GetElem_DL

DNode *LocateElem_DL(DLinklist L, ElemType e)
{
    DNode *p = L->next;

    while (p && p->data != e)
    {
        p = p->next;
    }

    return p;
} // LocateElem_DL

Status ListInsert_DL(DLinklist *L, int i, ElemType e)
{
    DNode *p;

    p = GetElem_DL(*L, i - 1);

    if (!p)
    {
        printf("插入位置非法\n");
    }

    DNode *s = malloc(sizeof(DNode));
    s->data = e;

    s->next = p->next;
    p->next = s;

    return OK;
} // ListInsert_DL

Status ListDelete_DL(DLinklist *L, int i)
{
    DNode *p;

    p = GetElem_DL(*L, i - 1);

    if (!p)
    {
        printf("插入位置非法\n");
    }

    // 这是要删除的结点.
    DNode *q = p->next;

    // 跳过被删除结点.
    p->next = q->next;

    // 新的后继结点前驱指向 p.
    q->next->prior = p;

    // 删除结点 q.
    free(q);

    return OK;
} // ListDelete_DL

int ListLength_DL(DLinklist L)
{
    DNode *p = L->next;

    int length = 0;

    while (p && p->data != -1)
    {
        length++;
        p = p->next;
    }

    return length;
} // ListLength_DL

void PrintList_DL(DLinklist L)
{
    // L 是头结点, p 指向第一个结点.
    DNode *p = L->next;

    // 若第一个结点不为空, 则打印数据.
    while (p != NULL && p->data != -1)
    {
        printf("%d->", p->data);
        p = p->next;
    }

    return;
} // PrintList_DL