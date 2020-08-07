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
