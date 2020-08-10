/**
 * @file threadtree.c
 * @author tianshihao
 * @brief 线索二叉树函数实现.
 * @version 0.1
 * @date 2020-08-10
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <chapter6/threadtree.h>

// 初始化线索二叉树, Thrt 是头节点.
Status InitTree_Thread(ThreadTree *Thrt)
{
    if (!((*Thrt) = (ThreadTree)malloc(sizeof(ThreadNode))))
        exit(OVERFLOW);

    (*Thrt)->data = 0;

    ThreadNode *root = NULL;
    (*Thrt)->lchild = root;
    // (*Thrt)->rchild = root;

    return OK;
} // InitTree_Thread

Status CreateThreadTree(ThreadTree *T, char *path)
{
    FILE *fp = fopen(path, "r");

    if (fp == NULL)
    {
        return ERROR;
    }

    CreateTree_Thread(T, fp);

    fclose(fp);

    return OK;
} // CreateThreadTree

void CreateTree_Thread(ThreadTree *T, FILE *fp)
{
    char ch = 0;
    ch = fgetc(fp);

    if (ch == '^')
    {
        (*T) = NULL;
    }
    else
    {
        (*T) = (ThreadNode *)malloc(sizeof(ThreadNode));
        if (!(*T))
        {
            exit(OVERFLOW);
        }

        (*T)->data = ch;
        (*T)->LTag = Link;
        (*T)->RTag = Link;
        CreateTree_Thread(&((*T)->lchild), fp);
        CreateTree_Thread(&((*T)->rchild), fp);
    }

    return;
} // CreateTree_Thread

Status PreOrderTraverse_Thread(ThreadTree T, Status (*Visit)(ElemType e))
{
    if (T)
    {
        if (Visit(T->data))
        {
            if (PreOrderTraverse_Thread(T->lchild, Visit))
            {
                if (PreOrderTraverse_Thread(T->rchild, Visit))
                {
                    return OK;
                }
            }
        }
        return ERROR;
    }
    else
    {
        printf("^");
        return OK;
    }
} // PreOrderTraverse_Thread

Status InOrderTraverse_Thread(ThreadTree T, Status (*Visit)(ElemType e))
{
    if (T)
    {
        if (InOrderTraverse_Thread(T->lchild, Visit))
        {
            if (Visit(T->data))
            {
                if (InOrderTraverse_Thread(T->rchild, Visit))
                {
                    return OK;
                }
            }
        }

        return ERROR;
    }
    else
    {
        printf("^");
        return OK;
    }
} // InOrderTraverse_Thread

Status InOrderThreading(ThreadTree *T)
{
    ThreadNode *pre = NULL;

    if (T != NULL)
    {
        InThreading(*T, &pre);
        pre->rchild = NULL;
        pre->RTag = Thread;
    }
    return OK;
} // InOrderThreading

void InThreading(ThreadTree p, ThreadNode **pre)
{
    if (p)
    {
        // 左子树线索化.
        InThreading(p->lchild, pre);

        // p 左子为空, 令 p 指向其前驱 pre.
        if (p->lchild == NULL)
        {
            p->LTag = Thread;
            p->lchild = (*pre);
        }

        // 若前驱 pre 不为空, 且 pre 右子为空, 则令 pre 指向 p.
        if (*pre != NULL && (*pre)->rchild == NULL)
        {
            (*pre)->RTag = Thread;
            (*pre)->rchild = p; // 右子树回指
        }

        // 更新最后访问的结点.
        (*pre) = p;

        // 右子树线索化.
        InThreading(p->rchild, pre);
    }

    return;
} // InThreading

Status InOrder(ThreadTree T, Status (*Visit)(ElemType e))
{
    ThreadNode *p = T;

    // 空树或遍历结束时.
    while (p->LTag != Thread)
    {
        p = p->lchild;
    }

    for (; p != NULL; p = p->rchild)
    {
        Visit(p->data);
    }

    return OK;
} // InOrder
