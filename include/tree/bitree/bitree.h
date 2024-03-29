﻿/**
 * @file  : bitree.h
 * @brief : binary tree header. 这个二叉树的结点存储的是字符型变量,
 * 方便输出查看.
 * @author: 田世豪
 * @date  : 2020-2-11
 * */

#ifndef BITREE_H
#define BITREE_H

#include <status.h>

typedef char BiTElemType;

/**
 * @brief 二叉树结点.
 */
typedef struct BiTNode {
  // data field.
  BiTElemType data;
  struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

/**
 * @brief 构造一个空的二叉树 t. 其实就是将指向而差的的指针置空.
 * @param t 指向二叉树
 * @return OK 操作成功返回 OK.
 * @return ERROR 操作失败返回 ERROR.
 */
Status InitTreeBinary(BiTree *t);

/**
  @brief 按先序次序输入二叉树中结点的值, ^字符表示空树, 构造二叉链表表示的
 * 二叉树 t. 参考了
 * @param t 指向二叉树的指针.
 * @param path 存储二叉树序列的 .txt 文件的路径.
 * @return OK 操作成功返回 OK.
 * @return ERROR 操作失败返回 ERROR.
 */
Status CreateBinaryTreeFromFile(BiTree *t, const char *path);

/**
 * @brief 从文件中先序次序读取二叉树序列, 递归地建立二叉树.
 * @param t pointer to binary tree.
 * @param fp 存储二叉树信息的文件.
 */
void CreateTreeBinary(BiTree *t, FILE *PreSeq);

/**
 * @brief 采用二叉链表存储结构, Visit 是对结点操作的应用函数. 先序遍历二叉树 t,
 * 对每个结点调用函数 Visit 一次且仅一次. 一旦 Visit() 失败, 则操作失败.
 * @param t 非空二叉树.
 * @param Visit 应用函数.
 * @return OK 操作成功返回 OK.
 * @return ERROR 操作失败返回 ERROR.
 */
Status PreOrderTraverseBinaryRecur(BiTree t, Status (*Visit)(BiTElemType e));

/**
 * @brief 借助顺序栈, 非递归地先序遍历二叉树.
 * @param t 非空二叉树.
 * @param Visit 应用函数.
 * @return OK 操作成功返回 OK.
 * @return ERROR 操作失败返回 ERROR.
 */
Status PreOrderTraverseBinaryNonRecur(BiTree t, Status (*Visit)(BiTElemType e));

/**
 * @brief 采用二叉表存储结构, Visit 是对结操作的应用函数. 中序遍历二叉 t, 对每个
 * 结点调用函数 Visit 一次且仅一次. 一旦 Visit() 失败, 则操作失败.
 * @param t 非空二叉树.
 * @param Visit 应用函数.
 * @return OK 操作成功返回 OK.
 * @return ERROR 操作失败返回 ERROR.
 */
Status InOrderTraverseBinaryRecur(BiTree t, Status (*Visit)(BiTElemType e));

/**
 * @brief 借助顺序栈, 非递归地中序遍历二叉树.
 * @param t 非空二叉树.
 * @param Visit 应用函数.
 * @return OK 操作成功返回 OK.
 * @return ERROR 操作失败返回 ERROR.
 */
Status InOrderTraverseBinaryNonRecur(BiTree t, Status (*Visit)(BiTElemType e));

/**
 * @brief 采用二叉链表存储结构, Visit 是对结点操作的应用函数. 后序遍历二叉树 t,
 * 对每个结点调用函数 Visit 一次且仅一次. 一旦 Visit() 失败, 则操作失败.
 * @param t 非空二叉树.
 * @param Visit 应用函数.
 * @return OK 操作成功返回 OK.
 * @return ERROR 操作失败返回 ERROR.
 */
Status PostOrderTraverseBinaryRecur(BiTree t, Status (*Visit)(BiTElemType e));

/**
 * @brief 王道数据结构3, 借助顺序栈, 非递归地后序遍历二叉树.
 * @param t 非空二叉树.
 * @param Visit 应用函数.
 * @return OK 操作成功返回 OK.
 * @return ERROR 操作失败返回 ERROR.
 * @todo @see FindAncestor, @see FindCommonAncestor, 看是否能将这两个函数中的
 * 退栈操作在本函数中找到, 如果能, 改写成明确的具有退栈操作的形式.
 */
Status PostOrderTraverseBinaryNonRecur(BiTree t,
                                       Status (*Visit)(BiTElemType e));

/**
 * @brief 层序遍历二叉树.
 * @param t 非空二叉树.
 * @param Visit 应用函数.
 * @return OK 操作成功返回 OK.
 * @return ERROR 操作失败返回 ERROR.
 */
Status LevelOrderTraverseBinary(BiTree t, Status (*Visit)(BiTElemType e));

/**
 * @brief 王道数据结构4, 自下而上, 自右向左遍历二叉树.
 * @note 调试没问题, 直接运行内存溢出.
 * @param t 非空二叉树.
 * @param Visit 应用函数.
 * @return OK 操作成功返回 OK.
 * @return ERROR 操作失败返回 ERROR.
 */
Status InvertLevelTraverseBinary(BiTree t, Status (*Visit)(BiTElemType e));

/**
 * @brief 王道数据结构5, 非递归算法求二叉树高度. 根据层序遍历修改.
 * 其实就是层序遍历的层数.
 * @param t 非空二叉树.
 * @return int 返回二叉树高度.
 */
int BiTreeHeight(BiTree t);

/**
 * @brief 王道数据结构149/6, 由先序遍历序列和中序遍历序列构建二叉树.
 * @param pre_order 先序遍历序列.
 * @param pre_l 先序遍历序列第一个结点索引.
 * @param pre_r 先序遍历序列最后一个结点索引.
 * @param in_order 中序遍历序列.
 * @param in_l 中序遍历序列第一个结点索引.
 * @param in_r 中序遍历序列最后一个结点索引.
 * @return BiTree 构建好的二叉树.
 */
BiTree PreInCreate(BiTElemType *pre_order, int preL, int preR,
                   BiTElemType *in_order, int InL, int InR);

/**
 * @brief 王道数据结构150/9, 交换所有结点的左右子树.
 * @param t 二叉树.
 * @return OK 操作成功返回 OK.
 * @return ERROR 操作失败返回 ERROR.
 */
Status SwapSubTree(BiTree t);

/**
 * @brief 王道数据结构150/12, 在二叉树中查找值为 x 的结点, 打印其所有祖先, 假定
 * 值为 x 的结点不多于一个.
 * @param t 二叉树.
 * @param x 要寻找其祖先的结点.
 * @return OK 操作成功返回 OK.
 * @return ERROR 操作失败返回 ERROR.
 */
Status FindAncestor(BiTree t, BiTElemType x);

/**
 * @brief 王道数据结构150/13, 找到二叉树中任意两个结点的最近公共祖先.
 * @param t 二叉树.
 * @param p 指向二叉树结点的指针.
 * @param q 指向二叉树结点的指针.
 * @return BiTNode* 最近公共祖先.
 */
BiTNode *FindCommonAncestor(BiTree t, BiTNode *p, BiTNode *q);

/**
 * @brief 王道数据结构150/14, 求二叉树的宽度. 即拥有结点最多的一层的结点数.
 * @see LevelOrderTraverseBinary
 * @param t 非空二叉树.
 * @return int 二叉树的宽度.
 */
int BiTreeWidth(BiTree t);

/**
 * @brief 王道数据结构151/15, 由满二叉树的先序遍历序列得到其后续遍历序列.
 * @param Pre 先序遍历序列.
 * @param preL
 * @param preR
 * @param Post 后续遍历序列
 * @param postL
 * @param postR
 * @see PreInCreate
 */
void PreToPost(BiTElemType *Pre, int preL, int preR, BiTElemType *Post,
               int postL, int postR);

/**
 * @brief 王道数据结构151/17, 判断两颗二叉树是否相似. 所谓二叉树相似是指 T1 和
 * T2 都是空树或都只有一个根结点; 或 T1 的左子树和 T2 的左子树时相似的, 且 T1 的
 * 右子树和 T2 的右子树是相似的.
 * 所谓相同的结构, 可以通过同步遍历, 例如中序遍历.
 * @param T1 二叉树.
 * @param T2 二叉树.
 * @return TRUE T1 和 T2 相似.
 * @return FALSE T1 和 T2 不相似.
 */
Status Similar(BiTree T1, BiTree T2);

/**
 * @brief 以谍对先序遍历的方式计算二叉树的 WPL.
 * @param t 二叉树.
 * @return int WPL.
 */
int WPL(BiTree t);

/**
 * @brief 递归的方式计算 WPL.
 * @param t 二叉树.
 * @param depth 当前所在深度.  根结点所在深度为 1.
 * @return int
 */
int WPLPreOrder(BiTree t, int depth);

/**
 * @brief 以层序遍历的方式计算 WPL.
 * @see BiTreeHeight.
 * @param t 二叉树.
 * @return int WPL.
 */
int WPLLevelOrder(BiTree t);

/**
 * @brief 195/6, 给定一棵二叉树, 判定其是否为二叉排序树. 采用中序遍历递归算法.
 * @param t 二叉树.
 * @return TRUE 是二叉排序树.
 * @return FALSE 不是二叉排序树.
 */
Status JudgeBST(BiTree t);

/**
 * @brief 195/8, 给定一棵二叉树, 判定其是否为平衡二叉树. 采用后续遍历递归算法.
 * 还可以顺便求出高度.
 * @param tree 二叉树.
 * @param tree_height 二叉树的高度.
 * @param tree_balance 平衡标记.
 * @return TRUE 是平衡二叉树.
 * @return FALSE 不是平衡二叉树.
 * @note AVL 树首先是一棵平衡的二叉排序树, 但是这里的 AVL 树只注重平衡,
 * 只是平衡二叉树.
 */
Status JudgeAVL(BiTree tree, size_t *tree_height, Status *tree_balance);

#endif  // BITREE_H
