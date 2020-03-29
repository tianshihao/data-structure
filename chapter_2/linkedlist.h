/************************
 * @file  : linkedlist.h
 * @brief : 单向链表
 * @author: 田世豪
 * @date  : 2020-1-25
 * *********************/

#pragma once

#include "predefconst.h"

// 省事写法
// 实例化结构体语句
// Link my_struct

// 结点类型
typedef struct LNode
{
    ElemType data;
    struct LNode *next;
} LNode, *Link, *Position;

// 链表类型
typedef struct LinkedList
{
    Link head;
    Link tail;
    int len;
} LinkedList;

// 传统写法
// 实例化结构体语句
// struct LNode my_struct

// // 结点类型
// struct LNode
// {
//     ElemType data;
//     struct LNode *next;
// };

// // 链表类型
// struct LinkedList
// {
//     struct LNode *head, *tail;
//     int len;
// };

// 分配由 p 指向的值为 e 的结点, 并返回 OK,
// 若分配失败, 则返回 ERROR.
Status MakeNode(Link *p, ElemType e)
{
    (*p) = malloc(sizeof(LNode));

    if ((*p) == NULL)
    {
        printf("内存分配失败\n");
        return ERROR;
    }

    (*p)->data = e;
    (*p)->next = NULL;

    return OK;
}

// 释放 p 所指向的结点.
void FreeNode(Link *p)
{
    free(*p);

    return;
} // FreeNode

/*******************************************************************************
 * * 指针传递 *
 * 此处传递的其实是指针, 在定义形参的时候, 声明这个参数是指针类型.
 * 在使用函数时, 应在实参左侧加 &, 表示传递实参的地址.
 * e.g.
 * int main()
 * {
 *      ...
 *      LinkedList my_list;
 *      InitList(&my_list);
 *      ...
 * }
 * 变量的地址传递给指针变量形参之后就可以用形参指向变量,
 * 修改主函数中的变量了, 不同于值传递的形参复制一份实参.
 * ****************************************************************************/

// 构造一个空的线性链表 L.
Status InitList(LinkedList *list)
{
    /***************************************************************************
     * a.   malloc 的返回值类型是 void *,
     *      可以将这个指针转换为申请所需要的任何类型的指针.
     *      e.g. list.head = (LNode *)malloc(sizeof(LNode));
     *      https://www.cnblogs.com/Jummyer/p/9852822.html
     * b.   但又有一篇文章说不要强制类型转换好.
     *      e.g. list->head = malloc(sizeof(LNode));
     *      https://blog.csdn.net/bestone0213/article/details/40829203
     * ************************************************************************/

    list->head = malloc(sizeof(LNode));

    if (list->head == NULL)
    {
        printf("申请内存失败\n");
        return ERROR;
    }

    // 初始化头结点数据
    list->head->data = -1;
    list->head->next = NULL;
    list->tail       = list->head;
    list->len        = 0;

    return OK;
} // InitList

// 销毁线性链表 L, L 不再存在.
Status DestoryList(LinkedList *L)
{
    while (L->head != NULL)
    {
        // 定位当前头结点
        Link ptr = L->head;

        // 移动头结点
        L->head = L->head->next;

        // 释放头结点
        FreeNode(&ptr);
    } // while

    return OK;
} // DestoryList

// 将线性链表 L 重置为空表, 并释放原链表的结点空间,
// 保留头结点.
Status ClearList(LinkedList *L)
{
    Link ptr = L->head->next;

    while (ptr != NULL)
    {
        Link next_ptr = ptr;

        ptr = ptr->next;

        FreeNode(&next_ptr);
    } // while

    // 重置长度为 0
    L->len = 0;

    // 重置头结点下一个结点为空
    L->head->next = NULL;

    // 别望了重置尾指针
    L->tail = L->head;
    return OK;
} // ClearList

// 已知 h 指向线性链表的头结点, 将 s 所指结点插入在第一个结点之前.
Status InsFirst(Link h, Link s)
{
    // 前插法
    s->next = h->next;
    h->next = s;

    return OK;
} // InsFirst

// 已知 h 指向线性链表的头结点, 删除链表中的一个结点并以 q 返回.
Status DelFirst(Link h, Link *q)
{
    // q 返回第一个结点
    (*q) = h->next;

    // h 是指向头结点指针的指针
    h->next = h->next->next;

    // 新结点没有后继结点
    (*q)->next = NULL;

    return OK;
} // DelFirst

// 将指针 s 所指的一串结点链接在线性链表 L 的最后一个结点,
// 之后, 并改变链表 L 的尾指针指向新的尾结点.
Status Append(LinkedList *L, Link s)
{
    Link ptr = L->head;

    // 找到线性链表 L 的最后一个结点
    while (ptr->next != NULL)
        ptr = ptr->next;

    // 将指针 s 所指的一串结点链接在线性链表 L 的最后一个结点
    ptr->next = s;

    // 找到新线性链表 L 的最后一个结点
    while (ptr->next != NULL)
        ptr = ptr->next;

    // 改变链表 L 的尾指针指向新的尾指针
    L->tail = ptr;

    return OK;
}

// 删除线性链表 L 中的尾结点, 并以 q 返回, 改变链表 L 的尾指针指向新的尾结点.
Status Remove(LinkedList *L, Link *q)
{
    Link ptr = L->head;

    while (ptr->next != L->tail)
        ptr = ptr->next;

    // 改变尾指针的指向
    L->tail = ptr;

    // q 为 (Link) * 类型指针,
    // 即指向 Link 的指针,
    // (*q) 为 Link 类型指针.
    (*q)->data = ptr->next->data;
    (*q)->next = NULL;

    ptr->next = NULL;

    return OK;
} // Remove

// 已知 p 指向线性链表 L 中的一个结点, 将 s 所指结点插入在 p 所指结点之前,
// 并修改指针 p 指向新插入的结点.
// TODO 有待修复一个结点重复插入两次会出现链表闭环的bug.
Status InsBefore(LinkedList *L, Link *p, Link s)
{
    Link before_p = L->head;

    // 找到结点 p 之前的结点
    while (before_p->next != (*p))
        before_p = before_p->next;

    /*******************************
     * 若修改指针指向的内容, 直接传递指针
     * 若修改指针本身, 传递指针的地址
     * ****************************/

    // 将 s 所指的指针插入在 p 所指的结点之前
    s->next = before_p->next;
    before_p->next = s;

    // 并修改指针 p 指向新插入的结点 s
    (*p) = s;

    return OK;
} // InsBefore

// 已知 p 指向线性链表 L 中的一个结点, 将 s 所指结点插入在 p 所指结点之后,
// 并修改指针 p 指向新插入的结点.
// TODO 若在头结点后插入, 则会丧失头结点, 因为头结点会指向新结点 s,
// TODO 导致原来的头结点成为野结点.
Status InsAfter(LinkedList *L, Link *p, Link s)
{
    // 将 s 所指的指针插入在 p 所指的结点之后
    s->next = (*p)->next;
    (*p)->next = s;

    // 并修改指针 p 指向新插入的结点 s
    (*p) = s;

    return OK;
} // InsAfter

// 已知 p 指向线性链表中的一个结点, 用 e 更新 p 所指结点中数据元素的值.
Status SetCurElem(Link p, ElemType e)
{
    p->data = e;

    return OK;
} // SetCurElem

// 已知 p 指向线性链表中的一个结点, 返回 p 所指结点中数据元素的值.
ElemType GetCurElem(Link p)
{
    return p->data;
} // GetCurElem

// 若线性链表 L 为空表, 则返回 TRUE, 否则返回 FALSE.
Status ListEmpty(LinkedList L)
{
    if (L.head->next == NULL)
        return TRUE;
    return FALSE;
} // ListEmpty

// 返回线性链表 L 中的元素个数.
// 不包括头结点.
int ListLength(LinkedList L)
{
    int len = 0;
    Link ptr = L.head;

    while (ptr->next != NULL)
    {
        ptr = ptr->next;
        ++len;
    } // while

    return len;
} // ListLength

// 返回线性链表 L 中头结点的位置.
Position GetHead(LinkedList L)
{
    return L.head;
} // GetHead

// 返回线性链表 L 中最后一个结点的位置.
Position GetLast(LinkedList L)
{
    return L.tail;
} // GetLast

// 已知 p 指向线性链表 L 中的一个结点, 返回 p 所指结点的直接前驱的位置.
Position PriorPos(LinkedList L, Link p)
{
    Link prior_position = L.head;

    while (prior_position->next != p)
        prior_position = prior_position->next;

    return prior_position;
} // PriorPos

// 已知 p 指向线性链表 L 中的一个结点, 返回 p 所指结点的直接后继的位置.
Position NextPos(LinkedList L, Link p)
{
    return p->next;
} // NextPos

// 返回 p 指示线性链表 L 中第 i 个结点的位置并返回 OK, i 值不合法时返回 ERROR.
Status LocatePos(LinkedList L, int i, Link *p)
{
    if ((i < 0) || (i > ListLength(L)))
        return ERROR;

    (*p) = L.head;

    for (int j = 0; j < i; ++j)
        (*p) = (*p)->next;

    return OK;
} // LocatePos

// 返回线性链表 L 中第 1 个与 e 满足函数 compare() 判定关系的元素的位置,
// 若不存在这样的元素, 返回 NULL.
Position LocateElem(LinkedList L, ElemType e, Status (*compare)(ElemType, ElemType))
{
    Link wanted = L.head->next;

    while ((wanted != NULL) && (!(*compare)(wanted->data, e)))
        wanted = wanted->next;

    if (wanted == NULL)
        return NULL;

    return wanted;
} // LocateElem

// 依次对 L 的每个元素调用函数 visit(). 一旦 visit() 失败, 则操作失败.
Status ListTraverse(LinkedList L, Status (*visit)(ElemType))
{
    Link visiting = L.head->next;

    while ((visiting != NULL) && ((*visit)(visiting->data)))
        visiting = visiting->next;

    if (visiting != NULL)
        return FALSE;

    return OK;
} // ListTraverse

/***************************利用基本操作实现的高级操作******************************/

// 在线性链表 L 第 i 个元素之前插入数据元素 e
Status ListInsert_L(LinkedList *L, int i, ElemType e)
{
    Link ptr;

    // 获取第 i - 1 个结点的位置, 并将其返回给 ptr
    if (!LocatePos(*L, i - 1, &ptr))
        return ERROR;

    Link new_node;

    if (!MakeNode(&new_node, e))
        return ERROR;

    // 对于要新插入的结点, ptr 是它的头结点,
    // ptr 会被插入到 ptr 之后.
    InsFirst(ptr, new_node);

    return OK;
} // ListInsert_L

// 已知单线性链表 La 和 Lb 的元素按值非递减排列.
// 归并 La 和 Lb 得到新的单线性链表 Lc, Lc 的元素也按值非线性递减排列.
Status MergeList_L(LinkedList *La, LinkedList *Lb, LinkedList *Lc, Status (*compare)(ElemType, ElemType))
{
    // 存储空间分配失败
    if (!InitList(Lc))
        return ERROR;

    // ha 和 hb 分别指向 La 和 Lb 的头结点
    Link ha = GetHead((*La));
    Link hb = GetHead((*Lb));

    // pa 和 pb 分别指向 La 和 Lb 中当前结点
    Link pa = NextPos(*La, ha);
    Link pb = NextPos(*Lb, hb);

    // La 和 Lb 均为非空
    while ((pa) && (pb))
    {
        // a 和 b 为两表中当前比较元素
        ElemType a = GetCurElem(pa);
        ElemType b = GetCurElem(pb);

        // a <= b
        if ((*compare)(a, b) <= 0)
        {
            Link ptr;
            DelFirst(ha, &ptr);
            Append(Lc, ptr);
            pa = NextPos(*La, ha);
        }
        // a > b
        else
        {
            Link ptr;
            DelFirst(hb, &ptr);
            Append(Lc, ptr);
            pb = NextPos(*Lb, hb);
        }
    } // while

    if (pa) // 链表 La 中剩余结点
        Append(Lc, pa);
    else // 链表 Lb 中剩余结点
        Append(Lc, pb);

    FreeNode(&ha);
    FreeNode(&hb);

    return OK;
} // MergeList_L

// 打印链表数据.
void PrintList(LinkedList L)
{
    if (L.head->next == NULL)
    {
        printf("list is empty\n");
        return;
    }

    for (Link ptr = L.head->next; ptr != NULL; ptr = ptr->next)
        printf(" %d ", ptr->data);
    printf("\n");

    return;
} // PrintList
