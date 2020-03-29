/*******************************************************************************
 * @file  : bitree.h
 * @brief : 二叉树的二叉链表存储表示
 * @author: 田世豪
 * @date  : 2020-2-11
 * ****************************************************************************/

#pragma once

#include "predefconst.h"
#include "sqstack.h"

typedef struct BiTNode
{
    ElemType data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

// 构造一个空的二叉树 T.
Status InitTree(BiTree *T)
{
    // *T 即为指向 BiTNode 的指针.
    if (*T == NULL) // 修改指针指向的内容.
        return ERROR;

    *T = NULL; // 使得指针指向 NULL.

    return OK;
} // InitTree

/*******************************************************************************
 * 即使 BiTree 类型和 BiTNode * 等价, 表面上是指针, 但是在指针传递时, 仍要取 BiTree 的地址,
 * 因为在子函数中需要改变是指针本身的内容 (改变了结点间的链接关系), 而不是指针指向的内容, 
 * 因此子函数参数列表中写 BiTree *T, 否则只能传递一份指向某二叉树的指针, 在子函数中修改了二叉树
 * 后, 主函数中的指针仍然指向 NULL.
 * 
 * 简单的理解是, 在 C 语言中, 若想使得传递的参数实际被修改, 则在子函数中加上一层指针总是没有错的,
 * 不论传递的参数是什么, 包括指针.
 * ****************************************************************************/

void CreateTree(BiTree *T, FILE *fp);

// 按先序次序输入二叉树中结点的值, 空格字符表示空树,
// 构造二叉链表表示的二叉树 T.
// 参考了
// https://github.com/kangjianwei/Data-Structure/blob/master/Dev-C%2B%2B/CourseBook/0602_BiTree/BiTree.cpp
Status CreateBiTree(BiTree *T, char *path)
{
    FILE *fp = fopen(path, "r");
    if (fp == NULL)
        return ERROR;

    // 此时只用修改指针指向的内容, 而不用修改指针本身的内容, 所以只传递指向二叉树的地址.
    CreateTree(T, fp);

    fclose(fp);

    return OK;
} // CreateBiTree

// 按先序次序读入字符, 创建二叉树.
void CreateTree(BiTree *T, FILE *fp)
{
    char ch = 0;

    // 读取当前结点的值
    if (fp == NULL)
        scanf("%c", &ch);
    else
        ch = fgetc(fp);

    if (ch == '^')
        *T = NULL;
    else
    {
        // 生成根结点
        *T = (BiTNode *)malloc(sizeof(BiTNode));
        if (!*T)
            exit(OVERFLOW);

        (*T)->data = ch;
        CreateTree(&((*T)->lchild), fp); // 创建左子树
        CreateTree(&((*T)->rchild), fp); // 创建右子树
    }
} // CreateTree

// 采用二叉链表存储结构, Visit 是对结点操作的应用函数.
// 先序遍历二叉树 T, 对每个结点调用函数 Visit 一次且仅一次.
// 一旦 Visit() 失败, 则操作失败.
Status PreOrderTraverse(BiTree T, Status (*Visit)(ElemType e))
{
    if (T)
    {
        if (Visit(T->data))
        {
            if (PreOrderTraverse(T->lchild, Visit))
            {
                if (PreOrderTraverse(T->rchild, Visit))
                    return OK;
            }
        }
        return ERROR;
    }
    else
        return OK;
} // PreOrderTraverse

// 采用二叉链表存储结构, Visit 是对结点操作的应用函数.
// 中序遍历二叉树 T, 对每个结点调用函数 Visit 一次且仅一次.
// 一旦 Visit() 失败, 则操作失败.
Status InOrderTraverse(BiTree T, Status (*Visit)(ElemType e))
{
    if (T)
    {
        if (InOrderTraverse(T->lchild, Visit))
            if (Visit(T->data))
                if (InOrderTraverse(T->rchild, Visit))
                    return OK;

        return ERROR;
    }
    else
        return OK;
} // InOrderTraverse

// 采用二叉链表存储结构, Visit 是对结点操作的应用函数.
// 后序遍历二叉树 T, 对每个结点调用函数 Visit 一次且仅一次.
// 一旦 Visit() 失败, 则操作失败.
Status PostOrderTraverse(BiTree T, Status (*Visit)(ElemType e))
{
    if (T)
    {
        if (PostOrderTraverse(T->lchild, Visit))
            if (PostOrderTraverse(T->rchild, Visit))
                if (Visit(T->data))
                    return OK;

        return ERROR;
    }
    else
        return OK;
} // PostOrderTraverse

// 采用二叉链表存储结构, Visit 是对结点操作的应用函数.
// 层序遍历二叉树 T, 对每个结点调用函数 Visit 一次且仅一次.
// 一旦 Visit() 失败, 则操作失败.
// Status LevelOrderTraverse(BiTree T, Status (*Visit)(ElemType e))
// {
//     SqStack S;
//     InitStack(&S);
//     Push(&S, )
// } // LevelOrderTraverse
