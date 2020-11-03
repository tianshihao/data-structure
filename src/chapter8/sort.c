/**
 * @file sort.c
 * @author tianshihao4944@126.com
 * @brief 排序算法实现
 * @version 0.1
 * @date 2020-11-01
 * @copyright Copyright (c) 2020
 */

#include <chapter8/sort.h>

void InsertSort(ElemType Arr[], int n)
{
    int i, j;
    for (i = 2; i < n; ++i)
    {
        if (Arr[i] < Arr[i - 1])
        {
            Arr[0] = Arr[i]; /* 设置哨兵. */

            for (j = i - 1; Arr[j] > Arr[0]; --j)
            {
                Arr[j + 1] = Arr[j]; /* 将小于哨兵的元素向后挪动. */
            }
            Arr[j + 1] = Arr[0]; /* 将哨兵复制到插入位置. */
        }
    }
}