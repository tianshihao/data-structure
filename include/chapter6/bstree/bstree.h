/**
 * @file bstree.h
 * @author tianshihao
 * @brief 二叉排序树
 * @version 0.1
 * @date 2020-09-01
 * @copyright Copyright (c) 2020
 */

#ifndef BSTREE_H
#define BSTREE_H

#include <chapter1/status.h>
#include <stdio.h>
#include <stdlib.h>

typedef int BSTElem;

/**
 * @brief 二叉排序树结点.
 */
typedef struct BSTNode
{
    BSTElem data;
    struct BSTNode *lchild, *rchild;
} BSTNode, *BSTree;

/**
 * @brief 初始化二叉排序树.
 * @param T 空的二叉排序树.
 * @return OK 操作成功返回 OK. 
 * @return ERROR 操作成功返回 ERROR. 
 */
Status InitTree_BS(BSTree *T);

/**
 * @brief 向二叉排序树中插入新数据.
 * @param T 二叉排序树.
 * @param e 数据.
 * @return OK 操作成功返回 OK. 
 * @return ERROR 操作成功返回 ERROR. 
 */
Status Insert_BST(BSTree *T, BSTElem e);

/**
 * @brief 以给定序列重新建立二叉排序树.
 * @param T 空的二叉排序树.
 * @param str 给定序列.
 * @param n 序列长度.
 * @return OK 操作成功返回 OK. 
 * @return ERROR 操作成功返回 ERROR. 
 */
Status CreateTree_BST(BSTree *T, BSTElem *str, int n);

/**
 * @brief 在二叉排序树中查找元素.
 * @param T 二叉排序树.
 * @param e 要查找的元素.
 * @return OK 操作成功返回 OK. 
 * @return ERROR 操作成功返回 ERROR. 
 */
Status SearchElem(BSTree T, BSTElem e);

#endif // BSTREE_H
