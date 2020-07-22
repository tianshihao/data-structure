#include <chapter_2/sqlist.h>

#include <stdio.h>

int main()
{
    SqList L;

    InitList_Sq(&L);

    ListInsert_Sq(&L, 1, 5);
    ListInsert_Sq(&L, 1, 1);
    ListInsert_Sq(&L, 1, 4);
    ListInsert_Sq(&L, 1, 2);

    return 0;
}