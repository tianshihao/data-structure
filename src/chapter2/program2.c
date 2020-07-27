/**
 * @file  : program2.c
 * @brief : 使用第二章的数据结构.
 * @author: 田世豪
 * @date  : 2020-07-22
 * */

#include <chapter2/clinklist.h>
#include <chapter2/dclinklist.h>
#include <chapter2/dlinklist.h>
#include <chapter2/linklist.h>
#include <chapter2/sqlist.h>

void UseSqlist();
void UseLinklist();
void UseCLinklist();
void UseDLinklist();
void UseDCLinklist();
Status MyCompare(ElemType e1, ElemType e2);

int main()
{
    // UseSqlist();

    UseLinklist();

    // UseCLinklist();

    // UseDLinklist();

    // UseDCLinklist();

    // UseSLinklist();

    return 0;
}

void UseSqlist()
{
    SqList A, B, C;

    // 初始化顺序表.
    InitList_Sq(&A);
    InitList_Sq(&B);
    InitList_Sq(&C);

    // 如果顺序表为空, 向顺序表中插入数据元素.
    if (ListEmpty_Sq(A))
    {
        ListInsert_Sq(&A, 1, 9);
        ListInsert_Sq(&A, 1, 7);
        ListInsert_Sq(&A, 1, 5);
        ListInsert_Sq(&A, 1, 3);
        ListInsert_Sq(&A, 1, 1);
    }
    if (ListEmpty_Sq(B))
    {
        ListInsert_Sq(&B, 1, 8);
        ListInsert_Sq(&B, 1, 6);
        ListInsert_Sq(&B, 1, 4);
        ListInsert_Sq(&B, 1, 2);
        ListInsert_Sq(&B, 1, 0);
    }

    printf("测试Merge()\n");

    Merge(A, B, &C);

    PrintList_Sq(C);

    return;
}

void UseLinklist()
{
    Linklist odd, even;

    InitList_L(&odd);
    InitList_L(&even);

    for (int i = 1, e = 1; i <= 5; ++i, e += 2)
    {
        TailInsert_L(&odd, e);
    }

    for (int i = 1, e = 2; i <= 5; ++i, e += 2)
    {
        TailInsert_L(&even, e);
    }

    ListInsert_L(&odd, 6, 100);

    PrintList_L(odd);

    Linklist r = Reverse_L2(odd);

    PrintList_L(r);

    printf("\nlength = %d\n", ListLength_L(odd));

    // Linklist sequence;
    // MergeList_L(&odd, &even, &sequence, MyCompare);

    // PrintList(sequence);

    return;
}

void UseCLinklist()
{
    CLinklist L;

    InitList_C(&L);

    TailInsert_C(&L, 1);
    TailInsert_C(&L, 2);
    TailInsert_C(&L, 3);
    TailInsert_C(&L, 4);
    TailInsert_C(&L, 5);

    PrintList_C(L);

    ListDelete_C(&L, 6);

    PrintList_C(L);

    return;
}

void UseDLinklist()
{
    DLinklist L;

    InitList_DL(&L);

    TailInsert_DL(&L, 1);
    TailInsert_DL(&L, 2);
    TailInsert_DL(&L, 3);
    TailInsert_DL(&L, 4);
    TailInsert_DL(&L, 5);

    ListInsert_DL(&L, 6, 100);

    PrintList_DL(L);

    printf(">>>%d\n", ListLength_DL(L));

    ListDelete_DL(&L, 0);

    PrintList_DL(L);

    printf(">>>%d\n", ListLength_DL(L));

    return;
}

void UseDCLinklist()
{
    DCLinklist L;

    InitList_DC(&L);

    TailInsert_DC(&L, 1);
    TailInsert_DC(&L, 2);
    TailInsert_DC(&L, 3);
    TailInsert_DC(&L, 4);
    TailInsert_DC(&L, 5);

    PrintList_DC(L);

    ListInsert_DC(&L, 7, 999);

    PrintList_DC(L);

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
