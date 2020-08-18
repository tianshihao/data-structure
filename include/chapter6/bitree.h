/**
 * @file  : bitree.h
 * @brief : binary tree header. 这个二叉树的结点存储的是字符型变量, 方便输出查看.
 * @author: 田世豪
 * @date  : 2020-2-11
 * */

#pragma once

#include <chapter1/status.h>
#include <stdio.h>
#include <stdlib.h>

typedef char ElemType;

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
 * @param T 指向二叉树
 * @return OK 操作成功返回 OK.
 * @return ERROR 操作失败返回 ERROR.
 */
Status InitTree_Binary(BiTree *T);

/**
  @brief 按先序次序输入二叉树中结点的值, ^字符表示空树, 构造二叉链表表示的
 * 二叉树 T. 参考了
 * @param T 指向二叉树的指针.
 * @param path 存储二叉树序列的 .txt 文件的路径.
 * @return OK 操作成功返回 OK.
 * @return ERROR 操作失败返回 ERROR. 
 */
Status CreateBinaryTree(BiTree *T, const char *path);

/**
 * @brief 从文件中先序次序读取二叉树序列, 递归地建立二叉树.
 * @param T pointer to binary tree.
 * @param fp 存储二叉树信息的文件.
 */
void CreateTree_Binary(BiTree *T, FILE *PreSeq);

/**
 * @brief 采用二叉链表存储结构, Visit 是对结点操作的应用函数. 先序遍历二叉树 T,
 * 对每个结点调用函数 Visit 一次且仅一次. 一旦 Visit() 失败, 则操作失败.
 * @param T 非空二叉树.
 * @param Visit 应用函数.
 * @return OK 操作成功返回 OK.
 * @return ERROR 操作失败返回 ERROR.
 */
Status PreOrderTraverse_Binary(BiTree T, Status (*Visit)(ElemType e));

/**
 * @brief 借助顺序栈, 非递归地先序遍历二叉树.
 * @param T 非空二叉树.
 * @param Visit 应用函数.
 * @return OK 操作成功返回 OK.
 * @return ERROR 操作失败返回 ERROR.
 */
Status PreOrderTraverse_Binary2(BiTree T, Status (*Visit)(ElemType e));

/**
 * @brief 采用二叉表存储结构, Visit 是对结操作的应用函数. 中序遍历二叉 T, 对每个
 * 结点调用函数 Visit 一次且仅一次. 一旦 Visit() 失败, 则操作失败.
 * @param T 非空二叉树.
 * @param Visit 应用函数.
 * @return OK 操作成功返回 OK.
 * @return ERROR 操作失败返回 ERROR.
 */
Status InOrderTraverse_Binary(BiTree T, Status (*Visit)(ElemType e));

/**
 * @brief 借助顺序栈, 非递归地中序遍历二叉树.
 * @param T 非空二叉树.
 * @param Visit 应用函数.
 * @return OK 操作成功返回 OK.
 * @return ERROR 操作失败返回 ERROR.
 */
Status InOrderTraverse_Binary2(BiTree T, Status (*Visit)(ElemType e));

/**
 * @brief 采用二叉链表存储结构, Visit 是对结点操作的应用函数. 后序遍历二叉树 T,
 * 对每个结点调用函数 Visit 一次且仅一次. 一旦 Visit() 失败, 则操作失败.
 * @param T 非空二叉树.
 * @param Visit 应用函数.
 * @return OK 操作成功返回 OK.
 * @return ERROR 操作失败返回 ERROR.
 */
Status PostOrderTraverse_Binary(BiTree T, Status (*Visit)(ElemType e));

/**
 * @brief 王道数据结构3, 借助顺序栈, 非递归地后序遍历二叉树.
 * @param T 非空二叉树.
 * @param Visit 应用函数.
 * @return OK 操作成功返回 OK.
 * @return ERROR 操作失败返回 ERROR.
 */
Status PostOrderTraverse_Binary2(BiTree T, Status (*Visit)(ElemType e));

/**
 * @brief 层序遍历二叉树.
 * @param T 非空二叉树.
 * @param Visit 应用函数.
 * @return OK 操作成功返回 OK.
 * @return ERROR 操作失败返回 ERROR.
 */
Status LevelOrderTraverse_Binary(BiTree T, Status (*Visit)(ElemType e));

/**
 * @brief 王道数据结构4, 自下而上, 自右向左遍历二叉树.
 * @note 调试没问题, 直接运行内存溢出.
 * @param T 非空二叉树.
 * @param Visit 应用函数.
 * @return OK 操作成功返回 OK.
 * @return ERROR 操作失败返回 ERROR.
 */
Status InvertLevelTraverse_Binary(BiTree T, Status (*Visit)(ElemType e));

/**
 * @brief 王道数据结构5, 非递归算法求二叉树高度.
 * @param T 非空二叉树.
 * @return int 返回二叉树高度.
 */
int BiTreeDepth(BiTree T);

/**
 * @brief 由先序遍历序列和中序遍历序列构建二叉树.
 * @param pre 先序遍历序列.
 * @param In 中序遍历学列.
 * @param preL 先序遍历序列第一个结点下标.
 * @param preR 先序遍历序列最后一个结点序列.
 * @param InL 中序遍历序列第一个结点下标.
 * @param InR 中序遍历序列最后一个结点序列.
 * @return BiTree 构建好的二叉树.
 */
BiTree PreInCreate(ElemType *Pre, ElemType *In,
                   int preL, int preR, int InL, int InR);

/**
 * @brief 王道数据结构150/9, 交换所有结点的左右子树.
 * @param T 二叉树.
 * @return OK 操作成功返回 OK.
 * @return ERROR 操作失败返回 ERROR.
 */
Status Swap(BiTree T);

/**
 * @brief 王道数据结构150/12, 在二叉树中查找值为 x 的结点, 打印其所有祖先, 假定
 * 值为 x 的结点不多于一个.
 * @param T 二叉树.
 * @param x 要寻找其祖先的结点.
 * @return OK 操作成功返回 OK.
 * @return ERROR 操作失败返回 ERROR.
 */
Status FindAncestor(BiTree T, ElemType x);

/**
 * @brief 王道数据结构150/13, 找到二叉树中任意两个结点的最近公共祖先.
 * @param T 二叉树.
 * @param p 指向二叉树结点的指针.
 * @param q 指向二叉树结点的指针.
 * @return BiTNode* 最近公共祖先.
 */
BiTNode *FindCommonAncestor(BiTree T, BiTNode *p, BiTNode *q);
