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

    ElemType Arr[arrLen];
    Arr[0] = 0;
    Arr[1] = 49;
    Arr[2] = 38;
    Arr[3] = 65;
    Arr[4] = 97;
    Arr[5] = 76;
    Arr[6] = 13;
    Arr[7] = 27;
    Arr[8] = 49;

    for (int i = 0; i < arrLen; ++i)
    {
        printf("%d%c", Arr[i], i == arrLen - 1 ? '\n' : ',');
    }

    // InsertionSort(Arr, 9);
    // BinaryInsertionSort(Arr, 9);
    // ShellSort(Arr, 9);
    // BubbleSort(Arr, 9);
    // QuickSort(Arr, 1, 8);
    MergeSort(Arr, 0, arrLen - 1, arrLen);

    for (int i = 0; i < arrLen; ++i)
    {
        printf("%d%c", Arr[i], i == arrLen - 1 ? '\n' : ',');
    }

    return 0;
}