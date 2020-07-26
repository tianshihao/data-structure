#include <chapter2/linklist.h>

Status InitList_L(Linklist *L)
{
    /**
     * a.   malloc 的返回值类型是 void *,
     *      可以将这个指针转换为申请所需要的任何类型的指针.
     *      e.g. L.head = (LNode *)malloc(sizeof(LNode));
     *      https://www.cnblogs.com/Jummyer/p/9852822.html
     * b.   但又有一篇文章说不要强制类型转换好.
     *      e.g. L->head = malloc(sizeof(LNode));
     *      https://blog.csdn.net/bestone0213/article/details/40829203
     **/

    // 为头结点分配内存空间.
    (*L) = malloc(sizeof(LNode)); // 创建头结点.
    // 内存分配失败.
    if (!(*L))
    {
        exit(OVERFLOW);
    }

    (*L)->data = 0; // 初始为空链表.
    (*L)->next = NULL;

    return OK;
} // InitList_L

Status HeadInsert_L(Linklist *L, ElemType e)
{
    // 创建新结点.
    LNode *s = malloc(sizeof(LNode));

    // 为新结点赋值.
    s->data = e;

    // 1. 新结点指向后继结点.
    s->next = (*L)->next;

    // 2. 前驱结点指向新结点.
    (*L)->next = s;

    return OK;
} // HeadInsert_L

Status TailInsert_L(Linklist *L, ElemType e)
{
    // 这是新结点.
    LNode *s = malloc(sizeof(LNode));
    s->data = e;
    s->next = NULL;

    /**
     * p 存储的是链表中每个结点的地址, 每次使用 p = p->next 会更新 p 为下一个结点
     * 的地址. p 只是一个存储地址的变量, 和原来的链表没有关系, 所以这样做也不会
     * 影响原来的链表. 但是使用 p->next = s, 则会影响原来的链表, 因为 p->next
     * 就是地址 p 指向的内存块中 next 的值, 改变它就是改变原来的链表.
     * 
     * 可以画一个内存块感受一下, 指针存储的是地址, 地址就可以看作是数, 这个数再
     * 怎么运算也不会影响其指向的内存中存储的数据, 除非使用运算符 -> 访问并修改
     * 内存块中的数据.
     */

    // 这是表尾结点, 即新结点的前驱结点.
    LNode *p = (*L);

    // 找到最后一个不为空的结点.
    while (p->next != NULL)
    {
        p = p->next;
    }

    // 将新结点链接到链表尾.
    p->next = s;

    return OK;
} // TailInsert

LNode *GetElem_L(Linklist L, int i)
{
    if (i < 0 || i > ListLength_L(L))
    {
        printf("索引越界\n");
        return NULL;
    }

    int counter = 0;
    LNode *p = L;

    // 从第一个结点开始找, 查找第 i 个结点.
    while (p && counter < i)
    {
        p = p->next;
        ++counter;
    }

    return p;
} // GetElem_L

LNode *LocateElem_L(Linklist L, ElemType e)
{
    LNode *p = L->next;

    while (p && p->data != e)
    {
        p = p->next;
    }

    return p;
} // LocateElem_L

Status ListInsert_L(Linklist *L, int i, ElemType e)
{
    if (i < 1 || i > ListLength_L(*L) + 1)
    {
        printf("插入位置非法\n");
        return ERROR;
    }

    // 新结点的前驱结点.
    LNode *p = GetElem_L(*L, i - 1);

    // 这是要插入的结点.
    LNode *s = malloc(sizeof(LNode));
    s->data = e;

    // 1. 新结点指向后继结点.
    s->next = p->next;

    // 2. 前驱结点指向新结点.
    p->next = s;

    return OK;
} // ListInsert_L

Status ListDelete_L(Linklist *L, int i)
{
    if (i < 1 || i > ListLength_L(*L))
    {
        printf("删除位置非法\n");
        return ERROR;
    }

    // 被删除结点的前驱结点.
    LNode *p = GetElem_L(*L, i - 1);

    // 这是要删除的结点.
    LNode *q = p->next;

    // 前驱结点跳过被删除的结点.
    p->next = q->next;

    // 删除结点 q.
    free(q);

    return OK;
} // ListDelete_L

int ListLength_L(Linklist L)
{
    int length = 0;
    LNode *p = L->next;

    while (p)
    {
        ++length;
        p = p->next;
    }

    return length;
} // ListLength

void PrintList_L(Linklist L)
{
    LNode *p = L->next;

    while (p != NULL)
    {
        printf("%d->", p->data);
        p = p->next;
    }

    return;
} // PrintList_L

// Status MakeNode(Link *p, ElemType e)
// {
//     (*p) = malloc(sizeof(LNode));

//     if ((*p) == NULL)
//     {
//         printf("内存分配失败\n");
//         return ERROR;
//     }

//     (*p)->data = e;
//     (*p)->next = NULL;

//     return OK;
// }

/**
 * * 指针传递 *
 * 此处传递的其实是指针, 在定义形参的时候, 声明这个参数是指针类型.
 * 在使用函数时, 应在实参左侧加 &, 表示传递实参的地址.
 * e.g.
 * int main()
 * {
 *      ...
 *      Linklist my_list;
 *      InitList_L(&my_list);
 *      ...
 * }
 * 变量的地址传递给指针变量形参之后就可以用形参指向变量,
 * 修改主函数中的变量了, 不同于值传递的形参复制一份实参.
 */

// // 依次对 L 的每个元素调用函数 visit(). 一旦 visit() 失败, 则操作失败.
// Status ListTraverse(Linklist L, Status (*visit)(ElemType))
// {
//     Link visiting = L.head->next;

//     while ((visiting != NULL) && ((*visit)(visiting->data)))
//         visiting = visiting->next;

//     if (visiting != NULL)
//         return FALSE;

//     return OK;
// } // ListTraverse

// /***************************利用基本操作实现的高级操作******************************/

// // 已知单线性链表 La 和 Lb 的元素按值非递减排列.
// // 归并 La 和 Lb 得到新的单线性链表 Lc, Lc 的元素也按值非线性递减排列.
// Status MergeList_L(Linklist *La, Linklist *Lb, Linklist *Lc, Status (*compare)(ElemType, ElemType))
// {
//     // 存储空间分配失败
//     if (!InitList_L(Lc))
//         return ERROR;

//     // ha 和 hb 分别指向 La 和 Lb 的头结点
//     Link ha = GetHead((*La));
//     Link hb = GetHead((*Lb));

//     // pa 和 pb 分别指向 La 和 Lb 中当前结点
//     Link pa = NextPos(*La, ha);
//     Link pb = NextPos(*Lb, hb);

//     // La 和 Lb 均为非空
//     while ((pa) && (pb))
//     {
//         // a 和 b 为两表中当前比较元素
//         ElemType a = GetCurElem(pa);
//         ElemType b = GetCurElem(pb);

//         // a <= b
//         if ((*compare)(a, b) <= 0)
//         {
//             Link ptr;
//             DelFirst(ha, &ptr);
//             Append(Lc, ptr);
//             pa = NextPos(*La, ha);
//         }
//         // a > b
//         else
//         {
//             Link ptr;
//             DelFirst(hb, &ptr);
//             Append(Lc, ptr);
//             pb = NextPos(*Lb, hb);
//         }
//     } // while

//     if (pa) // 链表 La 中剩余结点
//         Append(Lc, pa);
//     else // 链表 Lb 中剩余结点
//         Append(Lc, pb);

//     FreeNode(&ha);
//     FreeNode(&hb);

//     return OK;
// } // MergeList_L
