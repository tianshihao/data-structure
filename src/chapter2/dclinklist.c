#include <chapter2/dclinklist.h>

Status InitList_DC(DCLinklist *L)
{
    *L = malloc(sizeof(DCNode));
    if (!(*L))
    {
        exit(OVERFLOW);
    }

    (*L)->data = -1;

    (*L)->next = (*L);
    (*L)->prior = (*L);

    return OK;

} // InitList_DC

Status HeadInsert_DC(DCLinklist *L, ElemType e)
{
    // 创建新结点.
    DCNode *s = malloc(sizeof(DCNode));

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
} // HeadInsert_DC

Status TailInsert_DC(DCLinklist *L, ElemType e)
{
    // 不能是 p = (*L)->next, 可能会令 p 指向尾结点.
    DCNode *p = (*L);

    // 找到到合适的位置.
    while (p->next && p->next->data != -1)
    {
        p = p->next;
    }

    // 这是新结点.
    DCNode *s = malloc(sizeof(DCNode));
    s->data = e;

    // 这里和 HeadInsert_DC() 一样了.

    // 1. 新结点指向后继结点.
    s->next = p->next;

    // 2. 后继结点指向新结点.
    p->next->prior = s;

    // 3. 新结点指向前驱结点.
    s->prior = p;

    // 4. 前驱结点指向新结点.
    p->next = s;

    return OK;
} // TailInsert_DC

DCNode *GetElem_DC(DCLinklist L, int i)
{
    if (i < 0 || i > ListLength_DC(L) - 1)
    {
        printf("索引越界\n");
        return NULL;
    }

    DCNode *p = L;

    int counter = 0;

    while (p && counter < i)
    {
        p = p->next;
        counter++;
    }

    return p;
} // GetElem_DC

DCNode *LocateElem_DC(DCLinklist L, ElemType e)
{
    DCNode *p = L->next;

    while (p && p->data != e)
    {
        p = p->next;
    }

    return p;
} // LocateElem_DC

Status ListInsert_DC(DCLinklist *L, int i, ElemType e)
{
    DCNode *p;

    p = GetElem_DC(*L, i - 1);

    if (!p)
    {
        printf("插入位置非法\n");
    }

    DCNode *s = malloc(sizeof(DCNode));
    s->data = e;

    s->next = p->next;
    p->next = s;

    return OK;
} // ListInsert_DC

Status ListDelete_DC(DCLinklist *L, int i)
{
    DCNode *p;

    p = GetElem_DC(*L, i - 1);

    if (!p)
    {
        printf("插入位置非法\n");
    }

    // 这是要删除的结点.
    DCNode *q = p->next;

    // 跳过被删除结点.
    p->next = q->next;

    // 新的后继结点前驱指向 p.
    q->next->prior = p;

    // 删除结点 q.
    free(q);

    return OK;
} // ListDelete_DC

int ListLength_DC(DCLinklist L)
{
    DCNode *p = L->next;

    int length = 0;

    while (p && p->data != -1)
    {
        length++;
        p = p->next;
    }

    return length;
} // ListLength_DC

void PrintList_DC(DCLinklist L)
{
    // L 是头结点, p 指向第一个结点.
    DCNode *p = L->next;

    // 若第一个结点不为空, 则打印数据.
    while (p != NULL && p->data != -1)
    {
        printf("%d->", p->data);
        p = p->next;
    }

    return;
} // PrintList_DC