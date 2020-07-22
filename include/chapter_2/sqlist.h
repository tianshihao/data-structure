#ifndef SQLIST_H
#define SQLIST_H

#include <chapter_0/status.h>
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
 * 在顺序表 L 中第 i 个位置以前插入新的数据元素 e, L 的长度加1.
 * @param L 指向已存在的顺序表的指针.
 * @param i 位置索引, 大于等于 1.
 * @param e 待插入元素.
 * */
Status ListInsert_Sq(SqList *L, int i, ElemType e);

/**
 * 删除 L 的第 i 个数据元素, 并用 e 返回其值, L 的长度减一.
 * @param L 指向已存在的顺序表的指针.
 * @param i 索引位置.
 * @param e 存放删除数据元素.
 * */
Status ListDelete_Sq(SqList *L, int, ElemType *e);

#endif // SQLIST_H