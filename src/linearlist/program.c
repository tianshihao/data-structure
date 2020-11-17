/**
 * @file  : program.c
 * @brief : 使用第二章的数据结构.
 * @author: 田世豪
 * @date  : 2020-07-22
 * */

#include <linearlist/clinklist.h>
#include <linearlist/dclinklist.h>
#include <linearlist/dlinklist.h>
#include <linearlist/linklist.h>
#include <linearlist/sqlist.h>

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
    Linklist L;

    InitList_L(&L);

    TailInsert_L(&L, 1);
    TailInsert_L(&L, 2);
    TailInsert_L(&L, 3);
    TailInsert_L(&L, 4);
    TailInsert_L(&L, 5);
    TailInsert_L(&L, 6);
    TailInsert_L(&L, 7);
    TailInsert_L(&L, 8);
    TailInsert_L(&L, 9);

    PrintList_L(L);

    ChangeList(&L);

    PrintList_L(L);

    return;
}

void UseCLinklist()
{
    CLinklist L;

    InitList_C(&L);

    TailInsert_C(&L, 5);
    TailInsert_C(&L, 4);
    TailInsert_C(&L, 7865);
    TailInsert_C(&L, 124);
    TailInsert_C(&L, 65);

    DelAll(&L);

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

    PrintList_DL(L);

    DNode *node = LccateElem_DL2(&L, 1);
    node = LccateElem_DL2(&L, 2);
    node = LccateElem_DL2(&L, 3);
    node = LccateElem_DL2(&L, 4);
    node = LccateElem_DL2(&L, 1);
    node = LccateElem_DL2(&L, 2);
    node = LccateElem_DL2(&L, 3);
    node = LccateElem_DL2(&L, 4);
    node = LccateElem_DL2(&L, 5);

    PrintList_DL(L);

    printf("\n->>>%d\n", node->prior->freq);

    return;
}

void UseDCLinklist()
{
    DCLinklist L;

    InitList_DC(&L);

    TailInsert_DC(&L, 1);
    TailInsert_DC(&L, 2);
    TailInsert_DC(&L, 3);
    TailInsert_DC(&L, 2);
    TailInsert_DC(&L, 1);

    PrintList_DC(L);

    if (Symmetry(L))
    {
        printf("yes\n");
    }
    else
    {
        printf("no\n");
    }

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
