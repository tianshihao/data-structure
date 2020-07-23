﻿/**
 * @file  : sqlist.h
 * @brief : 顺序表.
 * @author: 田世豪
 * @date  : 2020-07-21
 * */

#ifndef SQLIST_H
#define SQLIST_H

#include <chapter1/status.h>
#include <stdio.h>
#include <stdlib.h>

#define INITSIZE 100 // 顺序表存储空间的初始分配量.
#define INCREMENT 10 // 顺序表存储空间的分配增量.
#define MAXSIZE 200  // 顺序表的最大长度.

typedef int ElemType;

// 顺序表的存储结构.
typedef struct SqList
{
    ElemType *elem; // 存储空间基址.
    int length;     // 顺序表当前长度.
    int listsize;   // 当前分配的存储容量.
} SqList;

/**
 * 构造一个空的顺序表 L.
 * @param L 未初始化过的顺序表的指针.
 * */
Status InitList_Sq(SqList *L);

/**
 * @brief 销毁顺序表 L.
 * @param L 指向已存在的顺序表的指针.
 * */
Status DestoryList_Sq(SqList *L);

/**
 * 返回 L 中数据元素个数.
 * @param L 已存在的顺序表.
 * */
int ListLength_Sq(SqList L);

/**
 * 返回 L 中第 1 个于 e 满足关系 compare() 的数据元素的位序. 若这样的数据元素
 * 不存在, 则返回值为 0.
 * @param L 已存在的顺序表.
 * @param e 待比较数据元素.
 * @param Compare 比较函数.
 * */
int LocateElem_Sq(SqList L, ElemType e, Status (*Compare)(ElemType, ElemType));

/**
 * 用 e 返回 L 中第 i 个数据元素的值.
 * @param L 已存在的顺序表.
 * @param i 索引位置, 取值范围 1 <= i <= length.
 * @param e 存放获得的数据元素.
 * */
void GetElem_Sq(SqList L, int i, ElemType *e);

/**
 * 在顺序表 L 中第 i 个位置以前插入新的数据元素 e, L 的长度加1.
 * @param L 指向已存在的顺序表的指针.
 * @param i 位置索引, 取值范围 1 <= i <= length + 1.
 * @param e 待插入元素.
 * */
Status ListInsert_Sq(SqList *L, int i, ElemType e);

/**
 * 删除 L 的第 i 个数据元素, 并用 e 返回其值, L 的长度减一.
 * @param L 指向已存在的顺序表的指针.
 * @param i 索引位置, 取值范围 1 <= i <= length.
 * @param e 存放删除数据元素.
 * */
Status ListDelete_Sq(SqList *L, int i, ElemType *e);

/**
 * 输出操作. 按前后顺序输出顺序表 L 的所有数据元素.
 * @param L 已存在的顺序表.
 * */
void PrintList_Sq(SqList L);

/**
 * 若 L 为空表, 则返回 TRUE, 否则返回 FALSE.
 * @param L 已存在的顺序表.
 * */
Status ListEmpty_Sq(SqList L);

#endif // SQLIST_H