/**
 * @file  : linklist.h
 * @brief : 双链表
 * @author: 田世豪
 * @date  : 2020-7-26
 * */

#pragma once

#include <chapter1/status.h>
#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct DNode
{
    ElemType data;
    struct DNode *prior, *next;
} DNode, *DLinklist;

/**
 * 构造一个空的双链表 L. 只有头结点.
 * @param L 指向未初始化过的双链表的指针.
 */
Status InitList_DL(DLinklist *L);

/**
 * @brief 头插法.
 * @param L 指向已存在双链表的指针.
 * @param e 要插入的数据元素.
 */
Status HeadInsert_DL(DLinklist *L, ElemType e);

/**
 * @brief 尾插法.
 * @param L 指向已存在双链表的指针.
 * @param e 要插入的数据元素.
 */
Status TailInsert_DL(DLinklist *L, ElemType e);

/**
 * @brief 按序号查找结点值.
 * @param L 双链表.
 * @param i 序号. 取值范围 0 <= i <= length.
 * @return 返回指向符合要求结点的指针, 否则返回 NULL.
 */
DNode *GetElem_DL(DLinklist L, int i);

/**
 * @brief 按值查找表结点.
 * @param L 双链表.
 * @param e 要查找的值.
 * @return 返回指向符合要求结点的指针, 否则返回 NULL.
 */
DNode *LocateElem_DL(DLinklist L, ElemType e);

/**
 * 在线性双链表 L 第 i 个元素之前插入数据元素 e.
 * @param L 指向已存在双链表.
 * @param i 插入的位置. 取值范围 1 <= i <= length.
 * @param e 要插入的元素.
 * */
Status ListInsert_DL(DLinklist *L, int i, ElemType e);

/**
 * 删除线性链表中第 i 个元素.
 * @param L 指向已存在双链表.
 * @param i 插入的位置. 取值范围 1 <= i <= length.
 * @param e 要插入的元素.
 * */
Status ListDelete_DL(DLinklist *L, int i);

/**
 * @brief 返回 L 中数据元素个数.
 * @param L 双链表.
 * @return L 的数据元素个数.
 */
int ListLength_DL(DLinklist L);
/**
 * @brief 打印双链表.
 * @param L 待打印双链表.
 */
void PrintList_DL(DLinklist L);