/**
 * @file  : sqlist.c
 * @brief : 顺序表.
 * @author: 田世豪
 * @date  : 2020-07-21
 * */

#include <linearlist/sqlist.h>

Status InitList_Sq(SqList *L)
{
    L->elem = (ElemType *)malloc(sizeof(ElemType) * LIST_INIT_SIZE);
    if (!L->elem)
    {
        exit(OVERFLOW);
    }

    L->length = 0;
    L->listsize = LIST_INIT_SIZE;

    return OK;
} // InitList_Sq

Status DestoryList_Sq(SqList *L)
{
    free(L);

    return OK;
} // DestoryList_Sq

int ListLength_Sq(SqList L)
{
    return L.listsize;
} // ListLength_Sq

int LocateElem_Sq(SqList L, ElemType e, Status (*Compare)(ElemType, ElemType))
{
    int i = 0;

    for (i = 0; i < L.length; ++i)
    {
        if ((*Compare)(L.elem[i], e))
        {
            return i;
        }
    }

    return 0;
} // LocateElem_Sq

void GetElem_Sq(SqList L, int i, ElemType *e)
{
    *e = L.elem[i];

    return;
} // GetElem_Sq

Status ListInsert_Sq(SqList *L, int i, ElemType e)
{
    // 判断 i 的范围是否有效.
    // 如果要在表尾插入元素, i 的值应为表长加 1; 在表头插入元素, i 应为 1.
    // 逻辑上顺序表位置索引是 1, 2, 3, ...
    // 算法实现时, 索引为 0, 1, 2, ...
    if (i < 1 || i > L->length + 1)
    {
        return ERROR;
    }

    // 当前存储空间已满, 不能插入.
    if (L->length >= LIST_MAX_SIZE)
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
    {
        return ERROR;
    }

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

void PrintList_Sq(SqList L)
{
    for (int i = 0; i < L.length; ++i)
    {
        printf("%d\n", L.elem[i]);
    }

    return;
} // PrintList_Sq

Status ListEmpty_Sq(SqList L)
{
    if (L.length == 0)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
} // ListEmpty_Sq

Status Del_Min(SqList *L, ElemType *value)
{
    // 如果顺序表为空.
    if (ListEmpty_Sq(*L))
    {
        // 现实错误信息.
        printf("error, the list is empty.\n");

        // 并退出运行.
        return ERROR;
    }

    // 假定第 0 号元素最小.
    *value = L->elem[0];

    // 用已记录最小元素索引.
    int pos = 0;

    for (int i = 1; i < L->length; ++i)
    {
        // 如果找到了更小的数据元素.
        if (L->elem[i] < *value)
        {
            // 则更新 *e 存储的最小数据元素.
            *value = L->elem[i];

            // 同时更新最小数据元素的索引.
            pos = i;
        }
    }

    // 空出的位置由最后一个元素填补, 相当于把最后一个元素移动到最小的元素处,
    // 所以顺序表长度减一.
    L->elem[pos] = L->elem[L->length - 1];
    L->length--;

    return OK;
} // Del_Min

Status Reverse_Sq(SqList *L)
{
    // 如果顺序表为空.
    if (ListEmpty_Sq(*L))
    {
        // 现实错误信息.
        printf("error, the list is empty.\n");

        // 并退出运行.
        return ERROR;
    }

    // 指向顺序表首尾的指针.
    int front = 0;
    int rear = L->length - 1;
    ElemType temp; // 辅助变量. 空间复杂度为 O(1).

    do
    {
        // 交换首尾数据元素.
        temp = L->elem[rear];
        L->elem[rear] = L->elem[front];
        L->elem[front] = temp;

        // 更新指向首尾的指针.x
        ++front;
        --rear;
    } while (front < rear);

    // 答案.
    // ElemType temp; // 辅助变量.

    // /**
    //  * 让 i < length / 2 很好地避免了顺序表长度奇偶问题.
    //  * 如果长度为偶数, 正好把表分成两半; 为奇数, 正好跳过正中间的元素.
    //  * */
    // for (int i = 0; i < L->length / 2; ++i)
    // {
    //     temp = L->elem[i];
    //     // length - i - 1.
    //     L->elem[i] = L->elem[L->length - i - 1];
    //     L->elem[L->length - i - 1] = temp;
    // }

    return OK;
} // Reverse_Sq

Status DelX(SqList *L, ElemType x)
{
    int xCount = 0; // 辅助变量, 空间复杂度 O(1).

    /**
     * 算法思想: 顺序表中等于 x 的数据元素有 m 个, 用 x 将顺序表分为 m+1 个区间,
     * 每个区间中元素向前移动的长度为该区间前面 x 的数量.
     * 所以只需要扫描一次顺序表, 一边扫描, 一边统计 m, 并将不等于 x 的元素向前
     * 移动 m 单位.
     */

    // for() 时间复杂度 O(n).
    for (int i = 0; i < L->length; ++i)
    {
        if (L->elem[i] == x)
        {
            ++xCount;
        }
        else
        {
            L->elem[i - xCount] = L->elem[i];
        }
    }

    // 更新顺序表长度.
    L->length = L->length - xCount;

    return OK;
} // DelX

Status DelST1(SqList *L, ElemType s, ElemType t)
{
    if (s >= t || L->length == 0)
    {
        printf("s, t 不合理或顺序表长度为 0.\n");
        return ERROR;
    }

    // 被删除的区间长度.
    int delLen = 0;
    for (int i = 0; i < L->length; ++i)
    {
        if ((L->elem[i] > s) && (L->elem[i] < t))
        {
            ++delLen;
        }
        // 大于等于 t 的元素要前移.
        if (L->elem[i] >= t)
        {
            L->elem[i - delLen] = L->elem[i];
        }
    }

    if (delLen == 0)
    {
        printf("L 中所有元素都小于 %d\n", s);
        return ERROR;
    }

    // 更新顺序表长度.
    L->length = L->length - delLen;

    return OK;
} // DelST1

Status DelST2(SqList *L, ElemType s, ElemType t)
{
    // 和 DelX() 一样

    if (s >= t || L->length == 0)
    {
        printf("s, t 不合理或顺序表长度为 0.\n");
        return ERROR;
    }

    int k = 0; // 辅助变量, 记录值在 s 和 t 之间的元素个数.

    for (int i = 0; i < L->length; ++i)
    {
        if (L->elem[i] >= s && L->elem[i] <= t)
        {
            ++k;
        }
        else
        {
            L->elem[i - k] = L->elem[i];
        }
    }

    // 更新顺序表长度.
    L->length -= k;

    return TRUE;
} // DelST2

Status DeleteSame(SqList *L)
{
    if (L->length == 0)
    {
        return ERROR;
    }

    int i, j;
    // i 存储第一个不相同的元素, j 为工作指针.
    for (i = 0, j = 1; j < L->length; ++j)
    {
        if (L->elem[i] != L->elem[j]) // 找到下一个与上一个元素不同的元素.
        {
            L->elem[++i] = L->elem[j]; // 将给元素前移至上一个元素之后.
        }
    }

    // 更新顺序表长度.
    L->length = i + 1;

    return OK;
} // DeleteSame

Status Merge(SqList A, SqList B, SqList *C)
{
    if (A.length + B.length > LIST_MAX_SIZE)
    {
        printf("合并结果大于顺序表最大长度.\n");
        return ERROR;
    }

    int i = 0, j = 0, k = 0;

    while (i < A.length && j < B.length)
    {
        if (A.elem[i] < B.elem[j])
        {
            C->elem[k++] = A.elem[i++];
        }
        else
        {
            C->elem[k++] = B.elem[j++];
        }
    }

    while (i < A.length) // 还剩一个没有比较完的顺序表.
    {
        C->elem[k++] = A.elem[i++];
    }
    while (j < B.length)
    {
        C->elem[k++] = B.elem[j++];
    }

    C->length = k;

    return OK;
} // Merge