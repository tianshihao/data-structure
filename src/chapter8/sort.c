/**
 * @file sort.c
 * @author tianshihao4944@126.com
 * @brief 排序算法实现
 * @version 0.1
 * @date 2020-11-01
 * @copyright Copyright (c) 2020
 */

#include <chapter8/sort.h>

void InsertionSort(ElemType Arr[], int n)
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

void BinaryInsertionSort(ElemType Arr[], int n)
{
    int i, j, left, right, mid;

    for (i = 2; i < n; ++i)
    {
        if (Arr[i] < Arr[i - 1])
        {
            Arr[0] = Arr[i]; /* 设置哨兵. */

            /**
             * @brief 开始在有序子序列中折半查找合适的插入位置. 有序子序列的起始
             * 索引为 1, i - 1.
             * 查找进行到最后一趟时, 不论区间长度奇偶, 一定出现 left == right == mid,
             * 此时有 2 种情况:
             * 1) 哨兵小于 left/right 所指元素, 那么 right = right - 1,
             * right < left, 循环结束;
             * 2) 哨兵大于 left/right 所指元素, 那么 left = left + 1,
             * right < left, 循环结束.
             * 这 2 种情况下, 都有 left = right + 1, 即 left 所指的元素大于哨兵,
             * right 所指的元素小于哨兵, 故插入位置在 left 和 right 之间, 应将
             * right 之前的元素后移, right + 1 插入哨兵.
             */
            left = 1, right = i - 1;
            while (left <= right)
            {
                mid = (left + right) / 2;
                /* 合适的插入位置落在左半区间. */
                if (Arr[mid] > Arr[0]) /* 此处的 > 保证排序稳定. */
                {
                    right = mid - 1;
                }
                /* 合适的位置落在了右半区间. */
                else
                {
                    left = mid + 1;
                }
            }
            /**
             * @brief 折半查找之后, right + 1 即为要插入的位置. 统一将元素后移,
             * 空出插入位置.
             */
            for (j = i - 1; j >= right + 1; --j)
            {
                Arr[j + 1] = Arr[j];
            }

            Arr[right + 1] = Arr[0]; /* 将哨兵复制到插入位置. */
        }
    }
}

void ShellSort(ElemType Arr[], int n)
{
    int i, j, delta;
    for (delta = n / 2; delta >= 1; delta = delta / 2)
    {
        for (i = 1 + delta; i < n; ++i)
        {
            if (Arr[i] < Arr[i - delta])
            {
                Arr[0] = Arr[i];
                for (j = i - delta; (j > 0) && (Arr[0] < Arr[j]); j -= delta)
                {
                    Arr[j + delta] = Arr[j];
                }
                Arr[j + delta] = Arr[0];
            }
        }
    }
}
