/*******************************
 * @file  : bitree.h
 * @brief : 二叉树的二叉链表存储表示
 * @author: 田世豪
 * @date  : 2020-2-11
 * ****************************/

#pragma once

#include "linkedqueue.h"
#include "predefconst.h"

typedef struct BiTNode
{
    TElemType data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

// 构造一个空的二叉树 T.
Status InitTree(BiTree *T)
{
    if (*T == NULL)
        return ERROR;

    *T = NULL;
    return OK;
} // InitTree

/*******************************************************************************
 * 即使 BiTree 类型和 BiTNode * 等价, 表面上是指针,但是在指针传递时, 仍要取 BiTree 的地址,
 * 因为在子函数中需要改变是指针本身 ( 改变了结点间的链接关系 ), 而不是指针指向的内容, 
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

    CreateTree(T, fp);

    fclose(fp);

    return OK;
} // CreateBiTree

// 创建二叉树的内部函数
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

// void PrintTree(BiTree T)
// {
//     int level, width;
//     int i, j, k, w;
//     int begin;
//     int distance;
//     TElemType **tmp;
//     LinkedQueue Q;
//     // LinkQueue Q;
//     BiTree e;

//     // 遇到空树则无需继续计算
//     if (BiTreeEmpty(T))
//     {
//         printf("\n");
//         return;
//     }

//     level = BiTreeDepth(T);         // （完全）二叉树结构高度
//     width = (int)pow(2, level) - 1; // （完全）二叉树结构宽度

//     // 动态创建行
//     tmp = (TElemType **)malloc(level * sizeof(TElemType *));

//     // 动态创建列
//     for (i = 0; i < level; i++)
//     {
//         tmp[i] = (TElemType *)malloc(width * sizeof(TElemType));

//         // 初始化内存值为空字符
//         memset(tmp[i], '\0', width);
//     }

//     // 借助队列实现层序遍历
//     InitQueue(&Q);
//     EnQueue(&Q, T);

//     // 遍历树中所有元素，将其安排到二维数组tmp中合适的位置
//     for (i = 0; i < level; i++)
//     {
//         w = (int)pow(2, i);                 // 二叉树当前层的宽度
//         distance = width / w;               // 二叉树当前层的元素间隔
//         begin = width / (int)pow(2, i + 1); // 二叉树当前层首个元素之前的空格数

//         for (k = 0; k < w; k++)
//         {
//             DeQueue(&Q, &e);

//             if (e == NULL)
//             {
//                 EnQueue(&Q, NULL);
//                 EnQueue(&Q, NULL);
//             }
//             else
//             {
//                 j = begin + k * (1 + distance);
//                 tmp[i][j] = e->data;

//                 // 左孩子入队
//                 EnQueue(&Q, e->lchild);

//                 // 右孩子入队
//                 EnQueue(&Q, e->rchild);
//             }
//         }
//     }

//     for (i = 0; i < level; i++)
//     {
//         for (j = 0; j < width; j++)
//         {
//             if (tmp[i][j] != '\0')
//             {
//                 printf("%c", tmp[i][j]);
//             }
//             else
//             {
//                 printf(" ");
//             }
//         }
//         printf("\n");
//     }
// }