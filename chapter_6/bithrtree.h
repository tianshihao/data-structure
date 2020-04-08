/**
 * @file    bithrtree.h
 * @author  田世豪
 * @brief   线索二叉树 Threaded Binary Tree
 * @date    2020年3月31日
 * */

#pragma once

#include "predefconst.h"

// Link == 0 表示指针, Thread == 1 表示线索.
typedef enum PointerTag
{
    Link,
    Thread
} PointerTag;

typedef struct BiThrNode
{
    ElemType data;
    struct BiThrNode *lchild, *rchild;
    PointerTag LTag, RTag;
} BiThrNode, *BiThrTree;

// 初始化线索二叉树, Thrt 是头节点.
Status InitTree_Thr(BiThrTree *Thrt)
{
    if (!((*Thrt) = (BiThrTree)malloc(sizeof(BiThrNode))))
        exit(OVERFLOW);

    (*Thrt)->data = 0;

    BiThrNode *root = NULL;
    (*Thrt)->lchild = root;
    // (*Thrt)->rchild = root;

    return OK;
} // InitBiThrTree

void CreateTree(BiThrTree *T, FILE *fp);

Status CreateThrTree(BiThrTree *T, char *path)
{
    FILE *fp = fopen(path, "r");

    if (fp == NULL)
    {
        return ERROR;
    }

    CreateTree(&((*T)->lchild), fp);

    fclose(fp);

    return OK;
} // CreateThrTree

// 先序创建二叉树
void CreateTree(BiThrTree *T, FILE *fp)
{
    char ch = 0;
    ch = fgetc(fp);

    if (ch == '^')
    {
        (*T) = NULL;
    }
    else if (ch == '#')
    {
        return;
    }
    else
    {
        (*T) = (BiThrNode *)malloc(sizeof(BiThrNode));
        if (!(*T))
        {
            exit(OVERFLOW);
        }

        (*T)->data = ch;
        CreateTree(&((*T)->lchild), fp);
        CreateTree(&((*T)->rchild), fp);
    }
} // CreateTree

// Status InOrderThreading(BiThrTree *T, )

// 前序遍历, 验证建树成功.
Status PreOrderTraverse(BiThrTree T, Status (*Visit)(ElemType e))
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
        printf(" ^ ");
        return OK;
    }
} // PreOrderTraverse

Status InOrderTraverse(BiThrTree T, Status (*Visit)(ElemType e))
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
        printf(" ^ ");
        return OK;
    }

} // InOrderTraverse

void InThreading(BiThrTree p, BiThrTree *pre);

// 中序遍历二叉树 T, 并将其中序线索化, Thrt 指向头节点
Status InOrderThreading(BiThrTree *Thrt, BiThrTree T)
{
    (*Thrt)->LTag = Link;
    (*Thrt)->RTag = Thread;

    // 右指针回指.
    (*Thrt)->rchild = *Thrt;

    // 如果二叉树空, 则左指针回指.
    if (!T)
    {
        (*Thrt)->lchild = *Thrt;
    }
    else
    {
        (*Thrt)->lchild = T;

        // 前驱结点.
        BiThrTree pre = (*Thrt);

        InThreading(T, &pre);

        // 最后一个结点线索化.
        pre->rchild = (*Thrt);
        pre->RTag = Thread;
        (*Thrt)->rchild = pre;
    }

    return OK;
} // InOrderThreading

// ! 这里遇到了一个BUG, 书中的伪代码未说明 pre 是否为全局变量, 而数据结构中也没有存储 pre, 所
// ! 以我先将其作为一个局部变量传递. 但这个中序线索化的算法是一个递归形式的回溯, 系统会维护一个
// ! 函数调用栈, 当回溯到上一次使用 InThreading 的状态时, 本次的 pre 会消失, 恢复到上一次的
// ! 状态, 所以会出现后继设置失败的情况.
// 改进方法有两个, 设置全局变量 pre, 或者将函数参数改为传递 pre 的地址, 这样
void InThreading(BiThrTree p, BiThrTree *pre)
{
    if (p)
    {
        // 左子树线索化.
        InThreading(p->lchild, pre);

        // 前驱线索.
        if (!(p->lchild))
        {
            p->LTag = Thread;
            p->lchild = (*pre);
        }

        // 后继线索.
        if (!((*pre)->rchild))
        {
            (*pre)->RTag = Thread;
            (*pre)->rchild = p; // 右子树回指
        }

        (*pre) = p;

        // 右子树线索化.
        InThreading(p->rchild, pre);
    }

    return;
} // InThreading

// T 指向头结点, 头结点的左链 lchild 指向根结点.
// 中序遍历二叉线索树 T 的非递归算法, 对每个数据元素调用函数 Visit.
Status InOrderTraverse_Thr(BiThrTree T, Status (*Visit)(ElemType e))
{
    // p 指向根结点.
    BiThrNode *p = T->lchild;

    // 空树或遍历结束时.
    while (p != T)
    {
        while (p->LTag != Thread)
        {
            p = p->lchild;
        }

        if (!Visit(p->data))
        {
            return ERROR;
        }

        // 访问后继结点.
        // 找到最左叶结点, 就可以轻松地访问其后继结点.
        while ((p->RTag == Thread) && (p->rchild != T))
        {
            p = p->rchild;
            Visit(p->data);
        }

        p = p->rchild;
    }

    return OK;
} // InOrderTraverse_Thr