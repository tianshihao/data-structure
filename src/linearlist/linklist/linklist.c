/**
 * @file linklist.c
 * @author 田世豪 (tianshihao@4944@126.com)
 * @brief 单向链表方法实现.
 * @version 0.2
 * @date 2020-12-16
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <linearlist/linklist/linklist.h>

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

    /* 为头结点分配内存空间. */
    (*L) = malloc(sizeof(LNode));
    /* 内存分配失败. */
    if (!(*L))
    {
        exit(OVERFLOW);
    }

    /* 为头结点赋值. */
    (*L)->data = 0;
    (*L)->next = NULL;

    return OK;
}

Status HeadInsert_L(Linklist L, ElemType e)
{
    /* 创建新结点. */
    LNode *s = malloc(sizeof(LNode));

    /* 为新结点赋值. */
    s->data = e;

    /* 1. 新结点指向后继结点. */
    s->next = L->next;

    /* 2. 头结点指向新结点. */
    L->next = s;

    return OK;
}

Status TailInsert_L(Linklist L, ElemType e)
{
    /* 这是新结点. */
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

    /* 工作指针, 指向表尾结点, 即新结点的前驱结点. */
    LNode *p = L;

    /* 找到最后一个不为空的结点. */
    while (p->next != NULL)
    {
        p = p->next;
    }

    /* 将新结点链接到链表尾. */
    p->next = s;

    return OK;
}

LNode *GetElem_L(Linklist L, int i)
{
    if (i < 0 || i > ListLength_L(L))
    {
        printf("Index out of range.\n");
        return NULL;
    }

    /* 计数器. */
    int counter = 0;
    /* 工作指针, 初始指向头结点.  */
    LNode *p = L;

    /* 从第一个结点开始找, 查找第 i 个结点. */
    while (p && counter < i)
    {
        p = p->next;
        ++counter;
    }

    /* 返回目标结点指针. */
    return p;
}

LNode *LocateElem_L(Linklist L, ElemType e)
{
    /* 工作指针, 指向第一个结点. */
    LNode *p = L->next;

    /* 循环查找数据为 e 的结点. */
    while (p && p->data != e)
    {
        p = p->next;
    }

    /* 返回目标结点指针. */
    return p;
}

Status ListInsert_L(Linklist L, int i, ElemType e)
{
    if (i < 1 || i > ListLength_L(L) + 1)
    {
        printf("Illegal insertion position.\n");
        return ERROR;
    }

    /* 新结点的前驱结点. */
    LNode *p = GetElem_L(L, i - 1);

    /* 这是要插入的结点. */
    LNode *s = malloc(sizeof(LNode));
    s->data = e;

    /* 1. 新结点指向后继结点. */
    s->next = p->next;

    /* 2. 前驱结点指向新结点. */
    p->next = s;

    return OK;
}

Status ListDelete_L(Linklist L, int i)
{
    if (i < 1 || i > ListLength_L(L))
    {
        printf("Illegal deletion position.\n");
        return ERROR;
    }

    /* 被删除结点的前驱结点. */
    LNode *p = GetElem_L(L, i - 1);

    /* 这是要删除的结点. */
    LNode *q = p->next;

    /* 前驱结点跳过被删除的结点. */
    p->next = q->next;

    /* 删除结点 q. */
    free(q);

    return OK;
}

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
}

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
}

void RPrintList_L(Linklist L)
{
    if (L->next != NULL)
    {
        /* 递归. */
        RPrintList_L(L->next);
    }
    if (L != NULL)
    {
        /* 输出函数. */
        printf("%d->", L->data);
    }
}

void Reverse_L1(Linklist L)
{
    /* p 为工作指针, r 为 p 的后继, 以防断链. */
    LNode *p, *r;

    /* 从第一个元素开始. */
    p = L->next;

    /* 先将头结点剥离出来. */
    L->next = NULL;

    /* 依次将元素摘下. */
    while (p != NULL)
    {
        /* 暂存 p 的后继. */
        r = p->next;
        /* 用头插法插入 p. */
        p->next = L->next;
        L->next = p;
        /* 更新 p, 指向下一个结点. */
        p = r;
    }

    return;
}

void Reverse_L2(Linklist L)
{
    /**
     * 三个指针, p 为要反转的结点, pre 为 p 前面的结点, r 是保存 p 后继的指针.
     * 初始相当于 pre 指向第 0 个结点, p 指向第 1 个结点, 即结点对(0, 1).
     * 从结点对 (1, 2) 开始操作.
     */
    LNode *pre = L, *p = L->next, *r = p->next;

    /**
     * 将要第一个结点后继链接断开. 因为它将成为逆置后链表的最后一个结点, 否则
     * 将在逆置后的链表中的最后一个元素和倒数第二个元素之间形成环.
     */
    p->next = NULL;

    /**
     * 如果 r 不为空, 三个指针前进一个单位.
     * 否则链表只有一个结点, 直接执行 while 后的 L->next = p.
     * 循环中将 p 反转指向其前面的结点 pre, r 是 p 的后继.
     * 假设链表有 n 个元素, 则循环可将前 n - 1 个元素逆置,
     * 之后 p 指向第 n 个元素.
     */
    /**
     * 用  0->1->...->n 表示一个链表, 其中 0 为头结点, 1 为第一个结点, 以此类推.
     * 和方法一的一次摘一个结点不同, 方法一工作(操作)对象是一个结点, 只有一个工作
     * 指针 p 和保存其后继的指针 r. 而方法二中的工作指针是一对指针和存储其后继的指针.
     * 例如 (3->4)->5, pre 指向 3, p 指向 4, p 和 pre 是一对工作指针, r 指向其后继 5.
     * 将3->4变成3<-4, 即 p->next = pre, (3<-4)->5, r 不为空, while 循环 3 个指针进一,
     * 变成了3<-(4->5), pre 指向 4, p 指向 5, r 指向 NULL, 然后 p->next = pre,
     * 变成了3<-4<-5; while 循环, r 指向空, 循环结束. 显然此时工作指针 p 指向
     * 最后一个结点, 再将头结点 L 指向 p 即可, 即 L->next = p.
     */
    /**
     * 若结点对存在后继.
     */
    while (r != NULL)
    {
        /* 指针依次进一. */
        pre = p;
        p = r;
        /* 更新后继.*/
        r = r->next;
        /* 逆置. */
        p->next = pre;
    }

    /* 头结点指向逆置之后的第一个结点. 此时 p 指向的结点是原链表的最后一个结点.*/
    L->next = p;

    return;
}

void Sort(Linklist L)
{
    /* pre 指向已经构造好的有序递增链表的尾结点. */
    LNode *p = L->next, *pre;
    /*  r 用以保存 *p 的后继结点指针. */
    LNode *r = p->next;

    /* 断开第一个结点的后继, 相当于先构造只有一个结点的有序表. */
    p->next = NULL;

    /**
     * 这时候之前保存的 r = p->next 就有用了. 指向后继结点, 第二个结点,
     * 即断开第一个结点的后继后得到的无序表的第一个结点.
     */
    p = r;

    /* p 不为空, 即链表至少有两个结点需要排序. */
    while (p != NULL)
    {
        /* 先保存下来, 后面将 p 插入到有序表时会修改 p->next. */
        r = p->next;

        /* pre 指向链表头结点. */
        pre = L;

        /**
         * pre 在有序表中遍历, 找到合适的位置.
         * 要么是 pre->next = NULL 的有序表尾结点, 要么是 pre->data < p->data &&
         * pre->next->data >= p->data 的合适的位置.
         */
        while (pre->next != NULL && pre->next->data < p->data)
        {
            pre = pre->next;
        }

        /* 将 p 插入到 pre 后. */
        p->next = pre->next;
        pre->next = p;

        /* 下一个结点. */
        p = r;
    }

    return;
}

Status RangeDelete(Linklist L, ElemType min, ElemType max)
{
    /* p 是检测指针, pr 为其前驱. */
    LNode *p = L->next, *pre = L;

    /* 若当前指针指向的结点不为空. */
    while (p != NULL)
    {
        /* 若满足删除要求. */
        if (p->data > min && p->data < max)
        {
            /* 前驱 pre 跳过 p. */
            pre->next = p->next;

            /* 释放 p 所指的内存空间. */
            free(p);

            /* 使 p 指向新的结点. */
            p = pre->next;
        }
        /* 否则, */
        else
        {
            /* pre 和 p 进一. */
            pre = p;
            p = p->next;
        }
    }

    return OK;
}

Linklist Split(Linklist A)
{
    /* 初始化单向链表 B. */
    Linklist B = malloc(sizeof(LNode));
    B->next = NULL;

    /**
     * 指向 A 和 B 尾结点的指针, 初始指向头结点. 由于要求相对位置保持不变,
     * 链表 A 和 B 都使用尾插法. 
     */
    LNode *rA = A;
    LNode *rB = B;

    /* p 为工作指针. */
    LNode *p = A->next;

    /* 原表 A 拆分出头结点. */
    A->next = NULL;

    /* i 记录 A 中的序号. */
    int i = 0;

    while (p != NULL)
    {
        /* 序号增加. */
        ++i;

        /* 偶数. */
        if (i % 2 == 0)
        {
            /* 新加尾结点. */
            rB->next = p;

            /* 更新尾结点. */
            rB = p;
        }
        /* 奇数. */
        else
        {
            rA->next = p;
            rA = p;
        }

        /* 工作指针前进一. */
        p = p->next;
    }

    /* 确保尾结点后继为 NULL. */
    rA->next = NULL;
    rB->next = NULL;

    return B;
}

Linklist Split2(Linklist A)
{
    /* 初始化单向链表 B. */
    Linklist B = malloc(sizeof(LNode));
    B->next = NULL;

    /* 指向原表 A 尾结点的指针. */
    LNode *rA = A;

    /* 工作指针. */
    LNode *p = A->next;
    /* 保存工作指针后继的指针. */
    LNode *q;

    /* 剥离原表头结点. */
    A->next = NULL;

    /* 假若 p 是要被分给 A 的结点. */
    while (p != NULL)
    {
        /* 将 p 链接至 A 表尾, 并更新 rA. */
        rA->next = p;
        rA = p;

        /* 工作指针前进一, 此时工作指针指向要被分给 B 的结点. */
        p = p->next;

        /* 如果要分给 B 的结点存在, */
        if (p != NULL)
        {
            /* 则保存其后继. */
            q = p->next;
        }

        /* 将工作指针头插入 B 中. */
        p->next = B->next;
        B->next = p;

        /* 读取工作指针后继, 在下次循环中, 若其不为空, 则应分配给 A. */
        p = q;
    }

    /* 确保 A 表尾后继正确; 由于 B 是逆序头插入, 所以无须考虑表尾后继指向. */
    rA->next = NULL;

    return B;
}

Status DeleteRepeat(Linklist L)
{
    /* p 为工作指针. */
    LNode *p = L->next;

    if (p == NULL)
    {
        return OK;
    }

    while (p->next != NULL)
    {
        /* q 指向 p 的后继结点. */
        LNode *q = p->next;

        /* 如果 p 的下一个结点 q 和 p 的数据重复. */
        if (p->data == q->data)
        {
            /* 结点 p 的指针跳过结点 q. */
            p->next = q->next;
            /* 释放分配给结点 q 的内存空间. */
            free(q);
        }
        /* 数据不重复. */
        else
        {
            p = p->next;
        }
    }

    return OK;
}

Linklist MergeList(Linklist A, Linklist B)
{
    /* 工作指针 pA 和 pB, 分别指向两个链表的第一个结点. */
    LNode *pA = A->next, *pB = B->next;

    /* 指针 r 用以保存 pA 或 pB 的后继. */
    LNode *r;

    /* 把链表 A 的头结点剥离出来, 作为新链表的头结点. */
    A->next = NULL;

    while (pA && pB)
    {
        if (pA->data <= pB->data)
        {
            /* 保存 pA 后继. */
            r = pA->next;

            /* 因为要求是降序, 所以使用头插法, 从最小的元素开始插入. */
            pA->next = A->next;
            A->next = pA;

            /* 读取后继. */
            pA = r;
        }
        else
        {
            /* 保存后继. */
            r = pB->next;

            /* 将 pB 指向的结点头插入链表 A 中. */
            pB->next = A->next;
            A->next = pB;

            /* 读取后继. */
            pB = r;
        }
    }

    /**
     * 妙啊, A 和 B 的剩余是互斥的: A 剩余了 B 就不会剩余, 此时让 pB 指向 pA,
     * 转化为 B 剩余. 而 B 剩余 A 不会剩余, 此时跳过 if.
     */
    if (pA)
    {
        pB = pA;
    }

    /* 总是 B 剩余. */
    while (pB)
    {
        /* 保存后继. */
        r = pB->next;

        /* 将 pB 指向的结点头插入链表 A 中. */
        pB->next = A->next;
        A->next = pB;

        /* 读取后继. */
        pB = r;
    }

    /* 释放链表 B 的头结点, B 被销毁. */
    free(B);

    return A;
}

Linklist GetCommon(Linklist A, Linklist B)
{
    /* 初始化新单向链表 C. */
    Linklist C = malloc(sizeof(LNode));
    C->data = -1;
    C->next = NULL;

    /* rC 指向 C 尾结点. */
    LNode *rC = C;

    /* 工作指针, 指向链表 A 和 B 的第一个结点. */
    LNode *pA = A->next, *pB = B->next;

    while (pA && pB)
    {
        /* pA, pB 相互追赶, 直到 pA->data = pB->data. */
        if (pA->data < pB->data)
        {
            pA = pA->next;
        }
        else if (pA->data > pB->data)
        {
            pB = pB->next;
        }
        else
        {
            /* 找到了公共结点, 准备一个新结点. */
            LNode *s = malloc(sizeof(LNode));
            s->data = pA->data;
            s->next = NULL;

            /* 尾插法. */
            rC->next = s;
            rC = s;

            /* 工作指针前进一. */
            pA = pA->next;
            pB = pB->next;
        }
    }

    return C;
}

void Union(Linklist A, Linklist B)
{
    /* 工作指针. */
    LNode *pA = A->next, *pB = B->next;
    /* 回收指针. */
    LNode *r = NULL;
    /* 指向 A 尾结点. A 用于存储求交集之后的结果, 所以初始尾结点是头结点. */
    LNode *rA = A;

    /* 剥离链表 A 的头结点. 目的链表 A 的头结点作为新链表的头结点. */
    A->next = NULL;

    while (pA && pB)
    {
        /* 异步前进, 相互追赶. 释放不属于交集的结点. */
        if (pA->data < pB->data)
        {
            /* 记录待回收结点. */
            r = pA;
            /* 指针进一. */
            pA = pA->next;

            /* 回收先前的结点. */
            free(r);
        }
        else if (pA->data > pB->data)
        {
            r = pB;
            pB = pB->next;
            free(r);
        }
        else
        {
            /* 找到符合要求的结点. 链接到 A 后. 尾插法. */
            rA->next = pA;
            rA = pA;

            /* pA 前进一. */
            pA = pA->next;

            /**
             * pB 也前进一, 因为要销毁链表 B, 所以用指针 r 指向 pB 指向的结点,
             * pB再前进一.
             */
            r = pB;
            pB = pB->next;

            /* 释放不属于交集的结点. */
            free(r);
        }
    }

    /* 如果 A 和 B 不一样长, 释放剩余结点的内存. */
    while (pA)
    {
        r = pA;
        pA = pA->next;
        free(r);
    }
    while (pB)
    {
        r = pB;
        pB = pB->next;
        free(r);
    }

    /* 注意新链表尾结点. 也可以在链接时处理处理后继, 但比较麻烦, 这里一句就行. */
    rA->next = NULL;

    /* 释放 B 头结点. */
    free(B);

    return;
}

Status Pattern(Linklist A, Linklist B)
{
    /* 工作指针. */
    LNode *pA = A->next, *pB = B->next;
    /* 记录 A 表的比较起点. 从 A 的第一个结点匹配 B. */
    LNode *start = pA;

    while (pA && pB)
    {
        /* 匹配, pA 和 pB 共同前进一. */
        if (pB->data == pA->data)
        {
            pA = pA->next;
            pB = pB->next;
        }
        /* 否则证明至少 A[i] 不是 B 开头, 下一次从 A[i+1] 开始匹配. */
        else
        {
            /* 更新 A 的比较起点. 从下一个结点开始匹配 B. */
            start = start->next;
            /* 更新工作指针. */
            pA = start;

            /* 重置 B 的比较起点. */
            pB = B->next;
        }
    }

    /* 若 B 是 A 的连续子序列, 则比较完后 pB 应为 NULL. */
    if (pB)
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

Status SearchK(Linklist L, int k)
{
    /* p 和 q 均为工作指针, 指向第一个结点. */
    LNode *p = L->next, *q = L->next;

    /* 计数器. 由于 p 和 q 指向第一个结点, 故计数器从 1 开始计数. */
    int count = 1;

    /**
     * 指针 p 前进 k 个单位, 指向第 k+1 个位置, 之后 p 和 q 同时前进, 直到 p
     * 指向表尾, 即 p 和 q 同步前进 n-k-1 次, 这样 q 会处于在正数第 1+(n-k-1),
     * 倒数第 n-(n-k)=k 个结点上. 具体实现还要注意计数器的计数是从 0 开始还是
     * 从 1 开始, 小于还是小于等于.
     */

    while (p)
    {
        /**
         * 从 1 开始计数, 让 p 前进 k 次, 即 p 指向第 k + 1 个结点. p 之后的结点
         * 还有 n - k - 1 个, p 还可以前进 n - k - 1 次.
         */
        if (count <= k)
        {
            ++count;
            p = p->next;
        }
        /* 然后 q 前进 n-k-1 次, 指向正数第 n-k 个结点, 即倒数第 k 个. */
        else
        {
            p = p->next;
            q = q->next;
        }
    }

    /* 1 <= count <= length, 若 count <= k, 则表示 length <= k, k 越界. */
    if (count <= k)
    {
        return FALSE;
    }
    else
    {
        printf("the %dth element from the bottom is %d.\n", k, q->data);
        return TRUE;
    }
}

LNode *FindLoopStart(Linklist L)
{
    /* 设置快慢指针. */
    LNode *fast = L, *slow = L;

    while (slow != NULL && fast->next != NULL)
    {
        slow = slow->next;
        fast = fast->next->next;

        /* 快慢指针相遇. */
        if (slow == fast)
        {
            break;
        }
    }

    /* 没有环, 返回 NULL. */
    if (slow == NULL || fast->next == NULL)
    {
        return NULL;
    }

    /**
     * 假设环长为 r, 头结点到环的入口点的距离为 a, 环的入口点沿着环的方向到相遇
     * 点的距离为 x, 相遇时 fast 绕过了 n 圈, 则 2(a+x)=a+n*r+x.
     * 解得 a = n * r - x, 即头结点到环的入口点的距离为 n 倍环长减去环的入口点到
     * 相遇点的距离, 当 n == 1, 时, a = r - x, r - x 为相遇点继续沿着环的方向到
     * 相遇点的距离. 因此, 可令 p1, p2 分别指向头结点和相遇点, 共同前进 r - x,
     * p1 和 p2 就会在入口点相遇, p1 == p2.
     */

    /* p1 指向开始点, p2 指向相遇点. */
    LNode *p1 = L, *p2 = slow;
    while (p1 != p2)
    {
        p1 = p1->next;
        p2 = p2->next;
    }

    return p1;
}

Status ChangeList(Linklist L)
{
    /* 1. 找出链表 L 的中间结点. */

    /* 设置工作指针 p 和 q. */
    LNode *p = L, *q = L, *r = NULL;

    /**
     * 找到了中间结点 p, p 步长为 1, q 步长为 2, q 到达表尾时, p 正好是中间结点.
     * 若结点数量为偶数, 则 p 指向第 n / 2 - 1 个结点, 前后等长;
     * 若结点数量为奇数, 则 p 指向第 n / 2 + 1 个结点, 且前半段比后半段长, 更改
     * p, q 前进顺序和规则但不改变步长, 可以实现让前半段比后半段短.
     * */
    while (q->next != NULL)
    {
        p = p->next;
        q = q->next;

        if (q->next)
        {
            q = q->next;
        }
    }

    /* 2. 将链表后半段逆置. */

    /* 中间结点 p 是链表前半段的最后一个结点, q 指向后半段第一个结点, 即 p->next. */
    q = p->next;
    /* 断开链表. */
    p->next = NULL;

    /* 头插法, 把 p 当作头结点. */
    while (q != NULL)
    {
        /* r 保存 q 的后继. */
        r = q->next;

        /* 头插法. */
        q->next = p->next;
        p->next = q;

        /* 读取后继. */
        q = r;
    }

    /* 3. 后半段插入到前半段中的合适位置. */

    /* q 指向链表后半段的第一个结点. */
    q = p->next;
    /* 把链表一分为二. p 指向链表前半段的最后一个结点. */
    p->next = NULL;
    /* p 指向链表前半段的第一个结点. */
    p = L->next;

    /**
     * 这时候的链表前半段 [a1,am], 后半段 [a(m+1),an].
     * a1->a2->a3->(...)->am->an->a(m-1)->a(n-2)->(...)->a(m+2)->a(m+1)
     * ↑                      ↑   ↑
     * p                      q   r
     * a1->an->a2->a3->(...)->am->a(m-1)->a(n-2)->(...)->a(m+2)->a(m+1)
     * ↑   ↑                      ↑
     * p   q                      r
     * a1->an->a2->a3->(...)->am->a(m-1)->a(n-2)->(...)->a(m+2)->a(m+1)
     *         ↑                  ↑       ↑
     *         p                  q/r     r
     */
    while (q)
    {
        /* r 保存 q 的后继. */
        r = q->next;

        /* 将 q 插入到 p 之后. */
        q->next = p->next;
        p->next = q;

        /* 更新插入点位置. */
        p = q->next;

        /* 读取后继. */
        q = r;
    }

    return OK;
}
