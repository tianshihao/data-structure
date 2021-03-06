﻿/**
 * @file dlinklist.h
 * @author 田世豪 (tianshihao@4944@126.com)
 * @brief 双向链表头文件.
 * @version 0.2
 * @date 2020-12-16
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef DLINKLIST_H
#define DLINKLIST_H

#include <status.h>

typedef int ElemType;

/* 双向链表的存储类型. */
typedef struct DNode
{
    ElemType data;
    int freq;
    struct DNode *prior, *next;
} DNode, *DLinklist;

/**
 * @brief 构造一个空的双向链表 L. 只有头结点.
 * @param L 指向未初始化过的双向链表的指针.
 */
Status InitList_D(DLinklist *L);

/**
 * @brief 头插法.
 * @param L 指向已存在双向链表的指针.
 * @param e 要插入的数据元素.
 */
Status HeadInsert_D(DLinklist L, ElemType e);

/**
 * @brief 尾插法.
 * @param L 指向已存在双向链表的指针.
 * @param e 要插入的数据元素.
 */
Status TailInsert_D(DLinklist L, ElemType e);

/**
 * @brief 按序号查找结点值.
 * @param L 双向链表.
 * @param i 序号. 取值范围 0 <= i <= length.
 * @return 返回指向符合要求结点的指针, 否则返回 NULL.
 */
DNode *GetElem_D(DLinklist L, int i);

/**jie
 * @brief 按值查找表结点.
 * @param L 双向链表.
 * @param e 要查找的值.
 * @return 返回指向符合要求结点的指针, 否则返回 NULL.
 */
DNode *LocateElem_D(DLinklist L, ElemType e);

/**
 * @brief 20, 每在链表中进行一次 Locate() 操作, 令元素值为 e 的结点中的 freq 域的值
 * 增加 1, 并使此链表保持按访问程度非递增 (递减) 的顺序排序, 同时最近访问的结点
 * 排在频度相同的节点后面, 以便使频度访问的结点总是靠近表头. 其实就是相同频底的
 * 结点, 先访问的排在前面, 后访问的排在后面.
 * 
 * @param L 双向链表.
 * @return DNode* 返回指向符合要求结点的指针, 否则返回 NULL.
 */
DNode *LccateElem_D2(DLinklist L, ElemType e);

/**
 * @brief 在双向链表 L 第 i 个元素之前插入数据元素 e.
 * @param L 指向已存在双向链表.
 * @param i 插入的位置. 取值范围 1 <= i <= length+1.
 * @param e 要插入的元素.
 * */
Status ListInsert_D(DLinklist *L, int i, ElemType e);

/**
 * @brief 删除双向链表 L 中第 i 个元素.
 * @param L 指向已存在双向链表.
 * @param i 插入的位置. 取值范围 1 <= i <= length.
 * @param e 要插入的元素.
 * */
Status ListDelete_D(DLinklist *L, int i);

/**
 * @brief 返回双向链表 L 中数据元素个数.
 * @param L 双向链表.
 * @return L 的数据元素个数.
 */

int ListLength_D(DLinklist L);
/**
 * @brief 打印双向链表.
 * @param L 待打印双向链表.
 */
void PrintList_D(DLinklist L);

#endif /* DLINKLIST_H */
