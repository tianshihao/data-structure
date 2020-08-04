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
        printf("%d", p->data);

        if (p->next == NULL)
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
} // PrintList_L

void RPrintList_L(Linklist L)
{
    if (L->next != NULL)
    {
        RPrintList_L(L->next); // 递归.
    }
    if (L != NULL)
    {
        printf("%d->", L->data); // 输出函数.
    }
} // RPrintList_L

Linklist Reverse_L1(Linklist L)
{
    LNode *p, *r; // p 为工作指针, r 为 p 得后继, 以防断链.

    p = L->next; // 从第一个元素开始.

    L->next = NULL; // 先将头结点剥离出来.

    while (p != NULL) // 依次将元素摘下.
    {
        r = p->next;       // 暂存 p 的后继.
        p->next = L->next; // 头插法, 插入 p.
        L->next = p;
        p = r;
    }

    return L;
} // Reverse_L1

Linklist Reverse_L2(Linklist L)
{
    // 三个指针, p 为要反转的结点, pre 为 p 前面的结点, r 是保存 p 后继的指针.
    // 初始状态 p 指向第一个元素, r 指向第二个元素.
    LNode *pre, *p = L->next, *r = p->next;

    // 将要第一个结点后继链接断开.
    p->next = NULL;

    // 如果 r 不为空, 三个指针前进一个单位.
    // 否则链表只有一个结点, 直接执行 while 后的 L->next = p.
    // 循环中将 p 反转指向其前面的结点 pre, r 是 p 的后继.
    // 假设链表有 n 个元素, 则循环可将前 n - 1 个元素逆置, 之后 p 指向第 n 个元素,
    while (r != NULL)
    {
        pre = p;
        p = r;
        r = r->next;
        p->next = pre; // 反转.
    }

    L->next = p;

    return L;
} // Reverse_L2

void Sort(Linklist *L)
{
    // pre 指向已经构造好的有序递增链表的尾结点.
    LNode *p = (*L)->next, *pre;
    LNode *r = p->next; // r 用以保存 *p 的后继结点指针.

    // 断开第一个结点的后继, 相当于先构造只有一个结点的有序表.
    p->next = NULL;

    // 这时候之前保存的 r = p->next 就有用了.
    // p 指向后继结点, 第二个结点, 即断开第一个结点的后继后得到的无序表的第一个结点.
    p = r;

    while (p != NULL)
    {
        // 先保存下来, 后面将 p 插入到有序表时会修改 p->next.
        r = p->next;

        // pre 指向有序表头结点.
        pre = (*L);

        // pre 在有序表中遍历, 找到合适的位置.
        // 要么是 pre->next = NULL 的有序表尾结点, 要么是 pre->data < p->data &&
        // pre->next->data >= p->data 的合适的位置.
        while (pre->next != NULL && pre->next->data < p->data)
        {
            pre = pre->next;
        }

        // 将 p 插入到 pre 后.
        p->next = pre->next;
        pre->next = p;

        // 下一个结点.
        p = r;
    }

    return;
} // Sort

Status RangeDelete(Linklist *L, ElemType min, ElemType max)
{
    // p 是检测指针, pr 为其前驱.
    LNode *p = (*L)->next, *pr = (*L);

    // 若当前指针指向的结点不为空.
    while (p != NULL)
    {
        // 比较是否满足删除要求.
        // 若满足,
        if (p->data > min && p->data < max)
        {
            // 前驱 pr 跳过 p.
            pr->next = p->next;

            // 释放 p 所指的内存空间.
            free(p);

            // 使 p 指向新的结点.
            p = pr->next;
        }
        // 否则,
        else
        {
            // pr 和 p 进一.
            pr = p;
            p = p->next;
        }
    }

    return OK;
} // RangeDelete

Linklist Split(Linklist *A)
{
    // 初始化单向链表 B.
    Linklist B = malloc(sizeof(LNode));
    B->next = NULL;

    // 指向 A 和 B 尾结点的指针.
    LNode *ra = (*A);
    LNode *rb = B;

    // p 为工作指针.
    LNode *p = (*A)->next;

    // 原表 A 拆分出头结点.
    (*A)->next = NULL;

    // i 记录 A 中的序号.
    int i = 0;

    while (p != NULL)
    {
        // 序号增加.
        ++i;

        // 偶数.
        if (i % 2 == 0)
        {
            // 新加尾结点.
            rb->next = p;

            // 更新尾结点.
            rb = p;
        }
        // 奇数.
        else
        {
            ra->next = p;
            ra = p;
        }

        // 工作指针前进一.
        p = p->next;
    }

    // 确保尾结点后继为 NULL.
    ra->next = NULL;
    rb->next = NULL;

    return B;
} // Split

Linklist Split2(Linklist *A)
{
    // 初始化单向链表 B.
    Linklist B = malloc(sizeof(LNode));
    B->next = NULL;

    // 指向原表 A 尾结点的指针.
    LNode *ra = (*A);

    // 工作指针.
    LNode *p = (*A)->next;
    // 保存工作指针后继的指针.
    LNode *q;

    // 剥离原表头结点.
    (*A)->next = NULL;

    // 假若 p 是要被分给 A 的结点.
    while (p != NULL)
    {
        // 将 p 链接至 A 表尾, 并更新 ra.
        ra->next = p;
        ra = p;

        // 工作指针前进一, 此时工作指针指向要被分给 B 的结点.
        p = p->next;

        // 如果要分给 B 的结点存在,
        if (p != NULL)
        {
            // 则保存其后继.
            q = p->next;
        }

        // 将工作指针头插入 B 中.
        p->next = B->next;
        B->next = p;

        // 读取工作指针后继, 在下次循环中, 若其不为空, 则应分配给 A.
        p = q;
    }

    // 确保 A 表尾后继正确; 由于 B 是逆序头插入, 所以无须考虑表尾后继指向.
    ra->next = NULL;

    return B;
} // Split2

Status DeleteRepeat(Linklist *L)
{
    // p 为工作指针.
    LNode *p = (*L)->next;

    if (p == NULL)
    {
        return OK;
    }

    while (p->next != NULL)
    {
        // q 指向 p 的后继结点.
        LNode *q = p->next;

        // 如果 p 的下一个结点
        if (p->data == q->data)
        {
            p->next = q->next;
            free(q);
        }
        else
        {
            p = p->next;
        }
    }

    return OK;
} // DeleteRepeat

Linklist MergeList(Linklist *A, Linklist *B)
{
    // 工作指针 pa 和 pb, 指向.
    LNode *pa = (*A)->next, *pb = (*B)->next;

    // 保存 pa 或 pb 的后继.
    LNode *q;

    // 使用 A 作为新链表的头结点.
    (*A)->next = NULL;

    while (pa && pb)
    {
        if (pa->data <= pb->data)
        {
            // 保存 pa 后继.
            q = pa->next;

            // 因为要求是降序, 所以使用头插法, 从最小的元素开始插入.
            pa->next = (*A)->next;
            (*A)->next = pa;

            // 读取后继.
            pa = q;
        }
        else
        {
            q = pb->next;

            pb->next = (*A)->next;
            (*A)->next = pb;

            pb = q;
        }
    }

    // 妙啊, A 和 B 的剩余是互斥的: A 剩余了 B 就不会剩余, 此时让 pb 指向 pa;
    // B 剩余 A 不会剩余, 此时跳过 if.
    if (pa)
    {
        pb = pa;
    }

    while (pb)
    {
        q = pb->next;
        pb->next = (*A)->next;
        (*A)->next = pb;
        pb = q;
    }

    free((*B));

    return (*A);
} // MergeList

Linklist GetCommon(Linklist A, Linklist B)
{
    // 初始化新单向链表 C.
    Linklist C = malloc(sizeof(LNode));
    C->data = -1;
    C->next = NULL;

    // rc 指向 C 尾结点.
    LNode *rc = C;

    // 工作指针.
    LNode *pa = A->next, *pb = B->next;

    while (pa && pb)
    {
        if (pa->data < pb->data)
        {
            pa = pa->next;
        }
        else if (pa->data > pb->data)
        {
            pb = pb->next;
        }
        else
        {
            // 找到了公共结点, 准备一个新结点.
            LNode *s = malloc(sizeof(LNode));
            s->data = pa->data;
            s->next = NULL;

            // 尾插法.
            rc->next = s;
            rc = s;

            // 工作指针前进一.
            pa = pa->next;
            pb = pb->next;
        }
    }

    // rc = NULL;

    return C;
} // GetCommon

Linklist Union(Linklist *A, Linklist *B)
{
    // 工作指针.
    LNode *pa = (*A)->next, *pb = (*B)->next;
    // 回收指针.
    LNode *r = NULL;
    // 指向 A 尾结点. A 用于存储求交集之后的结果, 所以尾结点是头结点.
    LNode *ra = (*A);

    (*A)->next = NULL;

    while (pa && pb)
    {
        if (pa->data < pb->data)
        {
            r = pa;
            pa = pa->next;
            free(r);
        }
        else if (pa->data > pb->data)
        {
            r = pb;
            pb = pb->next;
            free(r);
        }
        else
        {
            // 找到符合要求的结点. 链接到 A 后.
            ra->next = pa;
            ra = pa;

            // pa 前进一.
            pa = pa->next;

            // 释放 pb 内存空间.
            r = pb;
            pb = pb->next;
            free(r);
        }
    }

    // 释放剩余结点的内存.
    while (pa)
    {
        r = pa;
        pa = pa->next;
        free(r);
    }
    while (pb)
    {
        r = pb;
        pb = pb->next;
        free(r);
    }

    // 注意新链表尾结点. 也可以在链接时处理处理后继, 但比较麻烦, 这里一句就行.
    ra->next = NULL;

    // 释放 B 头结点.
    free((*B));

    return (*A);
} // Union

Status Pattern(Linklist A, Linklist B)
{
    // 工作指针.
    LNode *pa = A->next, *pb = B->next;
    // 记录 A 表的比较起点.
    LNode *start = pa;

    while (pa && pb)
    {
        // 匹配, pa 和 pb 共同前进一.
        if (pb->data == pa->data)
        {
            pa = pa->next;
            pb = pb->next;
        }
        // 否则证明至少 A[i] 不是 B 开头, 下一次从 A[i+1] 开始匹配.
        else
        {
            // 更新 A 的比较起点.
            start = start->next;
            pa = start;

            // 重置 B 的比较起点.
            pb = B->next;
        }
    }

    // 若 B 是 A 的连续子序列, 则比较完后 pb 应为 NULL.
    if (pb)
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
} // Pattern

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

// /***************************利用基本操作实现的高级操作**********************/

// // 已知单线性链表 La 和 Lb 的元素按值非递减排列.
// // 归并 La 和 Lb 得到新的单线性链表 Lc, Lc 的元素也按值非线性递减排列.
// Status MergeList_L(Linklist *La,
//                    Linklist *Lb,
//                    Linklist *Lc,
//                    Status (*compare)(ElemType, ElemType))
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
