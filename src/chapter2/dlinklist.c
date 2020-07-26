#include <chapter2/dlinklist.h>

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