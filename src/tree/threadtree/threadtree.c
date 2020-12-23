/**
 * @file threadtree.c
 * @author tianshihao
 * @brief 线索二叉树方法实现.
 * @version 0.2
 * @date 2020-12-21
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <tree/threadtree/threadtree.h>

Status InitTree_Thread(ThreadTree *T)
{
    if (!((*T) = malloc(sizeof(ThreadNode))))
    {
        exit(OVERFLOW);
    }

    (*T)->data = 0;

    ThreadNode *root = NULL;
    (*T)->lchild = root;
    /* (*T)->rchild = root; */

    return OK;
}

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
}

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
        (*T) = malloc(sizeof(ThreadNode));
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
}

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
}

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
}

Status PreOrderThreading(ThreadTree *T)
{
    /* 初始化前驱结点. */
    ThreadNode *pre = NULL;

    /* 若二叉树不为空. */
    if (T != NULL)
    {
        /* 开始先序线索化. */
        PreThreading(*T, &pre);

        /* 处理最后一个结点. */
        pre->rchild = NULL;
        pre->RTag = Thread;
    }

    return OK;
}

void PreThreading(ThreadTree p, ThreadNode **pre)
{
    if (p)
    {
        /* 若当前结点 p 左子为空, 令 p 指向其前驱 pre. */
        if (p->lchild == NULL)
        {
            p->LTag = Thread;
            p->lchild = (*pre);
        }

        /* 若前驱 pre 不为空, 且 pre 右子为空, 则令 pre 指向 p. */
        if ((*pre) != NULL && (*pre)->rchild == NULL)
        {
            (*pre)->RTag = Thread;
            (*pre)->rchild = p;
        }

        /* 更新最后访问的结点. */
        (*pre) = p;

        /* 左右子树线索化. */
        if (p->LTag == Link)
        {
            PreThreading(p->lchild, pre);
        }
        if (p->RTag == Link)
        {
            PreThreading(p->rchild, pre);
        }
    }

    return;
}

Status PreOrder(ThreadTree T, Status (*Visit)(ElemType e))
{
    ThreadNode *p = T;

    while (p != NULL)
    {
        /* 一直想左, 同时访问当前结点, 即根结点优先, 先序. */
        /* 若 p->LTag != Link 则表明 p 为左叶子结点. */
        while (p->LTag == Link)
        {
            Visit(p->data);
            p = p->lchild;
        }

        /* 左子树. */
        Visit(p->data);

        /* 右子树. */
        if (p->LTag == Thread)
        {
            p = p->rchild;
        }
    }

    return OK;
}

Status InOrderThreading(ThreadTree *T)
{
    /* 初始化前驱结点.*/
    ThreadNode *pre = NULL;

    /* 若二叉树不为空.*/
    if (T != NULL)
    {
        /* 开始中序线索化.*/
        InThreading(*T, &pre);

        /* 处理最后一个结点.*/
        pre->rchild = NULL;
        pre->RTag = Thread;
    }

    return OK;
}

void InThreading(ThreadTree p, ThreadNode **pre)
{
    if (p)
    {
        /* 左子树线索化. */
        InThreading(p->lchild, pre);

        /* 若当前结点 p 左子为空, 令 p 指向其前驱 pre. */
        if (p->lchild == NULL)
        {
            p->LTag = Thread;
            p->lchild = (*pre);
        }

        /* 若前驱 pre 不为空, 且 pre 右子为空, 则令 pre 指向 p. */
        if (*pre != NULL && (*pre)->rchild == NULL)
        {
            (*pre)->RTag = Thread;
            (*pre)->rchild = p; /* 右子树回指. */
        }

        /* 更新最后访问的结点. */
        (*pre) = p;

        /* 右子树线索化. */
        InThreading(p->rchild, pre);
    }

    return;
}

Status InOrder(ThreadTree T, Status (*Visit)(ElemType e))
{
    ThreadNode *p = T;

    /* 空树或遍历结束时. */
    while (p->LTag != Thread)
    {
        p = p->lchild;
    }

    for (; p != NULL; p = p->rchild)
    {
        Visit(p->data);
    }

    return OK;
}

Status PostOrderThreading(ThreadTree *T)
{
    /* 初始化前驱结点. */
    ThreadNode *pre = NULL;

    /* 若二叉树不为空. */
    if (T != NULL)
    {
        /* 开始后序线索化. */
        PreThreading(*T, &pre);

        /* 处理最后一个结点. */
        pre->rchild = NULL;
        pre->RTag = Thread;
    }

    return OK;
}

void PostThreading(ThreadTree p, ThreadNode **pre)
{
    if (p != NULL)
    {
        /* 先左右子树线索化, 体现后续思想. */
        PostThreading(p->lchild, pre);
        PostThreading(p->rchild, pre);

        /* 若当前结点 p 左子为空, 令 p 指向其前驱 pre. */
        if (p->lchild == NULL)
        {
            p->LTag = Thread;
            p->lchild = (*pre);
        }

        /* 若前驱 pre 不为空, 且 pre 右子为空, 则令 pre 指向 p. */
        if ((*pre) != NULL && (*pre)->rchild == NULL)
        {
            (*pre)->RTag = Thread;
            (*pre)->rchild = p;
        }

        /* 更新最后访问结点. */
        (*pre) = p;
    }

    return;
}

Status PostOrder(ThreadTree T, Status (*Visit)(ElemType e))
{
    return OK;
}
