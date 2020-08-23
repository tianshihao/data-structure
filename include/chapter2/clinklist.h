/**
 * @file  : clinklist.h
 * @brief : 单项循环链表
 * @author: 田世豪
 * @date  : 2020-7-26
 * */

#ifndef CLINKLIST_H
#define CLINKLIST_H

#include <chapter1/status.h>
#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct CNode
{
    ElemType data;
    struct CNode *next;
} CNode, *CLinklist;

/**
 * @brief 构造一个空的单项循环链表 L. 只有头结点.
 * @param L 指向未初始化过的链表的指针.
 */
Status InitList_C(CLinklist *L);

/**
 * @brief 头插法.
 * @param L 指向已存在单项循环链表的指针.
 * @param e 要插入的数据元素.
 */
Status HeadInsert_C(CLinklist *L, ElemType e);

/**
 * @brief 尾插法.
 * @param L 指向已存在单项循环链表的指针.
 * @param e 要插入的数据元素.
 */
Status TailInsert_C(CLinklist *L, ElemType e);

/**
 * @brief 按序号查找结点值.
 * @param L 单项循环链表.
 * @param i 序号. 取值范围 0 <= i <= length.
 * @return 返回指向符合要求结点的指针, 否则返回 NULL.
 */
CNode *GetElem_C(CLinklist L, int i);

/**
 * @brief 按值查找表结点.
 * @param L 单项循环链表.
 * @param e 要查找的值.
 * @return 返回指向符合要求结点的指针, 否则返回 NULL.
 */
CNode *LocateElem_C(CLinklist L, ElemType e);

/**
 * @brief 在单项循环链表 L 第 i 个元素之前插入数据元素 e.
 * @param L 指向已存在单项循环链表.
 * @param i 插入的位置. 取值范围 1 <= i <= length+1.
 * @param e 要插入的元素.
 * */
Status ListInsert_C(CLinklist *L, int i, ElemType e);

/**
 * @brief 删除单项循环链表中第 i 个元素.
 * @param L 指向已存在链表.
 * @param i 插入的位置. 取值范围 1 <= i <= length.
 * @param e 要插入的元素.
 * */
Status ListDelete_C(CLinklist *L, int i);

/**
 * @brief 返回 L 中数据元素个数.
 * @param L 单项循环链表.
 * @return L 的数据元素个数.
 */
int ListLength_C(CLinklist L);
/**
 * @brief 打印单向循环链表 L.
 * @param L 待打印单向循环链表.
 */
void PrintList_C(CLinklist L);

/**
 * @brief 19, 在一个结点值均为正整数的单向循环链表中, 反复找出最小值并输出,然后
 * 将该结点从链表中删除, 直到链表为空, 在删除头结点.
 * 
 * @param L 单向循环链表.
 * @return OK 操作完成返回 OK.
 */
Status DelAll(CLinklist *L);

#endif // CLINKLIST_H
