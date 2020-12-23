/**
 * @file threadtree.h
 * @author 田世豪 (tianshihao@4944@126.com)
 * @brief 线索二叉树头文件
 * @version 0.2
 * @date 2020-12-21
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef THREADTREE_H
#define THREADTREE_H

#include <status.h>

typedef char ElemType;

/* 指针标签, Link == 0 表示指针, Thread == 1 表示线索. */
typedef enum PointerTag
{
    Link,  /* 链接. */
    Thread /* 线索. */
} PointerTag;

/* 线索二叉树存储结构. */
typedef struct ThreadNode
{
    ElemType data;
    struct ThreadNode *lchild, *rchild;
    PointerTag LTag, RTag;
} ThreadNode, *ThreadTree;

/**
 * @brief 初始化线索二叉树, T 是头节点.
 * 
 * @param T 指向线索二叉树.
 * @return OK 操作成功返回 OK.
 * @return ERROR 操作失败返回 ERROR.
 */
Status InitTree_Thread(ThreadTree *T);

/**
  @brief 按先序次序输入二叉树中结点的值, 空格字符表示空树, 构造二叉链表表示的
 * 二叉树 T. 参考了
 * 
 * @param T 指向线索二叉树的指针.
 * @param path 存储二叉树序列的 .txt 文件的路径.
 * @return OK 操作成功返回 OK.
 * @return ERROR 操作失败返回 ERROR. 
 */
Status CreateThreadTree(ThreadTree *T, char *path);

/**
 * @brief 从文件中先序次序读取二叉树序列, 递归地建立二叉树.
 * 
 * @param T 指向线索二叉树的指针.
 * @param fp 存储二叉树信息的文件.
 */
void CreateTree_Thread(ThreadTree *T, FILE *fp);

/**
 * @brief 采用二叉链表存储结构, Visit 是对结点操作的应用函数. 先序遍历二叉树 T,
 * 对每个结点调用函数 Visit 一次且仅一次. 一旦 Visit() 失败, 则操作失败.
 * 
 * @param T 非空线索二叉树.
 * @param Visit 应用函数.
 * @return OK 操作成功返回 OK.
 * @return ERROR 操作失败返回 ERROR.
 */
Status PreOrderTraverse_Thread(ThreadTree T, Status (*Visit)(ElemType e));

/**
 * @brief 采用二叉表存储结构, Visit 是对结操作的应用函数. 中序遍历二叉 T, 对每个
 * 结点调用函数 Visit 一次且仅一次. 一旦 Visit() 失败, 则操作失败.
 * 
 * @param T 非空线索二叉树.
 * @param Visit 应用函数.
 * @return OK 操作成功返回 OK.
 * @return ERROR 操作失败返回 ERROR.
 */
Status InOrderTraverse_Thread(ThreadTree T, Status (*Visit)(ElemType e));

/**
 * @brief 通过先序遍历建立先序线索二叉树的主过程算法.
 * 
 * @param T 线索二叉树.
 * @param Head 线索二叉树头结点.
 * @return OK 操作成功返回 OK.
 * @return ERROR 操作失败返回 ERROR.
 */
Status PreOrderThreading(ThreadTree *T);

/**
 * @brief 先序线索化.
 * 
 * @param p 正在访问的结点.
 * @param pre 刚刚访问过的结点.
 */
void PreThreading(ThreadTree p, ThreadNode **pre);

/**
 * @brief 先序线索化遍历, 通过建立的线索, 输出先序遍历的结果.
 * 
 * @param T 线索二叉树.
 * @param Visit 应用函数.
 * @return OK 操作成功返回 OK.
 * @return ERROR 操作失败返回 ERROR.
 */
Status PreOrder(ThreadTree T, Status (*Visit)(ElemType e));

/**
 * @brief 通过中序遍历建立中序线索二叉树的主过程算法.
 * 
 * @param T 线索二叉树.
 * @param Head 线索二叉树头结点.
 * @return OK 操作成功返回 OK.
 * @return ERROR 操作失败返回 ERROR.
 */
Status InOrderThreading(ThreadTree *T);

/**
 * ! 这里遇到了一个BUG, 书中的伪代码未说明 pre 是否为全局变量, 而数据结构中也没
 * ! 有存储 pre, 所以我先将其作为一个局部变量传递. 但这个中序线索化的算法是一个
 * ! 递归形式的回溯, 系统会维护一个函数调用栈, 当回溯到上一次使用 InThreading 的
 * ! 状态时, 本次的 pre 会消失, 恢复到上一次的状态, 所以会出现后继设置失败的情况.
 * 改进方法有两个, 设置全局变量 pre, 或者将函数参数改为传递 pre 的地址.
 */
/**
 * @brief 中序线索化.
 * 
 * @param p 正在访问的结点.
 * @param pre 刚刚访问过的结点.
 */
void InThreading(ThreadTree p, ThreadNode **pre);

/**
 * @brief 中序线索化遍历, 通过建立的线索, 输出中序遍历的结果.
 * 
 * @param T 线索二叉树.
 * @param Visit 应用函数.
 * @return OK 操作成功返回 OK.
 * @return ERROR 操作失败返回 ERROR.
 */
Status InOrder(ThreadTree T, Status (*Visit)(ElemType e));

/**
 * @brief 通过后序遍历建立后序线索二叉树的主过程算法.
 * 
 * @param T 线索二叉树.
 * @param Head 线索二叉树头结点.
 * @return OK 操作成功返回 OK.
 * @return ERROR 操作失败返回 ERROR.
 */
Status PostOrderThreading(ThreadTree *T);

/**
 * @brief 后序线索化.
 * 
 * @param p 正在访问的结点.
 * @param pre 刚刚访问过的结点.
 */
void PostThreading(ThreadTree p, ThreadNode **pre);

/**
 * @brief 后序线索化遍历, 通过建立的线索, 输出后序遍历的结果.
 * 
 * @param T 线索二叉树.
 * @param Visit 应用函数.
 * @return OK 操作成功返回 OK.
 * @return ERROR 操作失败返回 ERROR.
 */
Status PostOrder(ThreadTree T, Status (*Visit)(ElemType e));

#endif /* THREADTREE_H */
