/**
 * @file bitree.c
 * @author tianshihao
 * @brief implementation of binary tree function.
 * @version 0.1
 * @date 2020-08-07
 *
 * @copyright Copyright (c) 2020
 *
 */

#include <chapter6/bitree.h>
#include <chapter6/sqqueue.h>
#include <chapter6/sqstack.h>

Status InitTree_Binary(BiTree *T)
{
    // *T 即为指向二叉树根结点的指针.
    if (*T == NULL) // 若已经指向空, 操作失败, 报错.
    {
        return ERROR;
    }

    *T = NULL; // 使得指针指向 NULL.

    return OK;
} // InitTree_Binary

/**
 * 即使 BiTree 类型和 BiTNode * 等价, 表面上是指针, 但是在指针传递时, 仍要取
 * BiTree 的地址, 因为在子函数中需要改变是指针本身的内容 (改变了结点间的链接关
 * 系), 而不是指针指向的内容, 因此子函数参数列表中写 BiTree *T, 否则只能传递一份
 * 指向某二叉树的指针, 在子函数中修改了二叉树后, 主函数中的指针仍然指向 NULL.
 * 
 * 简单的理解是, 在 C 语言中, 若想使得传递的参数实际被修改, 则在子函数中加上一层
 * 指针总是没有错的, 不论传递的参数是什么, 包括指针.
 */

Status CreateBinaryTree(BiTree *T, const char *path)
{
    // 打开存储二叉树先序序列的文件.
    FILE *fp = fopen(path, "r");

    // 如果文件打开失败, 返回 ERROR.
    if (fp == NULL)
    {
        return ERROR;
    }

    // 传递的还是二叉树指针的指针.
    CreateTree_Binary(T, fp);

    fclose(fp);

    return OK;
} // CreateBinaryTree

void CreateTree_Binary(BiTree *T, FILE *PreSeq)
{
    char ch = 0;

    // 读取当前结点的值
    // if (PreSeq == NULL)
    // scanf("%c", &ch);
    // else
    ch = fgetc(PreSeq);

    if (ch == '^') // 使用'^'表示空结点.
    {
        *T = NULL;
    }
    else
    {
        // 为根结点指针分配要指向要内存空间.
        *T = (BiTNode *)malloc(sizeof(BiTNode));
        if (!*T)
        {
            exit(OVERFLOW);
        }

        (*T)->data = ch;
        CreateTree_Binary(&((*T)->lchild), PreSeq); // 创建左子树
        CreateTree_Binary(&((*T)->rchild), PreSeq); // 创建右子树
    }
} // CreateTree_Binary

Status PreOrderTraverse_Binary(BiTree T, Status (*Visit)(ElemType e))
{
    if (T)
    {
        if (Visit(T->data))
        {
            if (PreOrderTraverse_Binary(T->lchild, Visit))
            {
                if (PreOrderTraverse_Binary(T->rchild, Visit))
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
} // PreOrderTraverse_Binary

Status PreOrderTraverse_Binary2(BiTree T, Status (*Visit)(ElemType e))
{
    SqStack S;
    InitStack(&S);

    // 工作指针.
    BiTNode *p = T;

    // 指针 p 不为空或栈不为空时.
    while (p || !StackEmpty(S))
    {
        /**
         * 1. 沿着根的左子, 一遍访问, 一遍入栈, 直至当前结点为空, 为空时说明该访
         * 问右子了.
         * */
        if (p)
        {
            Visit(p->data); // 先访问当前结点.
            Push(&S, *p);   // 入栈.
            p = p->lchild;  // 再向左
        }
        /**
         * 2. 将结点从栈中弹出, 若其右子为空, 则继续执行 2, 否则右子树继续执行 1. 
         * */
        else
        {
            Pop(&S, &p);
            p = p->rchild;
        }
    } // while

    return OK;
} // PreOrderTraverse_Binary2

Status InOrderTraverse_Binary(BiTree T, Status (*Visit)(ElemType e))
{
    if (T)
    {
        if (InOrderTraverse_Binary(T->lchild, Visit))
        {
            if (Visit(T->data))
            {
                if (InOrderTraverse_Binary(T->rchild, Visit))
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
} // InOrderTraverse_Binary

Status InOrderTraverse_Binary2(BiTree T, Status (*Visit)(ElemType e))
{
    // 初始化顺序栈.
    SqStack S;
    InitStack(&S);

    // 工作指针.
    BiTNode *p = T;

    while (p || !StackEmpty(S))
    {
        /**
         * 1. 沿着根的左子, 依次入栈, 直至左子为空, 说明已找到可以输出的结点.
         */
        if (p) // 一路向左.
        {
            Push(&S, *p);  // 当前结点入栈.
            p = p->lchild; // 左子不空, 一直向左走.
        }

        /**
         * 2. 可以输出的结点从栈中弹出, 若其右子为空, 则继续执行 2, 否则右子树继
         * 续执行 1.
         * */
        else // 出栈, 并转向出栈结点的右子树.
        {
            Pop(&S, &p);    // 栈顶元素出栈.
            Visit(p->data); // 访问出栈结点.
            p = p->rchild;  // 向右子树走, p 赋值为当前结点的右子.
        }
    } // while

    return OK;
} // InOrderTraverse_Binary2

Status PostOrderTraverse_Binary(BiTree T, Status (*Visit)(ElemType e))
{
    if (T)
    {
        if (PostOrderTraverse_Binary(T->lchild, Visit))
        {
            if (PostOrderTraverse_Binary(T->rchild, Visit))
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
} // PostOrderTraverse_Binary

Status PostOrderTraverse_Binary2(BiTree T, Status (*Visit)(ElemType e))
{
    SqStack S;
    InitStack(&S);

    // p 是工作指针.
    BiTNode *p = T;

    // r 记录最近访问过的结点.
    BiTNode *r = NULL;

    /**
     * 后续非递归遍历二叉树是先访问左子树, 再访问右子树, 最后访问根结点.
     */

    while (p || !StackEmpty(S))
    {
        /**
         * 1. 沿着根结点的左子, 依次入栈, 直至左子为空.
        */
        if (p)
        {
            Push(&S, *p);
            p = p->lchild;
        }
        /**
         * 左子为空之后再判断右子, 如果右子也为空, 则需要将栈顶元素出栈. 否则,
         * 右子树也要执行 1.
         */
        else
        {
            GetTop(S, &p);
            /**
             * 2. 若栈顶元素右子非空且未访问过, 则将右子执行 1.
             */
            /**
             * 注意, 原来 Push() 只是将结点复制了一份存到了栈中, 所以 r 记录的上
             * 次访问过的结点和栈中相对应的结点并不相同, 不能直接使用
             * p->rchild != r 比较, 可以比较 data. 但是二叉树中可能会出现重复的
             * 元素, 比较 data 会出现误差, 所以修改 Push() 为向栈中存放二叉树中
             * 结点本身, 而不是拷贝比较好.
             * 
             * 刚才试了一下, 还是直接比较 data 方便.
             */
            if (p->rchild && p->rchild->data != r->data)
            {
                p = p->rchild;
                Push(&S, *p);  // 右子入栈.
                p = p->lchild; // 检查右子左子.
            }
            /**
             * 否则栈顶元素出栈, 并访问.
             */
            /**
             * @see LevelOrderTraverse_Binary(BiTree T, Status (*Visit)(ElemType e))
             * 
             * 这里 Pop 中第二个参数是类型是 BiTNode **, 即指向 BiTNode 指针的指
             * 针, 并不是我需要修改栈中的存储的元素本身, 而是只用当指针 p 为 NULL
             * 时, 才会使用 Pop(), 而 NULL 并没有指向的内容, 不能修改 p 指向的内
             * 容, 也就无法复制栈中的元素, 而在 Pop() 中为 p malloc 存储空间又改
             * 变了指针本身, 所以将参数改为 BiTNode **, 直接修改 *p, 即 BiTNode*.
             */
            else
            {
                Pop(&S, &p);
                Visit(p->data);
                r = p;    // 更新最近访问结点.
                p = NULL; // 结点访问之后置 p 为 NULL.
            }
        }
    }

    return OK;
} // PostOrderTraverse_Binary2

Status LevelOrderTraverse_Binary(BiTree T, Status (*Visit)(ElemType e))
{
    // 初始化辅助队列.
    SqQueue Q;
    InitQueue_Sq(&Q);

    // 二叉树根结点入队, 根结点为第一层.
    EnQueue_Sq(&Q, *T);

    /**
     * @see PostOrderTraverse_Binary2(BiTree T, Status (*Visit)(ElemType e))
     * 
     * 层序遍历 LevelOrderTraverse_Binary() 中队列出队操作没有像出栈操作一样修该为传递
     * 指针的指针, 原因是出队之前, 工作指针 p 未被初始化为 NULL, 算法也使得 p 不
     * 可能为 NULL, 所以在 DeQueue_Sq() 中, 子函数修改了已经指向某块内存的指针 (
     * 不管这个指针指向什么, 即使是指向初始化时的随机内存单元) 所指向的内容, 并
     * 没有修改指针本身, 所以原来的算法可以继续使用, 无需修改. 这样做带来的副作用
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

    // 工作指针.
    BiTNode *p;

    while (!QueueEmpty_Sq(Q))
    {
        // 队头结点出队.
        DeQueue_Sq(&Q, p);

        // 访问出队结点.
        Visit(p->data);

        // 左子树不为空, 则左子树根结点入队.
        if (p->lchild != NULL)
        {
            EnQueue_Sq(&Q, *p->lchild);
        }

        // 右子树不为空, 则右子树根结点入队.
        if (p->rchild != NULL)
        {
            EnQueue_Sq(&Q, *p->rchild);
        }
    } // while

    return OK;
} // LevelOrderTraverse_Binary

Status InvertLevelTraverse_Binary(BiTree T, Status (*Visit)(ElemType e))
{
    if (T != NULL)
    {
        SqQueue Q;
        InitQueue_Sq(&Q);
        EnQueue_Sq(&Q, *T);

        SqStack S;
        InitStack(&S);

        BiTNode *p = T;

        while (!QueueEmpty_Sq(Q))
        {
            DeQueue_Sq(&Q, p);

            Push(&S, *p);

            if (p->lchild != NULL)
            {
                EnQueue_Sq(&Q, *p->lchild);
            }

            if (p->rchild != NULL)
            {
                EnQueue_Sq(&Q, *p->rchild);
            }
        } // while

        while (!StackEmpty(S))
        {
            Pop(&S, &p);
            Visit(p->data);
        }
        return OK;
    }
    else
    {
        return ERROR;
    }
} // InvertLevelTraverse_Binary

int BiTreeDepth(BiTree T)
{
    if (T != NULL)
    {
        SqQueue Q;
        InitQueue_Sq(&Q);

        EnQueue_Sq(&Q, *T);

        // 二叉树高度.
        int depth = 0;

        // 工作指针.
        BiTNode *p = T;

        // 指针指向每层最右边结点在队列中的位置.
        int last = Q.rear;

        while (!QueueEmpty_Sq(Q))
        {
            DeQueue_Sq(&Q, p);

            if (p->lchild != NULL)
            {
                EnQueue_Sq(&Q, *p->lchild);
            }

            if (p->rchild != NULL)
            {
                EnQueue_Sq(&Q, *p->rchild);
            }

            // 上一层元素都出队了.
            if (Q.front == last)
            {
                depth++;
                last = Q.rear;
            }
        }

        return depth;
    }
    else
    {
        // 树空, 高度为 0.
        return 0;
    }
} // BiTreeDepth