/***************************
 * @file  : uselinkedlist.h
 * @brief : 测试单向链表
 * @author: 田世豪
 * @date  : 2020-1-25
 * ************************/

#include "linkedlist.h"

// 自定义比较函数
Status MyCompare(ElemType a, ElemType b)
{
    return a >= b;
} // MyCompare

Status MyVisit(ElemType e)
{
    return e > 0;
} // MyVisit

int main()
{
    LinkedList odd, even;
    InitList(&odd);
    InitList(&even);

    for (int i = 1, e = 1; i <= 3; ++i, e += 2)
        ListInsert_L(&odd, i, e);

    for (int i = 1, e = 2; i <= 5; ++i, e += 2)
        ListInsert_L(&even, i, e);

    PrintList(odd);
    PrintList(even);

    LinkedList sequence;
    MergeList_L(&odd, &even, &sequence, MyCompare);

    PrintList(sequence);

    return 0;
}
