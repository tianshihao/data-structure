/**
 * @file program8.c
 * @author tianshihao4944@126.com
 * @brief 测试排序算法
 * @version 0.1
 * @date 2020-11-01
 * @copyright Copyright (c) 2020
 */

#include <chapter8/sort.h>
#include <stdio.h>

int main()
{
    const int arrLen = 9;

    ElemType A[arrLen];
    A[0] = 0;
    A[1] = 49;
    A[2] = 38;
    A[3] = 65;
    A[4] = 97;
    A[5] = 76;
    A[6] = 13;
    A[7] = 27;
    A[8] = 49;

    for (int i = 0; i < arrLen; ++i)
    {
        printf("%d%c", A[i], i == arrLen - 1 ? '\n' : ',');
    }

    // InsertionSort(A, 9);
    // BinaryInsertionSort(A, 9);
    // ShellSort(A, 9);
    // BubbleSort(A, 9);
    // QuickSort(A, 1, 8);
    MergeSort(A, 0, arrLen - 1, arrLen);

    for (int i = 0; i < arrLen; ++i)
    {
        printf("%d%c", A[i], i == arrLen - 1 ? '\n' : ',');
    }

    return 0;
}