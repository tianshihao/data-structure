/**
 * @file  : bitree.h
 * @brief : binary tree header.
 * @author: 田世豪
 * @date  : 2020-2-11
 * */

#pragma once

#include <chapter1/status.h>
#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

/**
 * @brief 二叉树结点.
 */
typedef struct BiTNode
{
    ElemType data; // data field.
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

/**
 * @brief 构造一个空的二叉树 T. 其实就是将指向而差的的指针置空.
 * 
 * @param T 指向二叉树
 * @return OK 操作成功返回 OK.
 * @return ERROE 操作失败返回 ERROR.
 */
Status InitTree(BiTree *T);

/**
  @brief 按先序次序输入二叉树中结点的值, 空格字符表示空树, 构造二叉链表表示的
 * 二叉树 T. 参考了
 * 
 * @param T 指向二叉树的指针.
 * @param path 存储二叉树序列的 .txt 文件的路径.
 * @return OK 操作成功返回 OK.
 * @return ERROR 操作失败返回 ERROR. 
 */
Status CreateBiTree(BiTree *T, const char *path);

/**
 * @brief 从文件中先序次序读取二叉树序列, 递归地建立二叉树.
 * 
 * @param T pointer to binary tree.
 * @param fp 存储二叉树信息的文件.
 */
void CreateTree(BiTree *T, FILE *PreSeq);

/**
 * @brief 采用二叉链表存储结构, Visit 是对结点操作的应用函数. 先序遍历二叉树 T,
 * 对每个结点调用函数 Visit 一次且仅一次. 一旦 Visit() 失败, 则操作失败.
 * 
 * @param T 非空二叉树.
 * @param Visit 应用函数.
 * @return OK 操作成功返回 OK.
 * @return ERROR 操作失败返回 ERROR.
 */
Status PreOrderTraverse(BiTree T, Status (*Visit)(ElemType e));

/**
 * @brief 采用二叉表存储结构, Visit 是对结操作的应用函数. 中序遍历二叉 T, 对每个
 * 结点调用函数 Visit 一次且仅一次. 一旦 Visit() 失败, 则操作失败.
 * 
 * @param T 非空二叉树.
 * @param Visit 应用函数.
 * @return OK 操作成功返回 OK.
 * @return ERROR 操作失败返回 ERROR.
 */
Status InOrderTaverse(BiTree , Status (*Visit)(ElemType e));

/**
 * @brief 采用二叉链表存储结构, Visit 是对结点操作的应用函数. 后序遍历二叉树 T,
 * 对每个结点调用函数 Visit 一次且仅一次. 一旦 Visit() 失败, 则操作失败.
 * 
 * @param T 非空二叉树.
 * @param Visit 应用函数.
 * @return OK 操作成功返回 OK.
 * @return ERROR 操作失败返回 ERROR.
 */
Status PostOrderTraverse(BiTree T, Status (*Visit)(ElemType e));
