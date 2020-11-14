/**
 * @file  : bitree.h
 * @brief : binary tree header. 这个二叉树的结点存储的是字符型变量, 方便输出查看.
 * @author: 田世豪
 * @date  : 2020-2-11
 * */

#ifndef BITREE_H
#define BITREE_H

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
 * @todo @see FindAncestor, @see FindCommonAncestor, 看是否能将这两个函数中的
 * 退栈操作在本函数中找到, 如果能, 改写成明确的具有退栈操作的形式.
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
 * @brief 王道数据结构5, 非递归算法求二叉树高度. 根据层序遍历修改.
 * @param T 非空二叉树.
 * @return int 返回二叉树高度.
 */
int BiTreeHeight(BiTree T);

/**
 * @brief 王道数据结构149/6, 由先序遍历序列和中序遍历序列构建二叉树.
 * @param preOrder 先序遍历序列.
 * @param preL 先序遍历序列第一个结点索引.
 * @param preR 先序遍历序列最后一个结点索引.
 * @param InOrder 中序遍历序列.
 * @param InL 中序遍历序列第一个结点索引.
 * @param InR 中序遍历序列最后一个结点索引.
 * @return BiTree 构建好的二叉树.
 */
BiTree PreInCreate(ElemType *preOrder,
                   int preL, int preR,
                   ElemType *InOrder,
                   int InL, int InR);

/**
 * @brief 王道数据结构150/9, 交换所有结点的左右子树.
 * @param T 二叉树.
 * @return OK 操作成功返回 OK.
 * @return ERROR 操作失败返回 ERROR.
 */
Status SwapSubTree(BiTree T);

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

/**
 * @brief 王道数据结构150/14, 求二叉树的宽度. 即拥有结点最多的一层的结点数.
 * @see LevelOrderTraverse_Binary
 * @param T 非空二叉树.
 * @return int 二叉树的宽度.
 */
int BiTreeWidth(BiTree T);

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
void PreToPost(ElemType *Pre,
               int preL, int preR,
               ElemType *Post,
               int postL, int postR);

/**
 * @brief 王道数据结构151/17, 判断两颗二叉树是否相似. 所谓二叉树相似是指 T1 和
 * T2 都是空树或都只有一个根结点; 或 T1 的左子树和 T2 的左子树时相似的, 且 T1 的
 * 右子树和 T2 的右子树是相似的.
 * @param T1 二叉树.
 * @param T2 二叉树.
 * @return TRUE T1 和 T2 相似.
 * @return FALSE T1 和 T2 不相似. 
 */
Status Similar(BiTree T1, BiTree T2);

/**
 * @brief 以谍对先序遍历的方式计算二叉树的 WPL.
 * @param T 二叉树.
 * @return int WPL.
 */
int WPL(BiTree T);

/**
 * @brief 递归的方式计算 WPL.
 * @param T 二叉树.
 * @param depth 当前所在深度.
 * @return int 
 */
int WPLPreOrder(BiTree T, int depth);

/**
 * @brief 以层序遍历的方式计算 WPL.
 * @see BiTreeHeight.
 * @param T 二叉树.
 * @return int WPL.
 */
int WPLLevelOrder(BiTree T);

/**
 * @brief 195/6, 给定一棵二叉树, 判定其是否为二叉排序树. 采用中序遍历递归算法.
 * @param T 二叉树.
 * @return TRUE 是二叉排序树.
 * @return FALSE 不是二叉排序树.
 */
Status JudgeBST(BiTree T);

/**
 * @brief 195/8, 给定一棵二叉树, 判定其是否为平衡二叉树. 采用后续遍历递归算法.
 * 还可以顺便求出高度.
 * @param T 二叉树.
 * @param height 二叉树的高度.
 * @param balance 平衡标记.
 * @return TRUE 是平衡二叉树.
 * @return FALSE 不是平衡二叉树.
 * @note AVL 树一般是一棵平衡的二叉排序树, 但是这里的 AVL 只注重平衡, 只是平衡二
 * 叉树.
 */
Status JudgeAVL(BiTree T, int *height, int *balance);

#endif // BITREE_H
