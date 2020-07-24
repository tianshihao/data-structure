/**
 * @file  : program2.c
 * @brief : 使用第二章的数据结构.
 * @author: 田世豪
 * @date  : 2020-07-22
 * */

#include <chapter2/linklist.h>
#include <chapter2/sqlist.h>

void UseSqlist();
void UseLinklist();
Status MyCompare(ElemType e1, ElemType e2);

int main()
{
    UseSqlist();

    // UseLinklist();

    return 0;
}

void UseSqlist()
{
    SqList L;

    // 初始化顺序表.
    InitList_Sq(&L);

    // 如果顺序表为空, 向顺序表中插入数据元素.
    if (ListEmpty_Sq(L))
    {
        ListInsert_Sq(&L, 1, 15);
        ListInsert_Sq(&L, 1, 12);
        ListInsert_Sq(&L, 1, 8);
        ListInsert_Sq(&L, 1, 6);
        ListInsert_Sq(&L, 1, 6);
        ListInsert_Sq(&L, 1, 5);
        ListInsert_Sq(&L, 1, 4);
        ListInsert_Sq(&L, 1, 2);
    }

    // 输出 L 中的数据元素.
    PrintList_Sq(L);

    printf("测试DelST1()\n");

    DelST1(&L, 3, 8);

    PrintList_Sq(L);

    printf("%d\n", L.length);

    return;
}

void UseLinklist()
{
    LinkList odd, even;
    InitList_L(&odd);
    InitList_L(&even);

    for (int i = 1, e = 1; i <= 3; ++i, e += 2)
    {
        ListInsert_L(&odd, i, e);
    }

    for (int i = 1, e = 2; i <= 5; ++i, e += 2)
    {
        ListInsert_L(&even, i, e);
    }
    PrintList(odd);
    PrintList(even);

    LinkList sequence;
    MergeList_L(&odd, &even, &sequence, MyCompare);

    PrintList(sequence);

    return;
}

Status MyCompare(ElemType e1, ElemType e2)
{
    if (e1 == e2)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
