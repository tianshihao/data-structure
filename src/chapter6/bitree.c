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

Status InitTree(BiTree *T)
{
    // *T 即为指向二叉树根结点的指针.
    if (*T == NULL) // 若已经指向空, 操作失败, 报错.
    {
        return ERROR;
    }

    *T = NULL; // 使得指针指向 NULL.

    return OK;
} // InitTree

/**
 * 即使 BiTree 类型和 BiTNode * 等价, 表面上是指针, 但是在指针传递时, 仍要取 BiTree 的地址,
 * 因为在子函数中需要改变是指针本身的内容 (改变了结点间的链接关系), 而不是指针指向的内容, 
 * 因此子函数参数列表中写 BiTree *T, 否则只能传递一份指向某二叉树的指针, 在子函数中修改了二叉树
 * 后, 主函数中的指针仍然指向 NULL.
 * 
 * 简单的理解是, 在 C 语言中, 若想使得传递的参数实际被修改, 则在子函数中加上一层指针总是没有错的,
 * 不论传递的参数是什么, 包括指针.
 * */

Status CreateBiTree(BiTree *T, const char *path)
{
    // 打开存储二叉树先序序列的文件.
    FILE *fp = fopen(path, "r");

    // 如果文件打开失败, 返回 ERROR.
    if (fp == NULL)
    {
        return ERROR;
    }

    // 传递的还是二叉树指针的指针.
    CreateTree(T, fp);

    fclose(fp);

    return OK;
} // CreateBiTree

void CreateTree(BiTree *T, FILE *PreSeq)
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
        CreateTree(&((*T)->lchild), PreSeq); // 创建左子树
        CreateTree(&((*T)->rchild), PreSeq); // 创建右子树
    }
} // CreateTree

Status PreOrderTraverse(BiTree T, Status (*Visit)(ElemType e))
{
    if (T)
    {
        if (Visit(T->data))
        {
            if (PreOrderTraverse(T->lchild, Visit))
            {
                if (PreOrderTraverse(T->rchild, Visit))
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
} // PreOrderTraverse

Status PreOrderTraverse2(BiTree T, Status (*Visit)(ElemType e))
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
} // PreOrderTraverse2

Status InOrderTraverse(BiTree T, Status (*Visit)(ElemType e))
{
    if (T)
    {
        if (InOrderTraverse(T->lchild, Visit))
        {
            if (Visit(T->data))
            {
                if (InOrderTraverse(T->rchild, Visit))
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
} // InOrderTraverse

Status InOrderTraverse2(BiTree T, Status (*Visit)(ElemType e))
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
         * 2. 可以输出的结点从栈中弹出, 若其右子为空, 则继续执行 2, 否则右子树继续
         * 执行 1.
         * */
        else // 出栈, 并转向出栈结点的右子树.
        {
            Pop(&S, &p);    // 栈顶元素出栈.
            Visit(p->data); // 访问出栈结点.
            p = p->rchild;  // 向右子树走, p 赋值为当前结点的右子.
        }
    } // while

    return OK;
} // InOrderTraverse2

Status PostOrderTraverse(BiTree T, Status (*Visit)(ElemType e))
{
    if (T)
    {
        if (PostOrderTraverse(T->lchild, Visit))
        {
            if (PostOrderTraverse(T->rchild, Visit))
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
} // PostOrderTraverse

Status PostOrderTraverse2(BiTree T, Status (*Visit)(ElemType e))
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
             * 结点本身, 而不是拷贝.
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
} // PostOrderTraverse2

Status LevelOrderTraverse(BiTree T, Status (*Visit)(ElemType e))
{
    // 初始化辅助队列.
    SqQueue Q;
    InitQueue_Sq(&Q);

    // 二叉树根结点入队, 根结点为第一层.
    EnQueue_Sq(&Q, *T);

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
} // LevelOrderTraverse
