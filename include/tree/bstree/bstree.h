/**
 * @file bstree.h
 * @author 田世豪 (tianshihao@4944@126.com)
 * @brief 二叉排序树头文件
 * @version 0.2
 * @date 2020-12-21
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef BSTREE_H
#define BSTREE_H

#include <status.h>

typedef int BSTElem;
typedef BSTElem KeyType;

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
 * 
 * @param T 空的二叉排序树.
 * @return OK 操作成功返回 OK. 
 * @return ERROR 操作成功返回 ERROR. 
 */
Status InitTree_BS(BSTree *T);

/**
 * @brief 向二叉排序树中插入新数据.
 * 
 * @param T 二叉排序树.
 * @param e 数据.
 * @return OK 操作成功返回 OK. 
 * @return ERROR 操作成功返回 ERROR. 
 */
Status Insert_BST(BSTree *T, BSTElem e);

/**
 * @brief 以给定序列重新建立二叉排序树.
 * 
 * @param T 空的二叉排序树.
 * @param str 给定序列.
 * @param n 序列长度.
 * @return OK 操作成功返回 OK. 
 * @return ERROR 操作成功返回 ERROR. 
 */
Status CreateTree_BST(BSTree *T, BSTElem *str, int n);

/**
 * @brief 在二叉排序树中查找元素.
 * 
 * @param T 二叉排序树.
 * @param e 要查找的元素.
 * @return OK 操作成功返回 OK. 
 * @return ERROR 操作成功返回 ERROR. 
 */
Status SearchElem(BSTree T, BSTElem e);

/**
 * @brief 王道 196/10, 从大到小输出二叉排序树中所有值不小于 k 的关键字. 先遍历
 * 右子树, 再访问根结点, 后遍历左子树.
 * 
 * @param T 二叉排序树.
 * @param k 关键字.
 */
void Output(BSTree T, KeyType k);

#endif /* BSTREE_H */
