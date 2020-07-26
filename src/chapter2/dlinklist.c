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
    rear->data = 0;
    rear->prior = (*L);
    rear->next = NULL;

    (*L)->next = rear;
    (*L)->prior = NULL;

    return OK;

} // InitList_DL

Status HeadInsert_DL(DLinklist *L, ElemType e)
{
    // 创建新结点.
    DNode *p = malloc(sizeof(DNode));

    // 为新结点赋值.
    p->data = e;

    // 1. p 指向原来的第一个元素.
    p->next = (*L)->next;

    // 2. 修改原来的第一个元素前驱指向新元素.
    (*L)->next->prior = p;

    // 3. 新元素前驱为头结点.
    p->prior = (*L);

    // 4. 头结点指向新的第一个元素.
    (*L)->next = p;

    return OK;
} // HeadInsert_DL