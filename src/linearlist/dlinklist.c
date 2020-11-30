/**
 * @file dlinklist.c
 * @author 田世豪 (tianshihao@4944@126.com)
 * @brief 双向链表方法实现.
 * @version 0.1
 * @date 2020-07-26
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <linearlist/dlinklist.h>

Status InitList_DL(DLinklist *L)
{
    // 为头结点分配内存空间.
    *L = malloc(sizeof(DNode));
    // 内存分配失败.
    if (!(*L))
    {
        exit(OVERFLOW);
    }

    // 为了保证可是使用头插法建立链表, 还要加入尾结点.
    DNode *rear = malloc(sizeof(DNode));
    rear->data = -1; // 尾结点标记.
    rear->freq = -1;
    rear->prior = (*L);
    rear->next = NULL;

    (*L)->data = -1;
    (*L)->freq = -1;
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
    s->freq = 0;

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
    while (p->next->data != -1)
    {
        p = p->next;
    }

    // 这是新结点.
    DNode *s = malloc(sizeof(DNode));
    s->data = e;
    s->freq = 0;

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
        printf("Index out of range.\n");
        return NULL;
    }

    int counter = 0;
    DNode *p = L;

    while (p && counter < i)
    {
        ++counter;
        p = p->next;
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

DNode *LccateElem_DL2(DLinklist *L, ElemType e)
{
    // 第一部分, 寻找结点.

    // p 是工作指针, 找符合要求的结点; pre 是 p 的前驱.
    DNode *p = (*L)->next, *pre = (*L);

    while (p && p->data != e)
    {
        pre = p;
        p = p->next;
    }

    // 如果符合要求的节点存在, 那么将其频度加 1.
    if (p)
    {
        ++p->freq;
    }
    // 否则算法可以结束了.
    else
    {
        return NULL;
    }

    // 第二部分, 剥离结点.

    // 找到符合要求的结点后, 将其从链表中剥离.
    // 1. 前驱结点向后跳过被删除结点.
    pre->next = p->next;
    // 2. 后继结点向前跳过被删除结点.
    p->next->prior = pre;

    // 这时候 p 被剥离了出来. 然后将 p 插入到合适的位置. 和普通插入没什么区别.
    // 为了描述方便, 这是使用 s 替换 p, s 是待插入结点, p 在后面仍然表示工作指针.
    DNode *s = p;

    // 第三部分, 插入结点.

    // p 重新作为工作指针, pre 记录其前驱.
    p = (*L)->next, pre = (*L);

    /**
     * 由于双向链表中尾结点的存在, 其频度为 -1, 所以不论存储数据的结点频度为几, 
     * 都可以在链表中找到自己的位置. 否则, 若没有尾结点, 且要插入的结点频度最小,
     * 要链接到表尾, 这此时 p 指向 NULL, 而不是尾结点, 还需要专门判断 p 为空的情
     * 况, 而不能统一地使用一样地插入方法. 有尾结点方便了操作.
     */

    while (p)
    {
        if (s->freq <= p->freq)
        {
            pre = p;
            p = p->next;
        }
        // 找到了合适的位置, 就在 pre  和 p 之间, pre 的频度大于等于 s,
        else
        {
            // 1. 新结点指向后继结点.
            s->next = p;

            // 2. 后继结点指向新结点.
            p->prior = s;

            // 3. 新结点指向前驱结点.
            s->prior = pre;

            // 4. 前驱结点指向新结点.
            pre->next = s;

            break;
        }
    }

    return s;
} // LocateElem_DL2

Status ListInsert_DL(DLinklist *L, int i, ElemType e)
{
    if (i < 1 || i > ListLength_DL(*L) + 1)
    {
        printf("Illegal insertion position.\n");
        return ERROR;
    }

    // 新结点的前驱结点.
    DNode *p = GetElem_DL(*L, i - 1);

    // 这是要插入的结点.
    DNode *s = malloc(sizeof(DNode));
    s->data = e;
    s->freq = 0;

    // 1. 新结点指向后继结点.
    s->next = p->next;

    // 2. 前驱结点指向新结点.
    p->next = s;

    return OK;
} // ListInsert_DL

Status ListDelete_DL(DLinklist *L, int i)
{
    if (i < 1 || i > ListLength_DL(*L))
    {
        printf("Illegal deletion position.\n");
        return ERROR;
    }

    // 被删除结点的前驱结点.
    DNode *p = GetElem_DL(*L, i - 1);

    // 这是要删除的结点.
    DNode *q = p->next;

    // 前驱结点跳过被删除的结点.
    p->next = q->next;

    // 后继结点跳过被删除的结点.
    q->next->prior = p;

    // 删除结点 q.
    free(q);

    return OK;
} // ListDelete_DL

int ListLength_DL(DLinklist L)
{
    int length = 0;
    DNode *p = L->next;

    while (p->data != -1)
    {
        ++length;
        p = p->next;
    }

    return length;
} // ListLength_DL

void PrintList_DL(DLinklist L)
{
    DNode *p = L->next;

    while (p->data != -1)
    {
        printf("%d->", p->data);
        p = p->next;
    }

    printf("\n");

    return;
} // PrintList_DL