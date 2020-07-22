#include <chapter_2/sqlist.h>

Status InitList_Sq(SqList *L)
{
    L->elem = (ElemType *)malloc(sizeof(ElemType) * INITSIZE);
    if (!L->elem)
        exit(OVERFLOW);

    L->length = 0;
    L->listsize = INITSIZE;

    return OK;
} // InitList_Sq

Status DestoryList_Sq(SqList *L)
{
    free(L);

    return OK;
}

int ListLength_Sq(SqList L)
{
    return L.listsize;
}

Status ListInsert_Sq(SqList *L, int i, ElemType e)
{
    // 判断 i 的范围是否有效.
    if (i < 1 || i > L->length + 1)
    {
        return ERROR;
    }

    // 当前存储空间已满, 不能插入.
    if (L->length >= MAXSIZE)
    {
        return ERROR;
    }

    // 将第 i 个元素及以后的元素后移.
    for (int j = L->length; j >= i; --j)
    {
        L->elem[j] = L->elem[j - 1];
    }

    // 在第 i 个元素之前插入数据元素 e.
    L->elem[i - 1] = e;

    L->length++;

    return OK;
} // ListInsert_Sq

Status ListDelete_Sq(SqList *L, int i, ElemType *e)
{
    // 判断 i 的范围是否有效
    if (i < 1 || i > L->length)
        return ERROR;

    // 将被删除的元素赋给 e.
    *e = L->elem[i - 1];

    // 将第 i 个位置后的元素前移.
    for (int j = i; j < L->length; ++j)
    {
        L->elem[j - 1] = L->elem[j];
    }

    // 顺序表长度减 1.
    L->length--;

    return OK;
} // ListDelete_Sq