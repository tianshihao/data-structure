﻿/**
 * @file bitree.c
 * @author tianshihao
 * @brief implementation of binary tree function.
 * @version 0.2
 * @date 2020-08-07
 *
 * @copyright Copyright (c) 2020
 *
 */

#include <bitree.h>
#include <sqqueue.h>
#include <sqstack.h>

Status InitTreeBinary(BiTree *T)
{
    *T = NULL; // 使得指针指向 NULL.

    return OK;
}

/**
 * 即使 BiTree 类型和 BiTNode * 等价, 表面上是指针, 但是在指针传递时, 仍要取
 * BiTree 的地址, 因为在子函数中需要改变是指针本身的内容 (改变了结点间的链接关
 * 系), 而不是指针指向的内容, 因此子函数参数列表中写 BiTree *T, 否则只能传递一份
 * 指向某二叉树的指针, 在子函数中修改了二叉树后, 主函数中的指针仍然指向 NULL.
 * 
 * 简单的理解是, 在 C 语言中, 若想使得传递的参数实际被修改, 则在子函数中加上一层
 * 指针总是没有错的, 不论传递的参数是什么, 包括指针.
 */

Status CreateBinaryTreeFromFile(BiTree *t, const char *path)
{
    // 打开存储二叉树先序序列的文件.
    FILE *fp = fopen(path, "r");

    // 如果文件打开失败, 返回 ERROR.
    if (fp == NULL)
    {
        printf("No such file %s\n", path);
        return ERROR;
    }
    printf("Load binay tree from file %s.\n", path);

    // 传递的还是二叉树指针的指针.
    CreateTreeBinary(t, fp);

    fclose(fp);

    return OK;
}

void CreateTreeBinary(BiTree *t, FILE *pre_seq)
{
    char ch = 0;

    // 读取当前结点的值
    ch = fgetc(pre_seq);

    if ('^' != ch) // 使用'^'表示空结点.
    {
        // 为根结点指针分配要指向要内存空间.
        *t = (BiTNode *)malloc(sizeof(BiTNode));
        if (!*t)
        {
            exit(OVERFLOW);
        }

        (*t)->data = ch;
        // 递归创建左右子树.
        CreateTreeBinary(&((*t)->lchild), pre_seq);
        CreateTreeBinary(&((*t)->rchild), pre_seq);
    }
    else
    {
        *t = NULL;
        return;
    }
}

Status PreOrderTraverseBinaryRecur(BiTree T, Status (*Visit)(ElemType e))
{
    if (T != NULL)
    {
        if (Visit(T->data))
        {
            if (PreOrderTraverseBinaryRecur(T->lchild, Visit))
            {
                if (PreOrderTraverseBinaryRecur(T->rchild, Visit))
                {
                    return OK;
                }
            }
        }
        return ERROR;
    }
    else
    {
        return OK;
    }
}

Status PreOrderTraverseBinaryNonRecur(BiTree T, Status (*Visit)(ElemType e))
{
    SqStack S;
    InitStack_Sq(&S);

    // 工作指针.
    BiTNode *p = T;

    // 指针 p 不为空或栈不为空时.
    while (p || !StackEmpty_Sq(S))
    {
        /**
         * 1. 沿着根的左子, 一遍访问, 一遍入栈, 直至当前结点为空, 为空时说明该访
         * 问右子了.
         * */
        if (p)
        {
            Visit(p->data);  // 先访问当前结点.
            Push_Sq(&S, *p); // 入栈.
            p = p->lchild;   // 再向左
        }
        /**
         * 2. 将结点从栈中弹出, 若其右子为空, 则继续执行 2, 否则右子树继续执行 1. 
         * */
        else
        {
            Pop_Sq(&S, &p);
            p = p->rchild;
        }
    }

    return OK;
}

Status InOrderTraverseBinaryRecur(BiTree T, Status (*Visit)(ElemType e))
{
    if (T)
    {
        if (InOrderTraverseBinaryRecur(T->lchild, Visit))
        {
            if (Visit(T->data))
            {
                if (InOrderTraverseBinaryRecur(T->rchild, Visit))
                {
                    return OK;
                }
            }
        }
        return ERROR;
    }
    else
    {
        return OK;
    }
}

Status InOrderTraverseBinaryNonRecur(BiTree T, Status (*Visit)(ElemType e))
{
    // 初始化顺序栈.
    SqStack S;
    InitStack_Sq(&S);

    // 工作指针.
    BiTNode *p = T;

    while (p || !StackEmpty_Sq(S))
    {
        /**
         * 1. 沿着根的左子, 依次入栈, 直至左子为空, 说明已找到可以输出的结点.
         */
        if (p) // 一路向左.
        {
            Push_Sq(&S, *p); // 当前结点入栈.
            p = p->lchild;   // 左子不空, 一直向左走.
        }

        /**
         * 2. 可以输出的结点从栈中弹出, 若其右子为空, 则继续执行 2, 否则右子树继
         * 续执行 1.
         * */
        else // 出栈, 并转向出栈结点的右子树.
        {
            Pop_Sq(&S, &p); // 栈顶元素出栈.
            Visit(p->data); // 访问出栈结点.
            p = p->rchild;  // 向右子树走, p 赋值为当前结点的右子.
        }
    }

    return OK;
}

Status PostOrderTraverseBinaryRecur(BiTree T, Status (*Visit)(ElemType e))
{
    if (T)
    {
        if (PostOrderTraverseBinaryRecur(T->lchild, Visit))
        {
            if (PostOrderTraverseBinaryRecur(T->rchild, Visit))
            {
                if (Visit(T->data))
                {
                    return OK;
                }
            }
        }
        return ERROR;
    }
    else
    {
        return OK;
    }
}

Status PostOrderTraverseBinaryNonRecur(BiTree T, Status (*Visit)(ElemType e))
{
    SqStack S;
    InitStack_Sq(&S);

    // p 是工作指针.
    BiTNode *p = T;

    // r 记录最近访问过的结点.
    BiTNode *r = NULL;

    /**
     * 后续非递归遍历二叉树是先访问左子树, 再访问右子树, 最后访问根结点.
     */

    while (p || !StackEmpty_Sq(S))
    {
        /**
         * 1. 沿着根结点的左子, 依次入栈, 直至左子为空.
        */
        if (p)
        {
            Push_Sq(&S, *p);
            p = p->lchild;
        }
        /**
         * 左子为空之后再判断右子, 如果右子也为空, 则需要将栈顶元素出栈. 否则,
         * 右子树也要执行 1.
         */
        else
        {
            GetTop_Sq(S, &p);
            /**
             * 2. 若栈顶元素右子非空且未访问过, 则将右子执行 1.
             */
            /**
             * 注意, 原来 Push_Sq() 只是将结点复制了一份存到了栈中, 所以 r 记录的上
             * 次访问过的结点和栈中相对应的结点并不相同, 不能直接使用
             * p->rchild != r 比较, 可以比较 data. 但是二叉树中可能会出现重复的
             * 元素, 比较 data 会出现误差, 所以修改 Push_Sq() 为向栈中存放二叉树中
             * 结点本身, 而不是拷贝比较好.
             * 
             * 刚才试了一下, 还是直接比较 data 方便.
             */
            if (p->rchild && p->rchild->data != r->data)
            {
                p = p->rchild;
                Push_Sq(&S, *p); // 右子入栈.
                p = p->lchild;   // 检查右子左子.
            }
            /**
             * 否则栈顶元素出栈, 并访问.
             */
            /**
             * @see LevelOrderTraverseBinary(BiTree T, Status (*Visit)(ElemType e))
             * 
             * 这里 Pop_Sq 中第二个参数是类型是 BiTNode **, 即指向 BiTNode 指针的指
             * 针, 并不是我需要修改栈中的存储的元素本身, 而是只用当指针 p 为 NULL
             * 时, 才会使用 Pop_Sq(), 而 NULL 并没有指向的内容, 不能修改 p 指向的内
             * 容, 也就无法复制栈中的元素, 而在 Pop_Sq() 中为 p malloc 存储空间又改
             * 变了指针本身, 所以将参数改为 BiTNode **, 直接修改 *p, 即 BiTNode*.
             */
            else
            {
                Pop_Sq(&S, &p);
                Visit(p->data);
                r = p;    // 更新最近访问结点.
                p = NULL; // 结点访问之后置 p 为 NULL.
            }
        }
    }

    return OK;
}

Status LevelOrderTraverseBinary(BiTree T, Status (*Visit)(ElemType e))
{
    // 初始化辅助队列.
    SqQueue Q;
    InitQueueSq(&Q);

    // 二叉树根结点入队, 根结点为第一层.
    EnQueueSq(&Q, *T);

    /**
     * @see PostOrderTraverseBinaryNonRecur(BiTree T, Status (*Visit)(ElemType e))
     * 
     * 层序遍历 LevelOrderTraverseBinary() 中队列出队操作没有像出栈操作一样修改
     * 为传递指针的指针, 原因是出队之前, 工作指针 p 未被初始化为 NULL, 算法也使得
     * p 不可能为 NULL, 所以在 DeQueue_Sq() 中, 子函数修改了已经指向某块内存的
     * 指针 (不管这个指针指向什么, 即使是指向初始化时的随机内存单元) 所指向的内容,
     * 并没有修改指针本身, 所以原来的算法可以继续使用, 无需修改. 这样做带来的副作用
     * 是, 初始化指针 p 时, p 可能指向任何内存单元, 向这个内存单元写入数据, 把原
     * 来的数据覆盖掉, 可能会导致系统崩溃. 我发现的副作用是多次执行这个函数, 输出
     * 的结果可能不同.
     * 
     * 但实际上, 编译器会将未初始化的指针指向固定的, 不用的地址. 可以试一试如下
     * 代码:
     * 
     * int *p;
     * 
     * printf(">>>>>>>>>>> *p = %d <<<<<<<<<<<\n", *p);
     * 
     * system("pause");
     * 
     * 相信每次的输出结果都是一样的, 例如:
     * 
     * >>>>>>>>>>> *p = 17744 <<<<<<<<<<<
     * 请按任意键继续. . . 
     *
     */

    // // 工作指针.

    // BiTNode *p = NULL;
    BiTNode *p = (BiTNode *)malloc(sizeof(BiTNode));
    p->lchild = NULL;
    p->rchild = NULL;

    while (!QueueEmptySq(Q))
    {

        // 队头结点出队.
        DeQueueSq(&Q, p);

        // 访问出队结点.
        Visit(p->data);

        // 左子树不为空, 则左子树根结点入队.
        if (p->lchild != NULL)
        {
            EnQueueSq(&Q, *p->lchild);
        }

        // 右子树不为空, 则右子树根结点入队.
        if (p->rchild != NULL)
        {
            EnQueueSq(&Q, *p->rchild);
        }
    }

    DestoryQueueSq(&Q);

    return OK;
}

Status InvertLevelTraverseBinary(BiTree T, Status (*Visit)(ElemType e))
{
    if (T != NULL)
    {
        SqQueue Q;
        InitQueueSq(&Q);
        EnQueueSq(&Q, *T);

        SqStack S;
        InitStack_Sq(&S);

        BiTNode *p = T;

        while (!QueueEmptySq(Q))
        {
            DeQueueSq(&Q, p);

            Push_Sq(&S, *p);

            if (p->lchild != NULL)
            {
                EnQueueSq(&Q, *p->lchild);
            }

            if (p->rchild != NULL)
            {
                EnQueueSq(&Q, *p->rchild);
            }
        }

        while (!StackEmpty_Sq(S))
        {
            Pop_Sq(&S, &p);
            Visit(p->data);
        }
        return OK;
    }
    else
    {
        return ERROR;
    }
}

int BiTreeHeight(BiTree t)
{
    if (t != NULL)
    {
        /* 初始化队列. */
        SqQueue q;
        InitQueueSq(&q);

        /* 根节点入队. */
        EnQueueSq(&q, *t);

        /* 计数器, 记录二叉树的高度. */
        int height = 0;

        /* 工作指针 p. */
        /* BiTNode *p = T; */
        BiTNode *p = (BiTNode *)malloc(sizeof(BiTNode));
        p->lchild = NULL;
        p->rchild = NULL;

        /* 指针指向每层最右边结点在队列中的位置. */
        int last = q.rear;

        while (!QueueEmptySq(q))
        {
            /* 队头结点出队. */
            DeQueueSq(&q, p);

            if (p->lchild != NULL)
            {
                EnQueueSq(&q, *p->lchild);
            }

            if (p->rchild != NULL)
            {
                EnQueueSq(&q, *p->rchild);
            }

            /* 上一层元素都出队了. */
            if (q.front == last)
            {
                /*层数加 1. */
                height++;

                /* 更新标记.*/
                last = q.rear;
            }
        }

        free(p);
        p = NULL;

        DestoryQueueSq(&q);

        return height;
    }
    else
    {
        // 树空, 高度为 0.
        return 0;
    }
}

BiTree PreInCreate(ElemType *PreOrder,
                   int preL, int preR,
                   ElemType *InOrder,
                   int InL, int InR)
{
    /* 创建根结点. */
    BiTree root = (BiTNode *)malloc(sizeof(BiTNode));

    /* 先序遍历序列第一个值是根结点的值. */
    root->data = PreOrder[preL];

    /* 在中序遍历序列中找到根结点的位置. */
    int rootPos = InL;
    while (InOrder[rootPos] != root->data)
    {
        ++rootPos;
    }

    /* 左子树长度. */
    int lchildLen = rootPos - InL;

    /* 右子树长度. */
    int rchildLen = InR - rootPos;

    /* 左子树不为空. */
    if (lchildLen > 0)
    {
        /* 注意 +1, -1 边界条件. */
        root->lchild = PreInCreate(PreOrder,
                                   preL + 1, preL + lchildLen,
                                   InOrder,
                                   InL, InL + lchildLen - 1);
    }
    else
    {
        root->lchild = NULL;
    }

    /* 右子树不为空. */
    if (rchildLen > 0)
    {
        root->rchild = PreInCreate(PreOrder,
                                   preR - rchildLen + 1, preR,
                                   InOrder,
                                   InR - rchildLen + 1, InR);
    }
    else
    {
        root->rchild = NULL;
    }

    return root;
}

Status SwapSubTree(BiTree T)
{
    /* 两种写法均可. */
    if (T)
    {
        SwapSubTree(T->lchild);
        SwapSubTree(T->rchild);

        BiTNode *tmp = T->lchild;
        T->lchild = T->rchild;
        T->rchild = tmp;
    }

    /**
    BiTNode *tmp = T->lchild;
    T->lchild = T->rchild;
    T->rchild = tmp;

    if (T->lchild)
    {
        SwapSubTree(T->lchild);
    }

    if (T->rchild)
    {
        SwapSubTree(T->rchild);
    }
     */

    return OK;
}

Status FindAncestor(BiTree T, ElemType x)
{
    // 临时的栈.
    typedef struct stack
    {
        BiTNode *node;
        int tag; // 标志域, 结点 *node 右子被访问 tag = 1, 否则为 0.
    } stack;

    // 算法本质是后序遍历过程, 所以栈的深度不会超过树的深度.
    stack s[BiTreeHeight(T) + 1];
    // 栈顶指针. 从 1 开始, 0 表示空栈.
    int top = 0;

    // 工作指针 p.
    BiTNode *p = T;

    while (p != NULL || top > 0)
    {
        // 一路向左, 将结点入栈.
        while (p != NULL && p->data != x)
        {
            s[++top].node = p;
            s[top].tag = 0;
            p = p->lchild; // 向左.
        }

        // 如果找到了 x. 注意上面的循环出来时 p 可以为空, 还要判空.
        if (p != NULL && p->data == x)
        {
            for (int i = 1; i <= top; ++i)
            {
                printf("%c%c", s[i].node->data, i == top ? '\n' : ',');
            }
            // exit(OK);
            return OK;
        }

        // 退栈.
        while (top > 0 && s[top].tag == 1)
        {
            top--;
        }

        // 沿着右分支向下遍历.
        if (top != 0)
        {
            s[top].tag = 1;          // 栈顶元素右子被访问了.
            p = s[top].node->rchild; // 跳到右子.
        }
    }

    return ERROR;
}

BiTNode *FindCommonAncestor(BiTree T, BiTNode *p, BiTNode *q)
{
    // 临时的栈.
    typedef struct stack
    {
        BiTNode *node;
        int tag; // 标志域, 结点 *node 右子被访问 tag = 1, 否则为 0.
    } stack;

    // 算法本质是后序遍历过程, 所以栈的深度不会超过树的深度.
    stack s[BiTreeHeight(T) + 1];
    // 栈顶指针. 从 1 开始, 0 表示空栈.
    int top = 0;

    stack s1[BiTreeHeight(T) + 1];
    int top1 = 0;

    // 工作指针.
    BiTNode *ptr = T;

    while (ptr != NULL || top > 0)
    {
        // 沿着左子入栈.
        // ? 书中答案这个外面的 while 是不是是错了?
        // while (ptr != NULL && ptr != p && ptr != q)
        {
            while (ptr != NULL)
            {
                s[++top].node = ptr;
                s[top].tag = 0;
                ptr = ptr->lchild;
            }
        }

        /**
         * @see FindAncestor(BiTree T, ElemType x)
         * 退栈, FindAncestor 中退栈上面的操作也可以向下面这样写到退栈循环里面,
         * 先于 top-- 执行.
         */
        while (top > 0 && s[top].tag == 1)
        {
            // 找到了结点 p, 复制 s 即 p 的祖先到辅助栈 s1. 再继续寻找 q.
            if (s[top].node == p)
            {
                for (int i = 1; i <= top; ++i)
                {
                    s1[i] = s[i];
                }
                top1 = top;
            }

            // 找到 q 时, 栈 s 中为 q 的祖先, 而 s1 中为 p 的祖先, 比较两个栈,
            // 将 q 的祖先到 p 的祖先中去匹配, 第一个匹配的元素就是 p 和 q 的
            // 最近公共祖先.
            if (s[top].node == q)
            {
                for (int i = top; i > 0; --i)
                {
                    for (int j = top1; j > 0; --j)
                    {
                        if (s1[j].node == s[i].node)
                        {
                            return s[i].node;
                        }
                    }
                }
            }

            // 后序遍历中到了访问根结点时, 其左右子均已被访问, 访问完根结点, 根
            // 结点退栈.
            top--;
        }

        // 访问右子树.
        if (top != 0)
        {
            s[top].tag = 1;
            ptr = s[top].node->rchild;
        }
    }

    return NULL;
}

int BiTreeWidth(BiTree T)
{
    if (T != NULL)
    {
        SqQueue Q;
        InitQueueSq(&Q);

        BiTNode *p = T;

        EnQueueSq(&Q, *p);

        int last = Q.rear;
        int width = 0;
        int maxWidth = 0;

        while (!QueueEmptySq(Q))
        {
            DeQueueSq(&Q, p);

            ++width;

            if (p->lchild != NULL)
            {
                EnQueueSq(&Q, *p->lchild);
            }

            if (p->lchild != NULL)
            {
                EnQueueSq(&Q, *p->rchild);
            }

            if (last == Q.front)
            {
                last = Q.rear;
                if (width > maxWidth)
                {
                    maxWidth = width;
                }
                width = 0;
            }
        }

        return maxWidth;
    }
    else
    {
        return 0;
    }
}

void PreToPost(ElemType *Pre,
               int preL, int preR,
               ElemType *Post,
               int postL, int postR)
{
    if (preR >= preL)
    {
        // 满二叉树左右子树在遍历序列中的长度相等.
        int half = (preR - preL) / 2;

        Post[postR] = Pre[preL];

        /**
         * 即先序遍历序列的非根结点部分的二分遍历. 每次二分都需要挖去先序序列中
         * 的最左边的元素 (即根结点), 且每次二分的长度都是上次的 1/2.
         */
        PreToPost(Pre,
                  preL + 1, preL + half,
                  Post,
                  postL, postL + half - 1);

        PreToPost(Pre,
                  preL + half + 1, preR,
                  Post,
                  postL + half, postR - 1);
    }
}

Status Similar(BiTree T1, BiTree T2)
{
    if (T1 == NULL && T2 == NULL)
    {
        return TRUE;
    }
    else if (T1 == NULL || T2 == NULL)
    {
        return FALSE;
    }
    else
    {
        return Similar(T1->lchild, T2->lchild) && Similar(T1->rchild, T2->rchild);
    }
}

int WPL(BiTree T)
{
    return WPLPreOrder(T, 1);
}

int WPLPreOrder(BiTree p, int depth)
{
    static int wpl = 0;

    // 若是叶结点, 累计 wpl.
    if (p->lchild == NULL && p->rchild == NULL)
    {
        wpl += depth * p->data;
    }

    // 若左子树不空, 则对左子树进行递归调用.
    if (p->lchild != NULL)
    {
        WPLPreOrder(p->lchild, depth + 1);
    }

    // 若右子树不空, 则对右子树进行递归调用.
    if (p->rchild != NULL)
    {
        WPLPreOrder(p->rchild, depth + 1);
    }

    return wpl;
}

int WPLLevelOrder(BiTree T)
{
    // 顺序队列.
    SqQueue Q;
    InitQueueSq(&Q);

    // 工作指针 p.
    BiTNode *p = T;

    // 根结点入队.
    EnQueueSq(&Q, *p);

    // 记录队尾指针, 用于判断一层是否遍历完毕.
    int last = Q.rear;

    // wpl.
    int wpl = 0;

    // 当前访问的叶结点深度. 根结点以入队, 所以初始深度为 1.
    int depth = 1;

    while (!QueueEmptySq(Q))
    {
        DeQueueSq(&Q, p);

        // 找到叶子结点, 更新 wpl.
        if (p->lchild == NULL && p->rchild == NULL)
        {
            wpl += depth * p->data;
        }

        if (p->lchild != NULL)
        {
            EnQueueSq(&Q, *p->lchild);
        }

        if (p->rchild != NULL)
        {
            EnQueueSq(&Q, *p->rchild);
        }

        if (last == Q.front)
        {
            ++depth;
            last = Q.rear;
        }
    }

    return wpl;
}

char predt = 0;

Status JudgeBST(BiTree T)
{
    if (T == NULL)
    {
        return TRUE;
    }
    else
    {
        // 判断左子树.
        int left = JudgeBST(T->lchild);

        // 如果左子树不是二叉排序树或者前驱结点即左子的值大于当前结点,
        if (left == 0 || predt >= T->data)
        {
            // 则不是二叉排序树.
            return FALSE;
        }

        // 更新前驱结点值.
        predt = T->data;

        // 判断右子树.
        int right = JudgeBST(T->rchild);
        // 返回右子树的结果.
        return right;
    }
}

Status JudgeAVL(BiTree T, int *height, int *balance)
{
    int lheight = 0, lbalance = 0, rheight = 0, rbalance = 0;

    // 1. 若 T 为空, 则height = 0, balance = 1.
    if (T == NULL)
    {
        *height = 0;
        *balance = 1;
    }
    // 2. 仅有根结点, 则height = 1, balance = 1.
    else if (T->lchild == NULL && T->rchild == NULL)
    {
        *height = 1;
        *balance = 1;
    }
    // 3. 否则,对 T 的左右子树执行后续遍历递归算法, 返回左右子树的高度和平衡标记.
    // T 的高度为最高子树的高度加 1. 若左右子树的高度差大于 1, 则 balance = 0;
    // 若左右子树的高度差小于等于 1, 且左右子树都平衡时, balance = 1, 否则,
    // balance = 0.
    else
    {
        JudgeAVL(T->lchild, &lheight, &lbalance);
        JudgeAVL(T->rchild, &rheight, &rbalance);

        *height = (lheight > rheight ? lheight : rheight) + 1;

        if (lheight - rheight < 2 || rheight - lheight < 2)
        {
            *balance = lbalance && rbalance;
        }
        else
        {
            *balance = 0;
        }
    }
}
