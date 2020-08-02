/**
 * @file  : linklist.h
 * @brief : 单向链表
 * @author: 田世豪
 * @date  : 2020-1-25
 * */

#pragma once

#include <chapter1/status.h>
#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

// 结点类型
typedef struct LNode
{
    ElemType data;
    struct LNode *next;
} LNode, *Linklist;

/**
 * @brief 构造一个空的单向链表 L. 只有头结点.
 * @param L 指向未初始化过的单向链表的指针.
 */
Status InitList_L(Linklist *L);

/**
 * @brief 头插法.
 * @param L 指向已存在单向链表的指针.
 * @param e 要插入的数据元素.
 */
Status HeadInsert_L(Linklist *L, ElemType e);

/**
 * @brief 尾插法.
 * @param L 指向已存在单向链表的指针.
 * @param e 要插入的数据元素.
 */
Status TailInsert_L(Linklist *L, ElemType e);

/**
 * @brief 按序号查找结点值.
 * @param L 单向链表.
 * @param i 序号. 取值范围 0 <= i <= length.
 * @return 返回指向符合要求结点的指针, 否则返回 NULL.
 */
LNode *GetElem_L(Linklist L, int i);

/**
 * @brief 按值查找表结点.
 * @param L 单向链表.
 * @param e 要查找的值.
 * @return 返回指向符合要求结点的指针, 否则返回 NULL.
 */
LNode *LocateElem_L(Linklist L, ElemType e);

/**
 * @brief 在单向链表 L 第 i 个元素之前插入数据元素 e.
 * @param L 指向已存在单向链表.
 * @param i 插入的位置. 取值范围 1 <= i <= length+1.
 * @param e 要插入的元素.
 * */
Status ListInsert_L(Linklist *L, int i, ElemType e);

/**
 * 删除单向链表 L 中第 i 个元素.
 * @param L 指向已存在单向链表.
 * @param i 插入的位置. 取值范围 1 <= i <= length.
 * @param e 要插入的元素.
 * */
Status ListDelete_L(Linklist *L, int i);

/**
 * @brief 返回单向链表 L 中数据元素个数.
 * @param L 单向链表.
 * @return L 的数据元素个数.
 */
int ListLength_L(Linklist L);

/**
 * @brief 打印单向链表.
 * @param L 待打印单向链表.
 */
void PrintList_L(Linklist L);

/*******************************2021王道数据结构习题*******************************

/**
 * @brief 3 逆序打印单向链表.
 * @param L 待打印单向链表.
 */
void RPrintList_L(Linklist L);

/**
 * @brief 5 逆置链表.
 * @param L 待逆置单向链表.
 * */
Linklist Reverse_L1(Linklist L);

/**
 * @brief 5 逆置链表.
 * @param L 待逆置单向链表.
 * */
Linklist Reverse_L2(Linklist L);

/**
 * @brief 6, 使单向链表元素递增.
 * @param L 待排序单向链表.
 * */
void Sort(Linklist *L);

/**
 * @brief 7, 删除单向链表中所有介于给定的两个值之间的元素的元素.
 * @param L 待删除元素单向链表.
 * @param min 删除范围左值.
 * @param max 删除范围右值.
 * */
Status RangeDelete(Linklist *L, ElemType min, ElemType max);

/**
 * @brief 10, 将单向链表 A 分解成两个单向链表 A 和 B, 使得 A 表中含有原表中序号为
 * 奇数的元素, 而 B 表中含有原表中序号为偶数的元素, 并使其相对顺序保持不变.
 * @param A 待拆分单向链表.
 * @return 包含原表偶数位结点的单向链表.
 * */
Linklist Split(Linklist *A);

/**
 * @brief 11, 将单向链表 A 分解成两个单向链表 A 和 B, 使得 A 表中含有原表中序号为
 * 奇数的元素, 而 B 表中含有原表中序号为偶数的元素, A 中元素保持原相对位置不变,
 * B 中元素相对位置为原表逆序.
 * @param A 待拆分单向链表.
 * @return 包含原表偶数位结点且逆序的单向链表.
 * */
Linklist Split2(Linklist *A);

/**
 * @brief 12, 删除单项链表 L 中重复出现的元素.
 * @param L 单向链表.
 * */
Status DeleteRepeat(Linklist *L);

/**
 * @brief 13, 将两个元素按值递增的线性表归并为一个元素按值递减的元素的单链表, 并
 * 用原来的两个单链表的结点存放归并后的单链表.
 * @param A 待归并递增单向链表.
 * @param B 待归并递增单向链表.
 * @return 归并后的单向链表.
 * */
Linklist MergeList(Linklist *A, Linklist *B);

/**
 * @brief 14, 从两个有序递增的单向链表中找到公共元素产生新的单向链表, 且不破坏原表.
 * @param A 待合并单向链表.
 * @param B 待合并单向链表.
 * @note 时间复杂度为 O(min(len1, len2)), 空间复杂度为 O(n).
 * @return 合并产生的新链表.
 * */
Linklist GetCommon(Linklist A, Linklist B);

/**
 * @brief 15, 已知两个元素递增链表, 其中元素不重复, 计算其交集, 存放于原表中.
 * 时间复杂度为 O(len1 + len2). 
 * @see GetCommon(), 和它的区别是更少的空间复杂度 O(1), 没有额外的内存空间, 
 * 但是修改了原表.
 * @param A 待归并单项链表.
 * @param B 待归并单项链表.
 * @return Linklist 交集.
 */
Linklist Union(Linklist *A, Linklist *B);

/**
 * @brief 16, 判断序列 B 是否是序列 A 的连续子序列.
 * @param A 单向链表.
 * @param B 单向链表.
 * @return TRUE B 是 A 的连续子序列.
 * @return FALSE  B 不是 A 的连续子序列.
 */
Status Pattern(Linklist A, Linklist B);

// // 依次对 L 的每个元素调用函数 visit(). 一旦 visit() 失败, 则操作失败.
// Status ListTraverse(Linklist L, Status (*visit)(ElemType));

// /***************************利用基本操作实现的高级操作******************************/

// // 已知单单向链表 La 和 Lb 的元素按值非递减排列.
// // 归并 La 和 Lb 得到新的单单向链表 Lc, Lc 的元素也按值非线性递减排列.
// Status MergeList_L(Linklist *La, Linklist *Lb, Linklist *Lc, Status (*compare)(ElemType, ElemType));
